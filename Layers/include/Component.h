#pragma once

#include "ClassId.h"

class Component
{
public:
	Component(ClassId id) : id(id){
	}
	virtual ~Component() {}
	ClassId getId() { return id; }
private:
	ClassId id;
};

//Base class that takes care of the component type initialisation 
template<typename TComponent>
class BaseComponent : public Component
{
public:
	BaseComponent() : Component(classId<TComponent>()){}
};