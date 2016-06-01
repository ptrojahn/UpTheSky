#include "Player.h"

#include "TransformComponent.h"
#include "StaticColliderComponent.h"
#include "LethalTriggerComponent.h"
#include "PlayerLayer.h"
#include "LevelManager.h"
#include "Scroll.h"
#include "RenderComponent.h"
#include "GameLayer.h"
#include "MainMenuLayerLogic.h"
#include "Layer.h"
#include "helper.h"

const Vector2<float> PlayerSystem::playerSize = Vector2<float>(1, 2);
const Vector2<float> PlayerSystem::jumpVelocity = Vector2<float>(8, -13);
const float PlayerSystem::gravity = 25;

int getJumpBlock(std::vector<Entity*> entities, Vector2<float> playerPosition, Vector2<float> playerSize) {
	for (Entity* entity : entities){
		StaticColliderComponent* colliderComponent = entity->getComponent<StaticColliderComponent>();
		if (colliderComponent){
			Vector2<float> colliderPosition = entity->getComponent<TransformComponent>()->position;
			Vector2<float> colliderSize = colliderComponent->size * entity->getComponent<TransformComponent>()->scale;
			if (colliderPosition.x - playerPosition.x - playerSize.x == 0
				&& playerPosition.y + playerSize.y > colliderPosition.y
				&& playerPosition.y < colliderPosition.y + colliderSize.y){
				return 1;
			} else if (playerPosition.x - colliderPosition.x - colliderSize.x == 0
				&& playerPosition.y + playerSize.y > colliderPosition.y
				&& playerPosition.y < colliderPosition.y + colliderSize.y){
				return -1;
			}
		}
	}
	return 0;
}

void PlayerSystem::update(LayersEngine& engine) {
	for (Entity* playerEntity : engine.getEntities()){
		PlayerComponent* playerComponent = playerEntity->getComponent<PlayerComponent>();
		if (playerComponent){
			TransformComponent* transformComponent = playerEntity->getComponent<TransformComponent>();
			int jumpBlock = getJumpBlock(engine.getEntities(), transformComponent->position, playerSize);
			//Only increase x velocity if the direction is not blocked by a wall. This is needed to avoid glitches on collider corners 
			if (engine.isTouchActive() && !playerComponent->lastFramePressed && jumpBlock){
				if (jumpBlock != copysign(1.0, engine.getTouchPosition().x - engine.getLogicalScreenSize().x / 2))
					playerComponent->velocity.x = copysign(1.0, engine.getTouchPosition().x - engine.getLogicalScreenSize().x / 2) * jumpVelocity.x;
				playerComponent->velocity.y = jumpVelocity.y;
			}
			playerComponent->lastFramePressed = engine.isTouchActive();
			playerComponent->velocity += Vector2<float>(0, gravity * engine.getDeltaTime());

			//Collision handling. The position needs to be set explicitly to avoid float precision problems
			Vector2<float> velocityFactor = Vector2<float>(1, 1);
			Vector2<float> futurePosition = transformComponent->position + playerComponent->velocity * engine.getDeltaTime();
			for (Entity* entity : engine.getEntities()){
				StaticColliderComponent* colliderComponent = entity->getComponent<StaticColliderComponent>();
				if (colliderComponent){
					TransformComponent* colliderTransformComponent = entity->getComponent<TransformComponent>();
					Vector2<float> colliderSize = colliderComponent->size * colliderTransformComponent->scale;
					if (intersect(futurePosition, playerSize, colliderTransformComponent->position, colliderSize)){
						if (transformComponent->position.x + playerSize.x <= colliderTransformComponent->position.x && playerComponent->velocity.x > 0){
							transformComponent->position.x = colliderTransformComponent->position.x - playerSize.x;
							playerComponent->velocity.x = 0;
							velocityFactor.x = 0;
						} else if (transformComponent->position.x >= colliderTransformComponent->position.x + colliderSize.x && playerComponent->velocity.x < 0){
							transformComponent->position.x = colliderTransformComponent->position.x + colliderSize.x;
							playerComponent->velocity.x = 0;
							velocityFactor.x = 0;
						} else if (transformComponent->position.y >= colliderTransformComponent->position.y + colliderComponent->size.y && playerComponent->velocity.y < 0){
							transformComponent->position.y = colliderTransformComponent->position.y + colliderComponent->size.y;
							playerComponent->velocity.y = 0;
							velocityFactor.y = 0;
						} else if (transformComponent->position.y + playerSize.y <= colliderTransformComponent->position.y && playerComponent->velocity.y > 0){
							transformComponent->position.y = colliderTransformComponent->position.y - playerSize.y;
							playerComponent->velocity.y = 0;
							velocityFactor.y = 0;
						}
					}
				}
			}
			transformComponent->position += playerComponent->velocity * velocityFactor * engine.getDeltaTime();

			for (Entity* entity : engine.getEntities()){
				LethalTriggerComponent* triggerComponent = entity->getComponent<LethalTriggerComponent>();
				if (triggerComponent){
					TransformComponent* triggerTransformComponent = entity->getComponent<TransformComponent>();
					Vector2<float> triggerSize = triggerComponent->size * triggerTransformComponent->scale;
					if (intersect(transformComponent->position, playerSize, triggerTransformComponent->position, triggerSize)){
						onPlayerDeath(playerEntity);
						break;
					}
				}
			}
			break;
		}
	}
}

std::vector<Entity*>::iterator PlayerSystem::onPlayerDeath(Entity* player) {
	player->getLayer()->getEngine()->getLayer<GameLayer>()->disable();
	player->getLayer()->getEngine()->getLayer<MainMenuLayerLogic>()->enable();

	//Reset game layer
	for (std::vector<Entity*>::iterator entityIter = player->getLayer()->getEngine()->getEntities().begin(); entityIter != player->getLayer()->getEngine()->getEntities().end();){
		if ((*entityIter)->getLayer()->isClass<GameLayer>() && (*entityIter)->getComponent<ScrollComponent>())
			entityIter = player->getLayer()->deleteEntity((*entityIter));
		else 
			entityIter++;
	}
	player->getLayer()->getEngine()->getLayer<GameLayer>()->addEntity((new Entity(400))
		->addComponent(new LevelManagerHelperComponent())
		->addComponent(new TransformComponent(Vector2<float>(0, 2)))
		->addComponent(new ScrollComponent()));

	//Reset the player
	player->getLayer()->addEntity((new Entity(100))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("player.vert", "player.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2D(0, 0, 1, 2))))
		->addComponent(new TransformComponent(Vector2<float>(player->getLayer()->getEngine()->getLogicalScreenSize().x / 2.f - 1, player->getLayer()->getEngine()->getLogicalScreenSize().y / 2.f - 2), 0, Vector2<float>(2.f, 2.f)))
		->addComponent(new PlayerComponent())
		->addComponent(new ScrollComponent()));
	return player->getLayer()->deleteEntity(player);
}