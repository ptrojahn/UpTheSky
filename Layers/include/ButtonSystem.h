#pragma once

#include "System.h"

class ButtonSystem : public System
{
public:
	ButtonSystem(int updatePriority) : System(updatePriority) {
	}
	void update(LayersEngine& data);
};