#include "PlayerLayer.h"

#include "RenderComponent.h"
#include "TransformComponent.h"
#include "RenderSystem.h"
#include "ScrollComponent.h"
#include "Player.h"
#include "GhostWall.h"
#include "TextureComponent.h"
#include "UniformsComponent.h"
#include "ScoreComponent.h"
#include "AnimationSystem.h"
#include "ParticleSystem.h"
#include "OnWaitFinishedComponent.h"
#include "OnWaitFinishedSystem.h"
#include "AnimationComponent.h"

void deleteTrailEntity(Entity* trailEntity) {
	trailEntity->getLayer()->deleteEntity(trailEntity);
}

void addTrailEntity(Entity* player) {
	TransformComponent* transformComponent = player->getComponent<TransformComponent>();
	Entity* trailItem = new Entity(101);
	trailItem->addComponent(new RenderComponent(ShaderManager::instance().createShader("default.vert", "playerTrail.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2D(0, 0, PlayerSystem::playerSize.x, PlayerSystem::playerSize.y))));
	UniformsComponent* uniformsComponent = new UniformsComponent({ Uniform("alpha", 1.f) });
	trailItem->addComponent(uniformsComponent);
	trailItem->addComponent(new TransformComponent(transformComponent->position, transformComponent->rotation, transformComponent->scale));
	trailItem->addComponent(new OnWaitFinishedComponent(100, deleteTrailEntity));
	trailItem->addComponent(new ScrollComponent());
	trailItem->addComponent(new AnimationComponent({
		AnimationState({
			AnimationChange((float*)(&uniformsComponent->uniforms[0].data[0]), 1.f, 0.f) 
		}, 0.1f)
	}, AnimationComponent::Once));
	player->getLayer()->addEntity(trailItem);
	player->addComponent(new OnWaitFinishedComponent(16, addTrailEntity));
}

void PlayerLayer::load() {
	addEntity((new Entity(100))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("defaultUV.vert", "player.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 1, 2))))
		->addComponent(new TransformComponent(Vector2<float>(getEngine()->getLogicalScreenSize().x / 2.f - 1, getEngine()->getLogicalScreenSize().y / 2.f - 2), 0, Vector2<float>(2.f, 2.f)))
		->addComponent(new PlayerComponent())
		->addComponent(new ScrollComponent())
		->addComponent(new TextureComponent("playerAtlas.bmp", GL_NEAREST))
		->addComponent(new UniformsComponent({ Uniform("color0", 0.f, 0.f, 0.f), Uniform("color1", 0.9f, 0.1f, 0.1f), Uniform("color2", 0.9f, 0.9f, 0.1f), Uniform("atlasIndex", 13) }))
		->addComponent(new OnWaitFinishedComponent(5, addTrailEntity)));

	addEntity((new Entity(0))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("score.vert", "score.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(-0.625, -1, 1.25, 2))))
		->addComponent(new TransformComponent(Vector2<float>(4.5, 2)))
		->addComponent(new TextureComponent("digits.bmp", GL_NEAREST))
		->addComponent(new UniformsComponent({ Uniform("score", 0), Uniform("length", 1), Uniform("alpha", 1.f), Uniform("textColor", 0.f, 0.f, 0.f) }))
		->addComponent(new ScoreComponent()));

	addSystem(new OnWaitFinishedSystem(12));
	addSystem(new ParticleSystem());
	addSystem(new AnimationSystem(10));
	addSystem(new RenderSystem(0));
}