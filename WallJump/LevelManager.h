#pragma once

#include "Component.h"
#include "System.h"
#include "TransformComponent.h"
#include "LethalTriggerComponent.h"
#include "Player.h"

#include <random>

class LevelManagerHelperComponent : public BaseComponent<LevelManagerHelperComponent>
{
public:
	LevelManagerHelperComponent() : firstUse(true), jumpStartYMin(0), jumpStartYMax(0), jumpDestX(0), playerPosition(Right){}
	float jumpStartYMin;
	float jumpStartYMax;
	float jumpStartX;
	float jumpDestX;
	enum PlayerPosition{
		Left,
		Right
	} playerPosition;
	bool firstUse;
};

class LevelManagerSystem : public BaseSystem<LevelManagerSystem>
{
public:
	LevelManagerSystem() : BaseSystem(10) {}
	void addBlocks(LevelManagerHelperComponent* helperComponent, float distance);
	void update(LayersEngine& engine);
};