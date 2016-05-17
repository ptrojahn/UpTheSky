#include "Entity.h"

Entity::Entity(int updatePriority) {
	priority = updatePriority;
	layer = nullptr;
}

Entity::~Entity() {
	for (Component* component : components){
		delete component;
	}
}

Entity* Entity::addComponent(Component* component) {
	components.push_back(component);
	return this;
}