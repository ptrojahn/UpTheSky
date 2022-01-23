#pragma once

#include "System.h"

class OnWaitFinishedSystem : public BaseSystem<OnWaitFinishedSystem>
{
public:
	OnWaitFinishedSystem(int updatePriority) : BaseSystem(updatePriority) {}
	void update(LayersEngine& engine);
};