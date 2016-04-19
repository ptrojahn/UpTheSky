#include "Player.h"

#include "TransformComponent.h"
#include "StaticColliderComponent.h"
#include "LevelManager.h"
#include "Layer.h"

bool intersect(Vector2<float> pos1, Vector2<float> size1, Vector2<float> pos2, Vector2<float> size2) {
	return pos1.x < pos2.x + size2.x
		&& pos1.x + size1.x > pos2.x
		&& pos1.y < pos2.y + size2.y
		&& pos1.y + size1.y > pos2.y;
}

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
			Vector2<float> playerSize = Vector2<float>(1, 2);
			int jumpBlock = getJumpBlock(engine.getEntities(), transformComponent->position, playerSize);
			//Only increase x velocity if the direction is not blocked by a wall. This is needed to avoid glitches on collider corners 
			if (engine.isTouchActive() && !playerComponent->lastFramePressed && jumpBlock){
				if (jumpBlock != copysign(1.0, engine.getTouchPosition().x - engine.getLogicalScreenSize().x / 2))
					playerComponent->velocity.x = copysign(1.0, engine.getTouchPosition().x - engine.getLogicalScreenSize().x / 2) * 8.f;
				playerComponent->velocity.y = -12;
			}
			playerComponent->lastFramePressed = engine.isTouchActive();
			playerComponent->velocity += Vector2<float>(0, 25 * engine.getDeltaTime());

			//Collision handling. The position needs to be set explicitly to avoid float precission problems
			Vector2<float> velocityFactor = Vector2<float>(1, 1);
			Vector2<float> futurePosition = transformComponent->position + playerComponent->velocity * engine.getDeltaTime();
			for (Entity* entity : engine.getEntities()){
				StaticColliderComponent* colliderComponent = entity->getComponent<StaticColliderComponent>();
				if (colliderComponent){
					TransformComponent* colliderTransformComponent = entity->getComponent<TransformComponent>();
					Vector2<float> colliderSize = colliderComponent->size * colliderTransformComponent->scale;
					if (intersect(futurePosition, playerSize, colliderTransformComponent->position, colliderSize)){
						if (colliderTransformComponent->position.x - transformComponent->position.x - playerSize.x >= 0 && playerComponent->velocity.x > 0){
							transformComponent->position.x = colliderTransformComponent->position.x - playerSize.x;
							playerComponent->velocity.x = 0;
							velocityFactor.x = 0;
						} else if (transformComponent->position.x - colliderTransformComponent->position.x - colliderSize.x >= 0 && playerComponent->velocity.x < 0){
							transformComponent->position.x = colliderTransformComponent->position.x + colliderSize.x;
							playerComponent->velocity.x = 0;
							velocityFactor.x = 0;
						} else if (transformComponent->position.y - colliderTransformComponent->position.y - colliderComponent->size.y >= 0 && playerComponent->velocity.y < 0){
							transformComponent->position.y = colliderTransformComponent->position.y + colliderComponent->size.y;
							playerComponent->velocity.y = 0;
							velocityFactor.y = 0;
						} else if (colliderTransformComponent->position.y - transformComponent->position.y - playerSize.y >= 0 && playerComponent->velocity.y > 0){
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
						playerEntity->getLayer()->disable();
						break;
					}
				}
			}
			break;
		}
	}
}