#pragma once

#include "System.h"
#include "Entity.h"

#include <vector>

class LayersEngine;

class Layer
{
public:
	Layer(bool startEnabled);
	bool isEnabled() { return enabled; }
	void addSystem(System* system);
	void addEntity(Entity* entity);
	std::vector<Entity*>::iterator deleteEntity(Entity* entity);
protected:
	virtual void load() = 0;
private:
	void setEngine(LayersEngine* layersEngine) { engine = layersEngine; }
	virtual void update();
	LayersEngine* engine;
	bool enabled;

	friend class LayersEngine;
};