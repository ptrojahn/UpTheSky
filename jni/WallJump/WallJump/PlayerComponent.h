#pragma once

#include "Component.h"
#include "helper.h"

class PlayerComponent : public BaseComponent<PlayerComponent>
{
public:
	PlayerComponent() { lastFramePressed = false; }
	Vector2<float> velocity;
	bool lastFramePressed;
};