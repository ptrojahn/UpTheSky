#include "OnUpdateSystem.h"

#include "OnUpdateComponent.h"

void OnUpdateSystem::update(LayersEngine& engine) {
	for (Entity* entity : engine.getEntities()){
		OnUpdateComponent* component = entity->getComponent<OnUpdateComponent>();
		if (component)
			component->function(entity);
	}
}