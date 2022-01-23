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

std::vector<Component*>::iterator Entity::deleteComponent(Component* component) {
	delete component;
	for (std::vector<Component*>::iterator iterComponent = components.begin(); iterComponent != components.end(); iterComponent++)
		if (*iterComponent == component)
			return components.erase(iterComponent);
	return components.end();
}

std::vector<Component*>& Entity::getComponents(){
	return components;
}