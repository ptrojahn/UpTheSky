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

void updateSun(Entity* entity) {
	float time = (10.f - (entity->getComponent<TransformComponent>()->position.y - 5)) / 10.f;
	*(float*)&entity->getComponent<UniformsComponent>()->uniforms[0].data[0] = time;
	if (time > 0.2)
		glClearColor(0.63922 * (time - 0.2) / 0.8 + 0.8f * (1 - (time - 0.2) / 0.8),
		             0.89804 * (time - 0.2) / 0.8 + 0.8f * (1 - (time - 0.2) / 0.8),
		             0.89804 * (time - 0.2) / 0.8 + 0.6f * (1 - (time - 0.2) / 0.8),
		             1);
	else if(time > 0)
		glClearColor(0.8f * time / 0.2 + 0.4f * (1 - time / 0.2),
		             0.8f * time / 0.2 + 0.4f * (1 - time / 0.2),
		             0.6f * time / 0.2 + .5f * (1 - time / 0.2),
		             1);
}

void BackgroundLayer::load() {
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
		->addComponent(new OnUpdateComponent(updateSun));
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