#pragma once

#include "include\Entity.h"

Entity::Entity(int updatePriority) {
	priority = updatePriority;
	layer = nullptr;
}

void Entity::addComponent(Component* component) {
	components.push_back(component);
}