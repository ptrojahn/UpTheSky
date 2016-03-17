#include "Layer.h"

Layer::Layer(bool isEnabled) {
	enabled = isEnabled;
}

void Layer::addSystem(System* system) {
	for (std::vector<System*>::iterator iterSystems = data->systems.begin(); iterSystems != data->systems.end(); iterSystems++){
		if ((*iterSystems)->getPriority() < system->getPriority()){
			data->systems.insert(iterSystems, system);
			system->setLayer(this);
			return;
		}
	}
	data->systems.push_back(system);
	system->setLayer(this);
}

void Layer::addEntity(Entity* entity) {
	for (std::vector<Entity*>::iterator iterEntities = data->entities.begin(); iterEntities != data->entities.end(); iterEntities++){
		if ((*iterEntities)->getPriority() < entity->getPriority()){
			data->entities.insert(iterEntities, entity);
			entity->setLayer(this);
			return;
		}
	}
	data->entities.push_back(entity);
	entity->setLayer(this);
}

void Layer::update() {
	
}