#pragma once

#include "Component.h"
#include "Entity.h"

class OnLayerEnabledComponent : public BaseComponent<OnLayerEnabledComponent>
{
public:
	OnLayerEnabledComponent(void(*function)(Entity* entity), ClassId layer = 0) : function(function), layer(layer) {}
	void(*function)(Entity* entity);
	ClassId layer;
};