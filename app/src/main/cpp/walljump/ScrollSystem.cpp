#include "ScrollSystem.h"

#include "PlayerComponent.h"
#include "TransformComponent.h"
#include "ScrollComponent.h"

void ScrollSystem::update(LayersEngine& engine) {
	for (Entity* player : engine.getEntities()){
		if (player->getComponent<PlayerComponent>()){
			if (player->getComponent<TransformComponent>()->position.y < 6){
				for (Entity* entity : engine.getEntities()){
					ScrollComponent* scrollComponent = entity->getComponent<ScrollComponent>();
					if (scrollComponent){
						entity->getComponent<TransformComponent>()->position.y += (6 - player->getComponent<TransformComponent>()->position.y) * scrollComponent->factor;
					}
				}
			}
			break;
		}
	}
	
}