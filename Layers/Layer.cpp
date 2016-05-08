#include "Layer.h"

#include "System.h"

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
	}
}

void Layer::disable() {
	if (enabled){
		enabled = false;
		engine->activeEntitiesChanged();
		engine->activeSystemsChanged();
	}
}