#pragma once

#include "System.h"

class HorizontalScrollSystem : public BaseSystem<HorizontalScrollSystem>
{
public:
	HorizontalScrollSystem(int updatePriority) : BaseSystem(updatePriority) {}
	void update(LayersEngine& engine);
};