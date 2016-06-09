#include "GameOverlayLayer.h"

#include "RenderSystem.h"
#include "RenderComponent.h"
#include "AnimationSystem.h"
#include "AnimationComponent.h"
#include "TransformComponent.h"
#include "StaticColliderComponent.h"
#include "OnLayerEnabledComponent.h"
#include "OnLayerDisabledComponent.h"
#include "GameLayer.h"

void fadeInLeft(Entity* entity) {
	entity->addComponent(new AnimationComponent({
		AnimationState({
			AnimationChange(&entity->getComponent<TransformComponent>()->position.x, -4.f, -3.5f)
		}, 0.1f) 
	}, AnimationComponent::Once));
}

void fadeOutLeft(Entity* entity) {
	entity->addComponent(new AnimationComponent({
		AnimationState({
			AnimationChange(&entity->getComponent<TransformComponent>()->position.x, -3.5f, -4.f)
		}, 0.1f)
	}, AnimationComponent::Once));
}

void fadeInRight(Entity* entity) {
	entity->addComponent(new AnimationComponent({
		AnimationState({
			AnimationChange(&entity->getComponent<TransformComponent>()->position.x, 9.f, 8.5f)
		}, 0.1f)
	}, AnimationComponent::Once));
}

void fadeOutRight(Entity* entity) {
	entity->addComponent(new AnimationComponent({
		AnimationState({
			AnimationChange(&entity->getComponent<TransformComponent>()->position.x, 8.5f, 9.f)
		}, 0.1f)
	}, AnimationComponent::Once));
}

void GameOverlayLayer::load() {
	//Level border
	addEntity((new Entity(200))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("default.vert", "levelGeometry.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2D(0, 0, 4, 16))))
		->addComponent(new TransformComponent(Vector2<float>(-4.f, 0)))
		->addComponent(new OnLayerEnabledComponent(fadeInLeft, classId<GameLayer>()))
		->addComponent(new OnLayerDisabledComponent(fadeOutLeft, classId<GameLayer>())));
	addEntity((new Entity(200))
		->addComponent(new TransformComponent(Vector2<float>(-3.5f, 0)))
		->addComponent(new StaticColliderComponent(Vector2<float>(4, 16))));

	addEntity((new Entity(200))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("default.vert", "levelGeometry.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2D(0, 0, 4, 16))))
		->addComponent(new TransformComponent(Vector2<float>(9, 0)))
		->addComponent(new OnLayerEnabledComponent(fadeInRight, classId<GameLayer>()))
		->addComponent(new OnLayerDisabledComponent(fadeOutRight, classId<GameLayer>())));
	addEntity((new Entity(200))
		->addComponent(new TransformComponent(Vector2<float>(8.5f, 0)))
		->addComponent(new StaticColliderComponent(Vector2<float>(4, 16))));

	addSystem(new AnimationSystem(1));
	addSystem(new RenderSystem(0));
}