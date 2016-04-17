#include "Layer.h"

Layer::Layer(bool isEnabled) {
	enabled = isEnabled;
}

void Layer::addSystem(System* system) {
	for (std::vector<System*>::iterator iterSystems = engine->getSystems().begin(); iterSystems != engine->getSystems().end(); iterSystems++){
		if ((*iterSystems)->getPriority() < system->getPriority()){
			engine->getSystems().insert(iterSystems, system);
			system->setLayer(this);
			return;
		}
	}
	engine->getSystems().push_back(system);
	system->setLayer(this);
}

void Layer::addEntity(Entity* entity) {
	for (std::vector<Entity*>::iterator iterEntities = engine->getEntities().begin(); iterEntities != engine->getEntities().end(); iterEntities++){
		if ((*iterEntities)->getPriority() < entity->getPriority()){
			engine->getEntities().insert(iterEntities, entity);
			entity->setLayer(this);
			return;
		}
	}
	engine->getEntities().push_back(entity);
	entity->setLayer(this);
}

std::vector<Entity*>::iterator Layer::deleteEntity(Entity* entity) {
	for (std::vector<Entity*>::iterator iterEntities = engine->getEntities().begin(); iterEntities != engine->getEntities().end(); iterEntities++){
		if ((*iterEntities) == entity){
			delete entity;
			return engine->getEntities().erase(iterEntities);
		}
	}
	return engine->getEntities().end();
}

void Layer::update() {
	
}