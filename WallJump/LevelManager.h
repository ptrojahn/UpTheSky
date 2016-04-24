#pragma once

#include "Component.h"
#include "System.h"
#include <time.h>

class LevelManagerHelperComponent : public BaseComponent<LevelManagerHelperComponent>
{
public:
	LevelManagerHelperComponent() : levelSectionId(-1) {}
	int levelSectionId;
};

class LethalTriggerComponent : public BaseComponent<LethalTriggerComponent>
{
public:
	LethalTriggerComponent(Vector2<float> size) : size(size) {}
	Vector2<float> size;
};

class LevelManagerSystem : public BaseSystem<LevelManagerSystem>
{
public:
	LevelManagerSystem() : BaseSystem(10) { srand(time(nullptr)); }
	void update(LayersEngine& engine);
};