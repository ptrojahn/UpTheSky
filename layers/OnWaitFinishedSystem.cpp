#include "OnWaitFinishedSystem.h"

#include "OnWaitFinishedComponent.h"

#include <SDL.h>

void OnWaitFinishedSystem::update(LayersEngine& engine) {
	bool done = true;
	do{
		done = true;
		for (Entity* entity : engine.getEntities()){
			OnWaitFinishedComponent* component = entity->getComponent<OnWaitFinishedComponent>();
			if (component && component->startTime + component->millisecs < SDL_GetTicks()){
				void(*function)(Entity* entity) = component->function;;
				entity->deleteComponent(component);
				function(entity);
				done = false;
				break;
			}
		}
	} while (!done);
}