#pragma once

#include "Component.h"
#include "System.h"
#include "TransformComponent.h"
#include "LethalTriggerComponent.h"

#include <random>

class LevelManagerHelperComponent : public BaseComponent<LevelManagerHelperComponent>
{
public:
	LevelManagerHelperComponent() : firstUse(true), jumpStartYMin(0), jumpStartYMax(0), jumpDestX(0), playerPosition(Right), height(0) {}
	float jumpStartYMin;//The y position of the top of the current wall segment
	float jumpStartYMax;//The y position of the bottom of the current wall segment
	float jumpStartX;//The start x position of the next jump
	float jumpDestX;//The end x position of the next jump
	float height;//The height of the current wall segment
	enum PlayerPosition{
		Left,
		Right
	} playerPosition;
	bool firstUse;
};

class LevelManagerSystem : public BaseSystem<LevelManagerSystem>
{
public:
	LevelManagerSystem() : BaseSystem(1) {}
	void addBlocks(LevelManagerHelperComponent* helperComponent, float distance);
	void addClutterLeft(Vector2<float> position, float jumpDifficultyReduction, float distance, float minX, int score);
	void addClutterRight(Vector2<float> position, float jumpDifficultyReduction, float distance, float minX, int score);
	void update(LayersEngine& engine);
};