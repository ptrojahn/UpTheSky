#pragma once

#include "Vector2.h"
#include "Matrix4x4.h"
#include "Entity.h"

#include <SDL.h>

#include <vector>

class Layer;
class System;

class LayersEngine
{
public:
	LayersEngine(int aspectX, int aspectY);
	void addLayer(Layer* layer);
	std::vector<Layer*>& getLayers() { return layers; }
	std::vector<Entity*>& getEntities() { return activeEntities; }
	std::vector<System*>& getSystems() { return activeSystems; }
	float getDeltaTime() { return deltaTime; }
	Vector2<int> getLogicalScreenSize() { return logicalScreenSize; }
	Vector2<int> getPhysicalScreenSize() { return physicalScreenSize; }
	Matrix4x4 getProjectionMatrix() { return projectionMatrix; }
	bool isTouchActive() { return touchActive; }
	Vector2<float> getTouchPosition() { return touchPosition; }
	void updateActiveEntities();
	void updateActiveSystems();
	void run();
private:
	SDL_Window* window;
	std::vector<Layer*> layers;
	std::vector<Entity*> entities;
	std::vector<Entity*> activeEntities;
	std::vector<System*> systems;
	std::vector<System*> activeSystems;
	float deltaTime;
	Vector2<float> touchPosition;
	bool touchActive;
	Vector2<int> logicalScreenSize;
	Vector2<int> physicalScreenSize;
	Matrix4x4 projectionMatrix;
	uint32_t lastTick;

	friend class Layer;
	void addEntity(Entity* entity);
	void addSystem(System* system);
	std::vector<Entity*>::iterator deleteEntity(Entity* entity);
};