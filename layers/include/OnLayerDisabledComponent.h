#pragma once

#include "Component.h"
#include "Entity.h"

class OnLayerDisabledComponent : public BaseComponent<OnLayerDisabledComponent>
{
public:
	OnLayerDisabledComponent(void(*function)(Entity* entity), ClassId layer = 0) : function(function), layer(layer) {}
	void(*function)(Entity* entity);
	ClassId layer;
};