#pragma once

#include "Component.h"
#include "System.h"

class ScrollComponent : public BaseComponent<ScrollComponent>
{

};

class ScrollSystem : public BaseSystem<ScrollSystem>
{
public:
	ScrollSystem() : BaseSystem(1) {}
	void update(LayersEngine& engine);
};