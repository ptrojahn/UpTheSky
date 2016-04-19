#pragma once

#include "Component.h"
#include "System.h"

class LevelManagerHelperComponent : public BaseComponent<LevelManagerHelperComponent>
{
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
	LevelManagerSystem() : BaseSystem(10) {}
	void update(LayersEngine& engine);
};