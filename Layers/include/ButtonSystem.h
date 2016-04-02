#pragma once

#include "System.h"

class ButtonSystem : public BaseSystem<ButtonSystem>
{
public:
	ButtonSystem(int updatePriority) : BaseSystem(updatePriority) {
	}
	void update(LayersEngine& data);
};