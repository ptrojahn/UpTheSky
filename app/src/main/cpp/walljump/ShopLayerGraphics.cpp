#include "ShopLayerGraphics.h"

#include "RenderSystem.h"
#include "AnimationSystem.h"
#include "RenderComponent.h"
#include "UniformsComponent.h"
#include "TransformComponent.h"
#include "OnLayerEnabledComponent.h"
#include "OnLayerDisabledComponent.h"
#include "TextureComponent.h"
#include "AnimationsCommon.h"
#include "MainMenuLayerLogic.h"
#include "ShopLayerLogic.h"
#include "HorizontalScrollComponent.h"
#include "OnWaitFinishedSystem.h"
#include "PlayerComponent.h"
#include "ColorChooserComponent.h"
#include "OnUpdateSystem.h"
#include "OnUpdateComponent.h"
#include "SharedPreferences.h"

void entityDelayedFadeIn(Entity* entity) {
	entity->addComponent(new AnimationComponent({
		AnimationState({
			AnimationChange((float*)&entity->getComponent<UniformsComponent>()->uniforms[0].data[0], 0.f, 0.f)
		}, 0.1f),
		AnimationState({
				AnimationChange((float*)&entity->getComponent<UniformsComponent>()->uniforms[0].data[0], 0.f, 1.f)
			}, 0.1f)
	}, AnimationComponent::Once));
}

void skinChooserFadeOut(Entity* skinChooser) {
	entityFadeOut(skinChooser);
	for (Entity* entity : skinChooser->getLayer()->getEngine()->getEntities()){
		if (entity->getComponent<PlayerComponent>()){
			std::vector<Uniform> &chooserUniforms = skinChooser->getComponent<UniformsComponent>()->uniforms;
			std::vector<Uniform> &playerUniforms = entity->getComponent<UniformsComponent>()->uniforms;
			*(int*)&playerUniforms[3].data[0] = *(float*)&chooserUniforms[1].data[0] / -2.f;
			*(int*)&playerUniforms[0].data[0]  = *(int*)&chooserUniforms[2].data[0];
			*(int*)&playerUniforms[1].data[0]  = *(int*)&chooserUniforms[3].data[0];
			*(int*)&playerUniforms[2].data[0]  = *(int*)&chooserUniforms[4].data[0];
			SharedPreferences::getSharedPreferences().putInt("skinIndex", *(float*)&chooserUniforms[1].data[0] / -2.f);
			SharedPreferences::getSharedPreferences().putInt("color0", *(int*)&chooserUniforms[2].data[0]);
			SharedPreferences::getSharedPreferences().putInt("color1", *(int*)&chooserUniforms[3].data[0]);
			SharedPreferences::getSharedPreferences().putInt("color2", *(int*)&chooserUniforms[4].data[0]);
			SharedPreferences::getSharedPreferences().apply();
			break;
		}
	}
}

void updateLock(Entity* lock) {
	float offset = *(float*)&dynamic_cast<ShopLayerGraphics*>(lock->getLayer())->getSkinChooser()->getComponent<UniformsComponent>()->uniforms[1].data[0];
	bool firstUnlocked = SharedPreferences::getSharedPreferences().getInt(("skinUnlocked" + std::to_string((int)floor(offset / -2.))).c_str());
	bool secondUnlocked = SharedPreferences::getSharedPreferences().getInt(("skinUnlocked" + std::to_string((int)ceil(offset / -2.))).c_str());
	*(float*)&lock->getComponent<UniformsComponent>()->uniforms[1].data[0] = 1 - (firstUnlocked + (secondUnlocked - firstUnlocked) * (offset / -2.f - floorf(offset / -2.f)));
}

void updatePrice(Entity* price) {
	updateLock(price);
	float offset = *(float*)&dynamic_cast<ShopLayerGraphics*>(price->getLayer())->getSkinChooser()->getComponent<UniformsComponent>()->uniforms[1].data[0];
	*(int*)&price->getComponent<UniformsComponent>()->uniforms[2].data[0] = offset / -2.f > 7.5f ? 600 : 200;
}

void updateSkinChooser(Entity* skinChooser) {
	//Play sound if the skin changed
	HorizontalScrollComponent* scrollComponent = skinChooser->getComponent<HorizontalScrollComponent>();
	int lastSkin = floorf(scrollComponent->lastValue/2.f + 0.5f);
	int currentSkin = floorf(*scrollComponent->currentValue/2.f + 0.5f);
	if (lastSkin != currentSkin)
		AudioManager::instance().playAudio(dynamic_cast<ShopLayerGraphics*>(skinChooser->getLayer())->getUiInteractionSound());
	scrollComponent->lastValue = *scrollComponent->currentValue;
}

void updateColorChooser(Entity* colorChooser) {
	//Update alpha of the color chooser. The color chooser only needs to be visible if the current skin supports the color.
	ColorChooserComponent* component = colorChooser->getComponent<ColorChooserComponent>();
	*component->colorOffset = *(float*)&colorChooser->getComponent<UniformsComponent>()->uniforms[1].data[0] * -2 + 0.5f;
	*(float*)&colorChooser->getComponent<UniformsComponent>()->uniforms[2].data[0] = 1 - std::min(std::max(*component->skinOffset + component->edge, 0.f), 1.f);
	//Play sound if the color changed
	HorizontalScrollComponent* scrollComponent = colorChooser->getComponent<HorizontalScrollComponent>();
	int lastColor = floorf(scrollComponent->lastValue*2.f + 0.5f);
	int currentColor = floorf(*scrollComponent->currentValue*2.f + 0.5f);
	if (lastColor != currentColor)
		AudioManager::instance().playAudio(dynamic_cast<ShopLayerGraphics*>(colorChooser->getLayer())->getUiInteractionSound());
	scrollComponent->lastValue = *scrollComponent->currentValue;
}

void ShopLayerGraphics::load() {
	float offset = SharedPreferences::getSharedPreferences().getInt("skinIndex")*-2.f;
	int color0 = SharedPreferences::getSharedPreferences().getInt("color0");
	int color1 = SharedPreferences::getSharedPreferences().getInt("color1");
	int color2 = SharedPreferences::getSharedPreferences().getInt("color2");
	uiInteractionSound = AudioManager::instance().loadAudio("uiInteraction.ogg");

	addEntity((new Entity(0))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("defaultUV.vert", "mainMenuButton.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 2, 2))))
		->addComponent(new TransformComponent(Vector2<float>(0.2, 13.8)))
		->addComponent(new UniformsComponent({ Uniform("alpha", 0.f) }))
		->addComponent(new OnLayerDisabledComponent(entityFadeOut, classId<ShopLayerLogic>()))
		->addComponent(new OnLayerEnabledComponent(entityFadeIn, classId<ShopLayerLogic>()))
		->addComponent(new TextureComponent({Texture("menuButtonBack.bmp", "texture", GL_NEAREST) })));

	skinChooser = new Entity(101);
	skinChooser->addComponent(new RenderComponent(ShaderManager::instance().createShader("defaultUV.vert", "skinChooser.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 9, 4))));
	skinChooser->addComponent(new TransformComponent(Vector2<float>(0.f, 1.5f)));
	skinChooser->addComponent(new TextureComponent({ Texture("playerAtlas.bmp", "atlas", GL_NEAREST), Texture("skinColors.bmp", "colors", GL_NEAREST) }));
	skinChooser->addComponent(new UniformsComponent({ Uniform("alpha", 0.f), Uniform("offset", offset), Uniform("color0", color0), Uniform("color1", color1), Uniform("color2", color2) }));
	skinChooser->addComponent(new OnLayerDisabledComponent(skinChooserFadeOut, classId<ShopLayerLogic>()));
	skinChooser->addComponent(new OnLayerEnabledComponent(entityDelayedFadeIn, classId<ShopLayerLogic>()));
	skinChooser->addComponent(new HorizontalScrollComponent(-30.f, 0.f, (float*)&skinChooser->getComponent<UniformsComponent>()->uniforms[1].data[0], Vector2<float>(9.f, 4.f), 2.f));
	skinChooser->addComponent(new OnUpdateComponent(updateSkinChooser));
	addEntity(skinChooser);

	lock = new Entity(99);
	lock->addComponent(new RenderComponent(ShaderManager::instance().createShader("defaultUV.vert", "lock.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0.f, 0.f, 1.8f, 1.8f))));
	lock->addComponent(new TransformComponent(Vector2<float>(3.6f, 2.f)));
	lock->addComponent(new TextureComponent({Texture("lock.bmp", "texture", GL_NEAREST)}));
	lock->addComponent(new UniformsComponent({ Uniform("alpha", 0.f), Uniform("alphaUnlocked", 0.f) }));
	lock->addComponent(new OnLayerDisabledComponent(entityFadeOut, classId<ShopLayerLogic>()));
	lock->addComponent(new OnLayerEnabledComponent(entityDelayedFadeIn, classId<ShopLayerLogic>()));
	lock->addComponent(new OnUpdateComponent(updateLock));
	addEntity(lock);

	skinPrice = new Entity(99);
	skinPrice->addComponent(new RenderComponent(ShaderManager::instance().createShader("money.vert", "moneyAlpha.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0.f, 0.f, 0.625f*0.75f, 1.f * 0.75f))));
	skinPrice->addComponent(new TransformComponent(Vector2<float>(4.5f - 0.625f*0.75f*3.5f / 2.f, 4.f)));
	skinPrice->addComponent(new UniformsComponent({ Uniform("alpha", 0.f), Uniform("alphaUnlocked", 0.f), Uniform("money", 100), Uniform("length", 3)}));
	skinPrice->addComponent(new OnLayerDisabledComponent(entityFadeOut, classId<ShopLayerLogic>()));
	skinPrice->addComponent(new OnLayerEnabledComponent(entityDelayedFadeIn, classId<ShopLayerLogic>()));
	skinPrice->addComponent(new TextureComponent({Texture("digits.bmp", "digits", GL_NEAREST)}));
	skinPrice->addComponent(new OnUpdateComponent(updatePrice));
	addEntity(skinPrice);

	Entity* colorChooser0 = new Entity(101);
	colorChooser0->addComponent(new RenderComponent(ShaderManager::instance().createShader("defaultUV.vert", "colorChooser.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 9, 1))));
	colorChooser0->addComponent(new TransformComponent(Vector2<float>(0.f, 7.f)));
	colorChooser0->addComponent(new UniformsComponent({Uniform("alpha", 0.f), Uniform("offset", color0 / -2.f), Uniform("alphaEnabled", 0.f) }));
	colorChooser0->addComponent(new HorizontalScrollComponent(-15.5f, 0.f, (float*)&colorChooser0->getComponent<UniformsComponent>()->uniforms[1].data[0], Vector2<float>(9, 1), 0.5f));
	colorChooser0->addComponent(new OnLayerDisabledComponent(entityFadeOut, classId<ShopLayerLogic>()));
	colorChooser0->addComponent(new OnLayerEnabledComponent(entityDelayedFadeIn, classId<ShopLayerLogic>()));
	colorChooser0->addComponent(new TextureComponent({ Texture("skinColors.bmp", "colors", GL_NEAREST) }));
	colorChooser0->addComponent(new OnUpdateComponent(updateColorChooser));
	colorChooser0->addComponent(new ColorChooserComponent((int*)&skinChooser->getComponent<UniformsComponent>()->uniforms[2].data[0], (float*)&skinChooser->getComponent<UniformsComponent>()->uniforms[1].data[0], 0));
	addEntity(colorChooser0);

	Entity* colorChooser1 = new Entity(101);
	colorChooser1->addComponent(new RenderComponent(ShaderManager::instance().createShader("defaultUV.vert", "colorChooser.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 9, 1))));
	colorChooser1->addComponent(new TransformComponent(Vector2<float>(0.f, 8.5f)));
	colorChooser1->addComponent(new UniformsComponent({ Uniform("alpha", 0.f), Uniform("offset", color1 / -2.f), Uniform("alphaEnabled", 0.f) }));
	colorChooser1->addComponent(new HorizontalScrollComponent(-15.5f, 0.f, (float*)&colorChooser1->getComponent<UniformsComponent>()->uniforms[1].data[0], Vector2<float>(9, 1), 0.5f));
	colorChooser1->addComponent(new OnLayerDisabledComponent(entityFadeOut, classId<ShopLayerLogic>()));
	colorChooser1->addComponent(new OnLayerEnabledComponent(entityDelayedFadeIn, classId<ShopLayerLogic>()));
	colorChooser1->addComponent(new TextureComponent({ Texture("skinColors.bmp", "colors", GL_NEAREST) }));
	colorChooser1->addComponent(new OnUpdateComponent(updateColorChooser));
	colorChooser1->addComponent(new ColorChooserComponent((int*)&skinChooser->getComponent<UniformsComponent>()->uniforms[3].data[0], (float*)&skinChooser->getComponent<UniformsComponent>()->uniforms[1].data[0], 2));
	addEntity(colorChooser1);

	Entity* colorChooser2 = new Entity(101);
	colorChooser2->addComponent(new RenderComponent(ShaderManager::instance().createShader("defaultUV.vert", "colorChooser.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 9, 1))));
	colorChooser2->addComponent(new TransformComponent(Vector2<float>(0.f, 10.f)));
	colorChooser2->addComponent(new UniformsComponent({ Uniform("alpha", 0.f), Uniform("offset", color2 / -2.f), Uniform("alphaEnabled", 0.f) }));
	colorChooser2->addComponent(new HorizontalScrollComponent(-15.5f, 0.f, (float*)&colorChooser2->getComponent<UniformsComponent>()->uniforms[1].data[0], Vector2<float>(9, 1), 0.5f));
	colorChooser2->addComponent(new OnLayerDisabledComponent(entityFadeOut, classId<ShopLayerLogic>()));
	colorChooser2->addComponent(new OnLayerEnabledComponent(entityDelayedFadeIn, classId<ShopLayerLogic>()));
	colorChooser2->addComponent(new TextureComponent({ Texture("skinColors.bmp", "colors", GL_NEAREST) }));
	colorChooser2->addComponent(new OnUpdateComponent(updateColorChooser));
	colorChooser2->addComponent(new ColorChooserComponent((int*)&skinChooser->getComponent<UniformsComponent>()->uniforms[4].data[0], (float*)&skinChooser->getComponent<UniformsComponent>()->uniforms[1].data[0], 16));
	addEntity(colorChooser2);

	addSystem(new OnUpdateSystem(4));
	addSystem(new OnWaitFinishedSystem(2));
	addSystem(new AnimationSystem(1));
	addSystem(new RenderSystem(0));
}