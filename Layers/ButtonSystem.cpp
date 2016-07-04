#include "ButtonSystem.h"

#include "ButtonComponent.h"
#include "TransformComponent.h"

#include <SDL.h>

namespace{
	bool pressed = false;
	Vector2<float> startPos;
}

void ButtonSystem::update(LayersEngine& engine) {
	if (engine.isTouchActive() && !pressed){
		pressed = true;
		startPos = engine.getTouchPosition();
	} else if (!engine.isTouchActive() && pressed){
		pressed = false;
		for (Entity* entity : engine.getEntities()){
			ButtonComponent* buttonComponent = entity->getComponent<ButtonComponent>();
			if (buttonComponent){
				Vector2<float> position = entity->getComponent<TransformComponent>()->position;
				if (engine.getTouchPosition().x > position.x && engine.getTouchPosition().x < position.x + buttonComponent->size.x
					&& engine.getTouchPosition().y > position.y && engine.getTouchPosition().y < position.y + buttonComponent->size.y
					&& sqrt(pow(engine.getTouchPosition().x - startPos.x, 2) + pow(engine.getTouchPosition().y - startPos.y, 2)) < 0.25){
					buttonComponent->onClick(entity);
					return;
				}
			}
		}
	}
}