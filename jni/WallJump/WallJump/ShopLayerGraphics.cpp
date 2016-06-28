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
#include "Player.h"

void entityDelayedFadeIn(Entity* entity) {
	entity->addComponent(new AnimationComponent({
		AnimationState({
			AnimationChange((float*)&entity->getComponent<UniformsComponent>()->uniforms[1].data[0], 0.f, 0.f)
		}, 0.1f),
		AnimationState({
				AnimationChange((float*)&entity->getComponent<UniformsComponent>()->uniforms[1].data[0], 0.f, 1.f)
			}, 0.1f)
	}, AnimationComponent::Once));
}

void playerChooserFadeIn(Entity* playerChooser) {
	entityDelayedFadeIn(playerChooser);
	for (Entity* entity : playerChooser->getLayer()->getEngine()->getEntities()){
		if (entity->getComponent<PlayerComponent>()){
			std::vector<Uniform> &chooserUniforms = playerChooser->getComponent<UniformsComponent>()->uniforms;
			std::vector<Uniform> &playerUniforms = entity->getComponent<UniformsComponent>()->uniforms;
			*(float*)&chooserUniforms[0].data[0] = *(int*)&playerUniforms[3].data[0] * -2;
			*(float*)&chooserUniforms[2].data[0]                 = *(float*)&playerUniforms[0].data[0];
			*(float*)&chooserUniforms[2].data[sizeof(float)]     = *(float*)&playerUniforms[0].data[sizeof(float)];
			*(float*)&chooserUniforms[2].data[sizeof(float) * 2] = *(float*)&playerUniforms[0].data[sizeof(float) * 2];
			*(float*)&chooserUniforms[3].data[0]                 = *(float*)&playerUniforms[1].data[0];
			*(float*)&chooserUniforms[3].data[sizeof(float)]     = *(float*)&playerUniforms[1].data[sizeof(float)];
			*(float*)&chooserUniforms[3].data[sizeof(float) * 2] = *(float*)&playerUniforms[1].data[sizeof(float) * 2];
			*(float*)&chooserUniforms[4].data[0]                 = *(float*)&playerUniforms[2].data[0];
			*(float*)&chooserUniforms[4].data[sizeof(float)]     = *(float*)&playerUniforms[2].data[sizeof(float)];
			*(float*)&chooserUniforms[4].data[sizeof(float) * 2] = *(float*)&playerUniforms[2].data[sizeof(float) * 2];
			break;
		}
	}
}

void playerChooserFadeOut(Entity* playerChooser) {
	entityFadeOut(playerChooser);
	for (Entity* entity : playerChooser->getLayer()->getEngine()->getEntities()){
		if (entity->getComponent<PlayerComponent>()){
			std::vector<Uniform> &chooserUniforms = playerChooser->getComponent<UniformsComponent>()->uniforms;
			std::vector<Uniform> &playerUniforms = entity->getComponent<UniformsComponent>()->uniforms;
			*(int*)&playerUniforms[3].data[0] = *(float*)&chooserUniforms[0].data[0] / -2;
			break;
		}
	}
}

void ShopLayerGraphics::load() {
	addEntity((new Entity(0))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("defaultUV.vert", "mainMenuButton.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 2, 2))))
		->addComponent(new TransformComponent(Vector2<float>(0.2, 13.8)))
		->addComponent(new UniformsComponent({ Uniform("alpha", 0.f) }))
		->addComponent(new OnLayerDisabledComponent(entityFadeOut, classId<ShopLayerLogic>()))
		->addComponent(new OnLayerEnabledComponent(entityFadeIn, classId<ShopLayerLogic>()))
		->addComponent(new TextureComponent("menuButtonBack.bmp", GL_NEAREST)));

	Entity* skinChooser = new Entity(101);
	skinChooser->addComponent(new RenderComponent(ShaderManager::instance().createShader("defaultUV.vert", "skinChooser.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 9, 4))));
	skinChooser->addComponent(new TransformComponent(Vector2<float>(0.f, 1.5f)));
	skinChooser->addComponent(new TextureComponent("playerAtlas.bmp", GL_NEAREST));
	skinChooser->addComponent(new UniformsComponent({ Uniform("offset", 0.f), Uniform("alpha", 0.f), Uniform("color0", 1.f, 0.f, 0.f), Uniform("color1", 0.f, 1.f, 0.f), Uniform("color2", 0.f, 0.f, 1.f) }));
	skinChooser->addComponent(new OnLayerDisabledComponent(playerChooserFadeOut, classId<ShopLayerLogic>()));
	skinChooser->addComponent(new OnLayerEnabledComponent(playerChooserFadeIn, classId<ShopLayerLogic>()));
	skinChooser->addComponent(new HorizontalScrollComponent(-30.f, 0.f, (float*)&skinChooser->getComponent<UniformsComponent>()->uniforms[0].data[0], Vector2<float>(9.f, 4.f), 2.f));
	addEntity(skinChooser);

	Entity* colorChooser0 = new Entity(101);
	colorChooser0->addComponent(new RenderComponent(ShaderManager::instance().createShader("defaultUV.vert", "colorChooser.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 9, 1))));
	colorChooser0->addComponent(new TransformComponent(Vector2<float>(0.f, 7.f)));
	colorChooser0->addComponent(new UniformsComponent({ Uniform("offset", 0.f), Uniform("alpha", 0.f) }));
	colorChooser0->addComponent(new HorizontalScrollComponent(-15.5f, 0.f, (float*)&colorChooser0->getComponent<UniformsComponent>()->uniforms[0].data[0], Vector2<float>(9, 1), 0.5f));
	colorChooser0->addComponent(new OnLayerDisabledComponent(entityFadeOut, classId<ShopLayerLogic>()));
	colorChooser0->addComponent(new OnLayerEnabledComponent(entityDelayedFadeIn, classId<ShopLayerLogic>()));
	colorChooser0->addComponent(new TextureComponent("skinColors.bmp", GL_NEAREST));
	addEntity(colorChooser0);

	Entity* colorChooser1 = new Entity(101);
	colorChooser1->addComponent(new RenderComponent(ShaderManager::instance().createShader("defaultUV.vert", "colorChooser.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 9, 1))));
	colorChooser1->addComponent(new TransformComponent(Vector2<float>(0.f, 8.5f)));
	colorChooser1->addComponent(new UniformsComponent({ Uniform("offset", 0.f), Uniform("alpha", 0.f) }));
	colorChooser1->addComponent(new HorizontalScrollComponent(-15.5f, 0.f, (float*)&colorChooser1->getComponent<UniformsComponent>()->uniforms[0].data[0], Vector2<float>(9, 1), 0.5f));
	colorChooser1->addComponent(new OnLayerDisabledComponent(entityFadeOut, classId<ShopLayerLogic>()));
	colorChooser1->addComponent(new OnLayerEnabledComponent(entityDelayedFadeIn, classId<ShopLayerLogic>()));
	colorChooser1->addComponent(new TextureComponent("skinColors.bmp", GL_NEAREST));
	addEntity(colorChooser1);

	Entity* colorChooser2 = new Entity(101);
	colorChooser2->addComponent(new RenderComponent(ShaderManager::instance().createShader("defaultUV.vert", "colorChooser.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 9, 1))));
	colorChooser2->addComponent(new TransformComponent(Vector2<float>(0.f, 10.f)));
	colorChooser2->addComponent(new UniformsComponent({ Uniform("offset", 0.f), Uniform("alpha", 0.f) }));
	colorChooser2->addComponent(new HorizontalScrollComponent(-15.5f, 0.f, (float*)&colorChooser2->getComponent<UniformsComponent>()->uniforms[0].data[0], Vector2<float>(9, 1), 0.5f));
	colorChooser2->addComponent(new OnLayerDisabledComponent(entityFadeOut, classId<ShopLayerLogic>()));
	colorChooser2->addComponent(new OnLayerEnabledComponent(entityDelayedFadeIn, classId<ShopLayerLogic>()));
	colorChooser2->addComponent(new TextureComponent("skinColors.bmp", GL_NEAREST));
	addEntity(colorChooser2);

	addSystem(new OnWaitFinishedSystem(2));
	addSystem(new AnimationSystem(1));
	addSystem(new RenderSystem(0));
}