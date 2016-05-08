#pragma once

#include "System.h"
#include "Component.h"

class PlayerComponent : public BaseComponent<PlayerComponent>
{
public:
	PlayerComponent() { lastFramePressed = false;}
	Vector2<float> velocity;
	bool lastFramePressed;
};


class PlayerSystem : public BaseSystem<PlayerSystem>
{
public:
	PlayerSystem() : BaseSystem(4) {}
	void update(LayersEngine& engine);
	static const Vector2<float> playerSize;
	static const Vector2<float> jumpVelocity;
	static const float gravity;
};