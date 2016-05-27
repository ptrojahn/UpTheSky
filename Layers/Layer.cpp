#include "Layer.h"

#include "System.h"
#include "OnLayerEnabledComponent.h"
#include "OnLayerDisabledComponent.h"

void Layer::addSystem(System* system) {
	system->setLayer(this);
	engine->addSystem(system);
}

void Layer::addEntity(Entity* entity) {
	entity->setLayer(this);
	engine->addEntity(entity);
}

std::vector<Entity*>::iterator Layer::deleteEntity(Entity* entity) {
	return engine->deleteEntity(entity);
}

void Layer::update() {
	
}

void Layer::enable() {
	if (!enabled){
		enabled = true;
		engine->activeEntitiesChanged();
		engine->activeSystemsChanged();
		for (Entity* entity : engine->getEntities()){
			OnLayerEnabledComponent* component = entity->getComponent<OnLayerEnabledComponent>();
			if (component && (component->layer == id || (component->layer == 0 && component->layer == entity->getLayer()->getId()))){
				component->function(entity);
			}
		}
	}
}

void Layer::disable() {
	if (enabled){
		enabled = false;
		engine->activeEntitiesChanged();
		engine->activeSystemsChanged();
		for (Entity* entity : engine->getEntities()){
			OnLayerDisabledComponent* component = entity->getComponent<OnLayerDisabledComponent>();
			if (component && (component->layer == id || (component->layer == 0 && component->layer == entity->getLayer()->getId()))){
				component->function(entity);
			}
		}
	}
}