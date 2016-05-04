#include "Scroll.h"

#include "Player.h"
#include "TransformComponent.h"

void ScrollSystem::update(LayersEngine& engine) {
	for (Entity* player : engine.getEntities()){
		if (player->getComponent<PlayerComponent>()){
			if (player->getComponent<TransformComponent>()->position.y < 6){
				for (Entity* entity : engine.getEntities()){
					if (entity->getComponent<ScrollComponent>()){
						entity->getComponent<TransformComponent>()->position.y += 6 - player->getComponent<TransformComponent>()->position.y;
					}
				}
			}
			break;
		}
	}
	
}