#pragma once

#include "System.h"

class PlayerSystem : public BaseSystem<PlayerSystem>
{
public:
	PlayerSystem() : BaseSystem(4) {}
	void update(LayersEngine& engine);
	static void onPlayerDeath(Entity* player);
	static const Vector2<float> playerSize;
	static const Vector2<float> jumpVelocity;
	static const float gravity;
};