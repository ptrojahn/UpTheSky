#pragma once

#include "System.h"
#include "Component.h"

class PlayerComponent : public BaseComponent<PlayerComponent>
{
public:
	Vector2<float> acceleration;
};


class PlayerSystem : public BaseSystem<PlayerSystem>
{
public:
	PlayerSystem() : BaseSystem(2) {}
	void update(LayersEngine& engine);
};