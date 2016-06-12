#pragma once

#include "System.h"

class CloudSystem : public BaseSystem<CloudSystem>
{
public:
	uint32_t spawnTime;
	CloudSystem() : BaseSystem(3), spawnTime(0) {}
	void update(LayersEngine& engine);
};