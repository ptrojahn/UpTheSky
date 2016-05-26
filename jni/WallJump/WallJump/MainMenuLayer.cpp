#include "MainMenuLayer.h"

#include "RenderComponent.h"
#include "TransformComponent.h"
#include "RenderSystem.h"
#include "ButtonSystem.h"
#include "ButtonComponent.h"
#include "TextureComponent.h"
#include "UniformsComponent.h"
#include "ScoreComponent.h"
#include "HighScoreComponent.h"
#include "HighScoreUpdateSystem.h"
#include "GameLayer.h"
#include "PlayerLayer.h"
#include "Player.h"
#include "AnimationComponent.h"

void startGame(Entity* button, float direction) {
	for (Entity* entity : button->getLayer()->getEngine()->getEntities()){
		PlayerComponent* playerComponent = entity->getComponent<PlayerComponent>();
		if (playerComponent){
			playerComponent->velocity = Vector2<float>(PlayerSystem::jumpVelocity.x * direction, PlayerSystem::jumpVelocity.y);

			entity->addComponent(new AnimationComponent({
				AnimationState({ AnimationChange(&entity->getComponent<TransformComponent>()->scale.x, 2.f, 1.f),
				                 AnimationChange(&entity->getComponent<TransformComponent>()->scale.y, 2.f, 1.f),
								 AnimationChange(&entity->getComponent<TransformComponent>()->position.x, 0.5, 1),
								 AnimationChange(&entity->getComponent<TransformComponent>()->position.y, 1, 2)
				},0.25f),
			}, AnimationComponent::Once));
		}
	}
	for (Entity* entity : button->getLayer()->getEngine()->getEntities()){
		if (entity->getComponent<ScoreComponent>()){
			UniformsComponent* uniforms = entity->getComponent<UniformsComponent>();
			(*(int*)&uniforms->uniforms[0].data[0]) = 0;
			*(int*)&uniforms->uniforms[1].data[0] = 1;
			break;
		}
	}
	for (Entity* highScore : button->getLayer()->getEngine()->getEntities()){
		HighScoreComponent* highScoreComponent = highScore->getComponent<HighScoreComponent>();
		if (highScoreComponent){
			highScoreComponent->updated = false;
			break;
		}
	}
	button->getLayer()->getEngine()->getLayer<GameLayer>()->enable();
	button->getLayer()->disable();
}

void jumpLeft(Entity* button) {
	startGame(button, -1);
}

void jumpRight(Entity* button) {
	startGame(button, 1);
}

void MainMenuLayer::load() {
	addEntity((new Entity(0))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("mainMenuButton.vert", "mainMenuButton.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 2, 2))))
		->addComponent(new TransformComponent(Vector2<float>(0.2, 13.8))));
	addEntity((new Entity(0))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("mainMenuButton.vert", "mainMenuButton.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 2, 2))))
		->addComponent(new TransformComponent(Vector2<float>(2.4, 13.8))));
	addEntity((new Entity(0))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("mainMenuButton.vert", "mainMenuButton.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 2, 2))))
		->addComponent(new TransformComponent(Vector2<float>(4.6, 13.8))));
	addEntity((new Entity(0))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("mainMenuButton.vert", "mainMenuButton.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 2, 2))))
		->addComponent(new TransformComponent(Vector2<float>(6.8, 13.8))));
	addEntity((new Entity(0))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("score.vert", "score.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(-0.3125, -0.5, 0.625, 1))))
		->addComponent(new TransformComponent(Vector2<float>(4.5, 4)))
		->addComponent(new TextureComponent("numbers.bmp", GL_NEAREST))
		->addComponent(new UniformsComponent({ Uniform("score", 0), Uniform("length", 1) }))
		->addComponent(new HighScoreComponent()));

	addEntity((new Entity(0))
		->addComponent(new TransformComponent())
		->addComponent(new ButtonComponent(Vector2<float>(getEngine()->getLogicalScreenSize().x / 2.f, getEngine()->getLogicalScreenSize().y - 2), &jumpLeft)));
	addEntity((new Entity(0))
		->addComponent(new TransformComponent(Vector2<float>(getEngine()->getLogicalScreenSize().x / 2.f, 0)))
		->addComponent(new ButtonComponent(Vector2<float>(getEngine()->getLogicalScreenSize().x / 2.f, getEngine()->getLogicalScreenSize().y - 2), &jumpRight)));

	addSystem(new HighScoreUpdateSystem());
	addSystem(new ButtonSystem(1));
	addSystem(new RenderSystem(0));
}