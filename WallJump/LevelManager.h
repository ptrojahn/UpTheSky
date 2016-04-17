#pragma once

#include "Component.h"
#include "System.h"

class LevelManagerHelperComponent : public BaseComponent<LevelManagerHelperComponent>
{
};

class LevelManagerSystem : public BaseSystem<LevelManagerSystem>
{
public:
	LevelManagerSystem() : BaseSystem(10) {}
	void update(LayersEngine& engine);
};