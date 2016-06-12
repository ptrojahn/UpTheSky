#include "BackgroundLayer.h"
#include "RenderSystem.h"
#include "RenderComponent.h"
#include "ShaderManager.h"
#include "BufferManager.h"
#include "TransformComponent.h"
#include "UniformsComponent.h"
#include "ScrollComponent.h"
#include "TextureComponent.h"
#include "AnimationComponent.h"
#include "AnimationSystem.h"
#include "OnUpdateSystem.h"
#include "OnUpdateComponent.h"
#include "OnLayerDisabledComponent.h"
#include "GameLayer.h"
#include "CloudSystem.h"
#include "CloudComponent.h"
#include "MersenneTwisterEngine.h"

class SunComponent : public BaseComponent<SunComponent>{
public:
	SunComponent(Entity* overlay) : overlay(overlay) {}
	Entity* overlay;
};

void updateSun(Entity* entity) {
	float& yPos = entity->getComponent<TransformComponent>()->position.y;
	if (yPos > 15)
		yPos = 15;
	float sunProgress = (10.f - (yPos - 5)) / 10.f;
	*(float*)&entity->getComponent<UniformsComponent>()->uniforms[0].data[0] = sunProgress;

	Uniform& color = entity->getComponent<SunComponent>()->overlay->getComponent<UniformsComponent>()->uniforms[0];
	if (sunProgress > 0.4){
		*(float*)&color.data[0                ] = 0.63922 * (sunProgress - 0.4) / 0.6 + 1.0f * (1 - (sunProgress - 0.4) / 0.6);
		*(float*)&color.data[1 * sizeof(float)] = 0.89804 * (sunProgress - 0.4) / 0.6 + 0.45f * (1 - (sunProgress - 0.4) / 0.6);
		*(float*)&color.data[2 * sizeof(float)] = 0.89804 * (sunProgress - 0.4) / 0.6 + 0.1f * (1 - (sunProgress - 0.4) / 0.6);
		*(float*)&color.data[3 * sizeof(float)] = 0.3f * (1 - (sunProgress - 0.4) / 0.6);
	} else if (sunProgress > 0){
		*(float*)&color.data[0                ] = 1.0f * sunProgress / 0.4 + 0.2f * (1 - sunProgress / 0.4);
		*(float*)&color.data[1 * sizeof(float)] = 0.45f * sunProgress / 0.4 + 0.2f * (1 - sunProgress / 0.4);
		*(float*)&color.data[2 * sizeof(float)] = 0.1f * sunProgress / 0.4 + .25f * (1 - sunProgress / 0.4);
		*(float*)&color.data[3 * sizeof(float)] = 0.3f * sunProgress / 0.4 + .60f * (1 - sunProgress / 0.4);
	}
}

void BackgroundLayer::load() {
	Entity* sunOverlay = (new Entity(301))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("default.vert", "sunOverlay.frag"),
		BufferManager::instance().createBuffer(BufferManager::rectangleVertices2D(0.f, 0.f, 9.f, 16.f))))
		->addComponent(new UniformsComponent({ Uniform("color", 0.f, 0.f, 0.f, 0.f) }));
	addEntity(sunOverlay);
	addEntity((new Entity(302))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("defaultUV.vert", "backgroundHeightMap.frag"),
		BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0.f, 0.f, 9.f, 3.f))))
		->addComponent(new TransformComponent(Vector2<float>(0.f, 13.f)))
		->addComponent(new UniformsComponent({Uniform("color", 0.3f, 0.3f, 0.3f)}))
		->addComponent(new TextureComponent("hills0.bmp")));
	addEntity((new Entity(303))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("defaultUV.vert", "backgroundHeightMap.frag"),
		BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0.f, 0.f, 9.f, 3.f))))
		->addComponent(new TransformComponent(Vector2<float>(0.f, 12.f)))
		->addComponent(new UniformsComponent({ Uniform("color", 0.4f, 0.4f, 0.4f) }))
		->addComponent(new TextureComponent("hills1.bmp")));
	addEntity((new Entity(304))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("defaultUV.vert", "backgroundHeightMap.frag"),
		BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0.f, 0.f, 9.f, 3.f))))
		->addComponent(new TransformComponent(Vector2<float>(0.f, 11.f)))
		->addComponent(new UniformsComponent({ Uniform("color", 0.5f, 0.5f, 0.5f) }))
		->addComponent(new TextureComponent("hills2.bmp")));
	addEntity((new Entity(305))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("defaultUV.vert", "sun.frag"),
		BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0.f, 0.f, 3.f, 3.f))))
		->addComponent(new TransformComponent(Vector2<float>(3.f, 5.f)))
		->addComponent(new UniformsComponent({ Uniform("sunProgress", 0.f) }))
		->addComponent(new ScrollComponent(0.2))
		->addComponent(new OnUpdateComponent(updateSun))
		->addComponent(new OnLayerDisabledComponent([](Entity* entity){
		float& posY = entity->getComponent<TransformComponent>()->position.y;
			entity->addComponent(new AnimationComponent({
				AnimationState({
					AnimationChange(&posY, posY, 5)
				}, (posY - 5) / 10 * 0.5),
			}, AnimationComponent::Once));
		}, getEngine()->getLayer<GameLayer>()->getId()))
		->addComponent(new SunComponent(sunOverlay)));

	std::uniform_real_distribution<float> xPosGenerator(0, 8);
	std::uniform_real_distribution<float> yPosGenerator(0, 14);
	std::uniform_int_distribution<int> indexGenerator(0, 3);
	for (int i = 0; i < 3; i++){
		addEntity((new Entity(300))
			->addComponent(new RenderComponent(ShaderManager::instance().createShader("defaultUV.vert", "cloud.frag"),
			BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 8, 1.0625))))
			->addComponent(new TransformComponent(Vector2<float>(xPosGenerator(getMtEngine()), yPosGenerator(getMtEngine()))))
			->addComponent(new UniformsComponent({ Uniform("index", indexGenerator(getMtEngine())) }))
			->addComponent(new TextureComponent("clouds.bmp"))
			->addComponent(new CloudComponent(0.2f)));
	}

	addSystem(new CloudSystem());
	addSystem(new OnUpdateSystem(2));
	addSystem(new AnimationSystem(1));
	addSystem(new RenderSystem(0));
}