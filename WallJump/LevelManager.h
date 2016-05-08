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
	LevelManagerHelperComponent() : firstUse(true), jumpStartYMin(0), jumpStartYMax(0), jumpDestX(0), playerPosition(Right), height(0) {}
	float jumpStartYMin;
	float jumpStartYMax;
	float jumpStartX;
	float jumpDestX;
	float height;
	enum PlayerPosition{
		Left,
		Right
	} playerPosition;
	bool firstUse;
};

class LevelManagerSystem : public BaseSystem<LevelManagerSystem>
{
public:
	LevelManagerSystem() : BaseSystem(1) { mtEngine = std::mt19937(randDevice()); }
	void addBlocks(LevelManagerHelperComponent* helperComponent, float distance);
	void update(LayersEngine& engine);
private:
	std::random_device randDevice;
	std::mt19937 mtEngine;
};