#pragma once

#include "Component.h"

#include <vector>

class Layer;

class Entity
{
public:
	Entity(int updatePriority);
	int getPriority() { return priority; }
	Entity* addComponent(Component* component);
	Layer* getLayer() { return layer; }

	template<typename TComponent>
	TComponent* getComponent() {
		for (Component* component : components){
			if (component->getType() == getComponentType<TComponent>())
				return dynamic_cast<TComponent*>(component);
		}
		return nullptr;
	}
private:
	void setLayer(Layer* l) { layer = l; }
	Layer* layer;
	int priority;
	std::vector<Component*> components;

	friend Layer;
};