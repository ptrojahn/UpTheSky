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

class SunComponent : public BaseComponent<SunComponent>{
public:
	SunComponent(Entity* overlay) : overlay(overlay) {}
	Entity* overlay;
};

void updateSun(Entity* entity) {
	float time = (10.f - (entity->getComponent<TransformComponent>()->position.y - 5)) / 10.f;
	*(float*)&entity->getComponent<UniformsComponent>()->uniforms[0].data[0] = time;

	Uniform& color = entity->getComponent<SunComponent>()->overlay->getComponent<UniformsComponent>()->uniforms[0];
	if (time > 0.2){
		*(float*)&color.data[0                ] = 0.63922 * (time - 0.3) / 0.7 + 1.0f * (1 - (time - 0.3) / 0.7);
		*(float*)&color.data[1 * sizeof(float)] = 0.89804 * (time - 0.3) / 0.7 + 0.5f * (1 - (time - 0.3) / 0.7);
		*(float*)&color.data[2 * sizeof(float)] = 0.89804 * (time - 0.3) / 0.7 + 0.1f * (1 - (time - 0.3) / 0.7);
		*(float*)&color.data[3 * sizeof(float)] =                                0.3f * (1 - (time - 0.2) / 0.7);
	} else if (time > 0){
		*(float*)&color.data[0                ] = 1.0f * time / 0.3 + 0.2f * (1 - time / 0.3);
		*(float*)&color.data[1 * sizeof(float)] = 0.5f * time / 0.3 + 0.2f * (1 - time / 0.3);
		*(float*)&color.data[2 * sizeof(float)] = 0.1f * time / 0.3 + .25f * (1 - time / 0.3);
		*(float*)&color.data[3 * sizeof(float)] = 0.3f * time / 0.3 + .60f * (1 - time / 0.3);
	}
}

void BackgroundLayer::load() {
	Entity* sunOverlay = (new Entity(300))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("default.vert", "sunOverlay.frag"),
		BufferManager::instance().createBuffer(BufferManager::rectangleVertices2D(0.f, 0.f, 9.f, 16.f))))
		->addComponent(new UniformsComponent({ Uniform("color", 0.f, 0.f, 0.f, 0.f) }));
	addEntity(sunOverlay);
	addEntity((new Entity(301))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("defaultUV.vert", "backgroundHeightMap.frag"),
		BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0.f, 0.f, 9.f, 3.f))))
		->addComponent(new TransformComponent(Vector2<float>(0.f, 13.f)))
		->addComponent(new UniformsComponent({Uniform("color", 0.3f, 0.3f, 0.3f)}))
		->addComponent(new TextureComponent("hills0.bmp")));
	addEntity((new Entity(302))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("defaultUV.vert", "backgroundHeightMap.frag"),
		BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0.f, 0.f, 9.f, 3.f))))
		->addComponent(new TransformComponent(Vector2<float>(0.f, 12.f)))
		->addComponent(new UniformsComponent({ Uniform("color", 0.4f, 0.4f, 0.4f) }))
		->addComponent(new TextureComponent("hills1.bmp")));
	addEntity((new Entity(303))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("defaultUV.vert", "backgroundHeightMap.frag"),
		BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0.f, 0.f, 9.f, 3.f))))
		->addComponent(new TransformComponent(Vector2<float>(0.f, 11.f)))
		->addComponent(new UniformsComponent({ Uniform("color", 0.5f, 0.5f, 0.5f) }))
		->addComponent(new TextureComponent("hills2.bmp")));
	Entity* sun = (new Entity(304))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("defaultUV.vert", "sun.frag"),
		BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0.f, 0.f, 3.f, 3.f))))
		->addComponent(new TransformComponent(Vector2<float>(3.f, 15.f)))
		->addComponent(new UniformsComponent({ Uniform("time", 0.f) }))
		->addComponent(new ScrollComponent(0.2))
		->addComponent(new OnUpdateComponent(updateSun))
		->addComponent(new SunComponent(sunOverlay));
	addEntity(sun
		->addComponent(new AnimationComponent({
			AnimationState({ 
				AnimationChange(&sun->getComponent<TransformComponent>()->position.y, 15.f, 5.f) 
			}, 1.f)
		}, AnimationComponent::Once)));

	addSystem(new OnUpdateSystem(2));
	addSystem(new AnimationSystem(1));
	addSystem(new RenderSystem(0));
}