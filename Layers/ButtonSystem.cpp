#include "ButtonSystem.h"

#include "ButtonComponent.h"
#include "TransformComponent.h"

#include <SDL.h>

void ButtonSystem::update(SceneData& data) {
	for (Entity* entity : data.entities){
		ButtonComponent* buttonComponent = entity->getComponent<ButtonComponent>();
		if (buttonComponent){
			Vector2<int> mousePosPhys;
			if (SDL_GetMouseState(&mousePosPhys.x, &mousePosPhys.y) == SDL_BUTTON(SDL_BUTTON_LEFT)){
				float width = (float)data.logicalScreenSize.x / (float)data.logicalScreenSize.y > (float)data.physicalScreenSize.x / (float)data.physicalScreenSize.y ?
					(float)data.physicalScreenSize.x : (float)data.logicalScreenSize.x / (float)data.logicalScreenSize.y * (float)data.physicalScreenSize.y;
				float height = (float)data.logicalScreenSize.x / (float)data.logicalScreenSize.y > (float)data.physicalScreenSize.x > (float)data.physicalScreenSize.y ?
					(float)data.logicalScreenSize.y / (float)data.logicalScreenSize.x * (float)data.physicalScreenSize.x : (float)data.physicalScreenSize.y;
				Vector2<float> mousePosition = (Vector2<float>(mousePosPhys.x, mousePosPhys.y) - Vector2<float>((data.physicalScreenSize.x - width) / 2, (data.physicalScreenSize.y - height) / 2)) / Vector2<float>(width, height) * Vector2<float>(data.logicalScreenSize.x, data.logicalScreenSize.y);
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