#pragma once

#include "System.h"

class ScrollSystem : public BaseSystem<ScrollSystem>
{
public:
	ScrollSystem() : BaseSystem(2) {}
	void update(LayersEngine& engine);
};