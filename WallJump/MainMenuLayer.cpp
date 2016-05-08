#include "MainMenuLayer.h"

#include "RenderComponent.h"
#include "TransformComponent.h"
#include "RenderSystem.h"
#include "ButtonSystem.h"
#include "ButtonComponent.h"
#include "GameLayer.h"
#include "Player.h"

void jumpLeft(Entity* button) {
	for (Entity* entity : button->getLayer()->getEngine()->getEntities()){
		PlayerComponent* playerComponent = entity->getComponent<PlayerComponent>();
		if (playerComponent){
			playerComponent->velocity = Vector2<float>(PlayerSystem::jumpVelocity.x * -1, PlayerSystem::jumpVelocity.y);
		}
	}
	button->getLayer()->getEngine()->getLayer<GameLayer>()->enable();
	button->getLayer()->disable();
}

void jumpRight(Entity* button) {
	for (Entity* entity : button->getLayer()->getEngine()->getEntities()){
		PlayerComponent* playerComponent = entity->getComponent<PlayerComponent>();
		if (playerComponent){
			playerComponent->velocity = PlayerSystem::jumpVelocity;
		}
	}
	button->getLayer()->getEngine()->getLayer<GameLayer>()->enable();
	button->getLayer()->disable();
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
		->addComponent(new TransformComponent())
		->addComponent(new ButtonComponent(Vector2<float>(getEngine()->getLogicalScreenSize().x / 2, getEngine()->getLogicalScreenSize().y - 2), &jumpLeft)));
	addEntity((new Entity(0))
		->addComponent(new TransformComponent(Vector2<float>(getEngine()->getLogicalScreenSize().x / 2, 0)))
		->addComponent(new ButtonComponent(Vector2<float>(getEngine()->getLogicalScreenSize().x / 2, getEngine()->getLogicalScreenSize().y - 2), &jumpRight)));

	addSystem(new ButtonSystem(1));
	addSystem(new RenderSystem(0));
}