#include "Layer.h"

Layer::Layer(bool startEnabled) {
	enabled = startEnabled;
}

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
		engine->updateActiveEntities();
		engine->updateActiveSystems();
	}
}

void Layer::disable() {
	if (enabled){
		enabled = false;
		engine->updateActiveEntities();
		engine->updateActiveSystems();
	}
}