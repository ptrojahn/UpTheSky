#include "ButtonSystem.h"

#include "ButtonComponent.h"
#include "TransformComponent.h"

#include <SDL.h>

void ButtonSystem::update(LayersEngine& engine) {
	for (Entity* entity : engine.getEntities()){
		ButtonComponent* buttonComponent = entity->getComponent<ButtonComponent>();
		if (buttonComponent){
			Vector2<int> mousePosPhys;
			if (engine.getTouchActive()){
				TransformComponent* transformComponent = entity->getComponent<TransformComponent>();
				if (transformComponent->position.x > engine.getTouchPosition().x - buttonComponent->size.x / 2 && transformComponent->position.x < engine.getTouchPosition().x + buttonComponent->size.x / 2
					&& transformComponent->position.y > engine.getTouchPosition().y - buttonComponent->size.y / 2 && transformComponent->position.y < engine.getTouchPosition().y + buttonComponent->size.y / 2
					&& !buttonComponent->pressed){
					buttonComponent->onClick(entity);
					buttonComponent->pressed = true;
				}
			} else
				buttonComponent->pressed = false;
		}
	}
}