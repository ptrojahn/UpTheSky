#pragma once

#include "System.h"

class HighScoreUpdateSystem : public BaseSystem<HighScoreUpdateSystem>
{
public:
	HighScoreUpdateSystem() : BaseSystem(1) {}
	void update(LayersEngine& engine);
};