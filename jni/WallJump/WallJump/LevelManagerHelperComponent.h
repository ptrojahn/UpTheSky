#pragma once

#include "Component.h"

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