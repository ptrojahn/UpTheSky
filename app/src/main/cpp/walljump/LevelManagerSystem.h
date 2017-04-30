#pragma once

#include "LevelManagerHelperComponent.h"
#include "System.h"
#include "TransformComponent.h"
#include "LethalTriggerComponent.h"

#include <random>

class LevelManagerSystem : public BaseSystem<LevelManagerSystem>
{
public:
	LevelManagerSystem() : BaseSystem(1) {}
	void addBlocks(LevelManagerHelperComponent* helperComponent, float distance);
	void addClutterLeft(Vector2<float> position, float jumpDifficultyReduction, float distance, float minX, int score);
	void addClutterRight(Vector2<float> position, float jumpDifficultyReduction, float distance, float minX, int score);
	void update(LayersEngine& engine);
	void genCoin(Vector2<float> position, int score);
};