#include "ButtonSystem.h"

#include "ButtonComponent.h"
#include "TransformComponent.h"

#include <SDL.h>

void ButtonSystem::update(LayersEngine& engine) {
	for (Entity* entity : engine.getEntities()){
		ButtonComponent* buttonComponent = entity->getComponent<ButtonComponent>();
		if (buttonComponent){
			Vector2<int> mousePosPhys;
			if (SDL_GetMouseState(&mousePosPhys.x, &mousePosPhys.y) == SDL_BUTTON(SDL_BUTTON_LEFT)){
				float width = (float)engine.getLogicalScreenSize().x / (float)engine.getLogicalScreenSize().y > (float)engine.getPhysicalScreenSize().x / (float)engine.getPhysicalScreenSize().y ?
					(float)engine.getPhysicalScreenSize().x : (float)engine.getLogicalScreenSize().x / (float)engine.getLogicalScreenSize().y * (float)engine.getPhysicalScreenSize().y;
				float height = (float)engine.getLogicalScreenSize().x / (float)engine.getLogicalScreenSize().y > (float)engine.getPhysicalScreenSize().x > (float)engine.getPhysicalScreenSize().y ?
					(float)engine.getLogicalScreenSize().y / (float)engine.getLogicalScreenSize().x * (float)engine.getPhysicalScreenSize().x : (float)engine.getPhysicalScreenSize().y;
				Vector2<float> mousePosition = (Vector2<float>(mousePosPhys.x, mousePosPhys.y) - Vector2<float>((engine.getPhysicalScreenSize().x - width) / 2, (engine.getPhysicalScreenSize().y - height) / 2)) / Vector2<float>(width, height) * Vector2<float>(engine.getLogicalScreenSize().x, engine.getLogicalScreenSize().y);
				TransformComponent* transformComponent = entity->getComponent<TransformComponent>();
				if (transformComponent->position.x > mousePosition.x - buttonComponent->size.x / 2 && transformComponent->position.x < mousePosition.x + buttonComponent->size.x / 2
					&& transformComponent->position.y > mousePosition.y - buttonComponent->size.y / 2 && transformComponent->position.y < mousePosition.y + buttonComponent->size.y / 2
					&& !buttonComponent->pressed){
					buttonComponent->onClick(entity);
					buttonComponent->pressed = true;
				}
			} else
				buttonComponent->pressed = false;
		}
	}
}