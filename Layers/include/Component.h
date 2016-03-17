#pragma once

typedef unsigned int ComponentType;

//Base class that takes care of the component type initialisation 
template<typename TComponent>
class BaseComponent : public Component
{
public:
	BaseComponent() : Component(getComponentType<TComponent>()){
	}
};

class Component
{
public:
	Component(ComponentType compType) {
		type = compType;
	}
	virtual ~Component() {}
	ComponentType getType() { return type; }
private:
	ComponentType type;
};

//Creates a unique id for every component class
template<typename TComponent>
static unsigned int getComponentType() {
	return ComponentTypeManager::getId<TComponent>();
}

class ComponentTypeManager{
public:
	template<class TComponent>
	static unsigned int getId() {
		static unsigned int id = nextComponentID++;
		return id;
	}
private:
	static ComponentType nextComponentID;
};