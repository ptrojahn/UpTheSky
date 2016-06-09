#pragma once

#include "System.h"

class ParticleSystem : public BaseSystem<ParticleSystem>
{
public:
	ParticleSystem() : BaseSystem(11) {}
	void update(LayersEngine& engine);
};