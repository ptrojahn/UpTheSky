#pragma once

#include "System.h"

class OnUpdateSystem : public BaseSystem<OnUpdateSystem>
{
public:
	OnUpdateSystem(int updatePriority) : BaseSystem(updatePriority) {}
	void update(LayersEngine& engine);
};