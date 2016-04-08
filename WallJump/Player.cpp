#include "Player.h"

#include "TransformComponent.h"

void PlayerSystem::update(LayersEngine& engine) {
	for (Entity* entity : engine.getEntities()){
		PlayerComponent* playerComponent = entity->getComponent<PlayerComponent>();
		if (playerComponent){
			TransformComponent* transformComponent = entity->getComponent<TransformComponent>();

			if (engine.isTouchActive()){
				playerComponent->acceleration.x = engine.getTouchPosition().x > engine.getLogicalScreenSize().x / 2
					? 8.f : -8.f;
				playerComponent->acceleration.y = -10;
			}

			playerComponent->acceleration += Vector2<float>(0, 25 * engine.getDeltaTime());
			transformComponent->position += playerComponent->acceleration * engine.getDeltaTime();
		}
	}
}