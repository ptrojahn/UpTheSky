#pragma once

#include "Component.h"
#include "System.h"
#include "glFunctions.h"

class GhostWallComponent : public BaseComponent<GhostWallComponent>
{
public:
	GhostWallComponent(Vector2<float> triggerSize) : triggerSize(triggerSize), state(Ghost), initialized(false) {}
	enum GhostWallState{
		Ghost,
		Intersecting,
		Solid
	} state;
	Vector2<float> triggerSize;
	bool initialized;
};

class GhostWallSystem : public BaseSystem<GhostWallSystem>
{
public:
	GhostWallSystem() : BaseSystem(1) {}
	void update(LayersEngine& engine);
};