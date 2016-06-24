#include "ButtonSystem.h"

#include "ButtonComponent.h"
#include "TransformComponent.h"

#include <SDL.h>

namespace{
	bool pressed = false;
}

void ButtonSystem::update(LayersEngine& engine) {
	for (Entity* entity : engine.getEntities()){
		ButtonComponent* buttonComponent = entity->getComponent<ButtonComponent>();
		if (buttonComponent){
			Vector2<int> mousePosPhys;
			if (engine.isTouchActive()){
				TransformComponent* transformComponent = entity->getComponent<TransformComponent>();
				if (engine.getTouchPosition().x > transformComponent->position.x && engine.getTouchPosition().x < transformComponent->position.x + buttonComponent->size.x
					&& engine.getTouchPosition().y > transformComponent->position.y && engine.getTouchPosition().y < transformComponent->position.y + buttonComponent->size.y
					&& !pressed){
					buttonComponent->onClick(entity);
					pressed = true;
					return;
				}
			} else
				pressed = false;
		}
	}
}