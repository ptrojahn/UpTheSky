#pragma once

#include "System.h"

class ColorChooserSystem : public BaseSystem<ColorChooserSystem>
{
public:
	ColorChooserSystem(int updatePriority) : BaseSystem(updatePriority) {}
	void update(LayersEngine& engine);
};