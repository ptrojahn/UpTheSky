#include "Scroll.h"

#include "Player.h"
#include "TransformComponent.h"

void ScrollSystem::update(LayersEngine& engine) {
	Vector2<float> playerPosition;
	for (Entity* entity : engine.getEntities()){
		if (entity->getComponent<PlayerComponent>()){
			playerPosition = entity->getComponent<TransformComponent>()->position;
			break;
		}
	}
	if (playerPosition.y < 6){
		for (Entity* entity : engine.getEntities()){
			if (entity->getComponent<ScrollComponent>()){
				entity->getComponent<TransformComponent>()->position.y += 6 - playerPosition.y;
			}
		}
	}
}