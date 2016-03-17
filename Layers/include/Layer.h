#pragma once

#include "System.h"
#include "Entity.h"
#include "SceneData.h"

#include <vector>

class Layer
{
public:
	Layer(bool startEnabled);
	bool isEnabled() { return enabled; }
	void update();
protected:
	void addSystem(System* system);
	void addEntity(Entity* entity);
	virtual void load() = 0;
private:
	void setSceneData(SceneData* sceneData) { data = sceneData; }
	SceneData* data;
	bool enabled;

	friend class LayersEngine;
};