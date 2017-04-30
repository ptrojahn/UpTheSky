#pragma once

#include "System.h"

class AnimationSystem : public BaseSystem<AnimationSystem>
{
public:
	AnimationSystem(int updatePriority) : BaseSystem(updatePriority){}
	void update(LayersEngine& engine);
};