#pragma once

#include "Entity.h"

#include <vector>
#include <utility>

class Layer;

class System
{
public:
	System(int updatePriority) 
	{
		priority = updatePriority;
		layer = nullptr;
	}
	virtual void update(std::vector<Entity*> entities) = 0;
	int getPriority() { return priority; }
	Layer* getLayer() { return layer; }
protected:
	int priority;
private:
	void setLayer(Layer* l) { layer = l; }
	Layer* layer;

	friend Layer;
};