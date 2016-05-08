#pragma once

#include "Entity.h"
#include "ClassId.h"

#include <vector>

class LayersEngine;
class System;

class Layer
{
public:
	Layer(ClassId id, bool enabled) : id(id), enabled(enabled) {}
	bool isEnabled() { return enabled; }
	LayersEngine* getEngine() { return engine; }
	void enable();
	void disable();
	void addSystem(System* system);
	void addEntity(Entity* entity);
	std::vector<Entity*>::iterator deleteEntity(Entity* entity);
	template<class TLayer> bool isClass() { return classId<TLayer>() == id; }
protected:
	virtual void load() = 0;
private:
	virtual void update();
	LayersEngine* engine;
	bool enabled;
	ClassId id;

	friend class LayersEngine;
	void setEngine(LayersEngine* layersEngine) { engine = layersEngine; }
};

template<class TLayer>
class BaseLayer : public Layer
{
public:
	BaseLayer(bool enabled) : Layer(classId<TLayer>(), enabled) {}
};