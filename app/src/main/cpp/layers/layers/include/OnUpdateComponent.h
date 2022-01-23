#pragma once

#include "Component.h"
#include "Entity.h"

class OnUpdateComponent : public BaseComponent<OnUpdateComponent>
{
public:
	OnUpdateComponent(void(*function)(Entity* entity), Entity* entity = nullptr) : function(function) {}
	void(*function)(Entity* entity);
};