#pragma once

#include "Component.h"

#include <vector>

class Layer;

class Entity
{
public:
	Entity(int updatePriority);
	~Entity();
	int getPriority() { return priority; }
	Entity* addComponent(Component* component);
	std::vector<Component*>::iterator deleteComponent(Component* component);
	Layer* getLayer() { return layer; }
	std::vector<Component*>& getComponents();

	template<typename TComponent>
	TComponent* getComponent() {
		for (Component* component : components){
			if (component->getId() == classId<TComponent>())
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