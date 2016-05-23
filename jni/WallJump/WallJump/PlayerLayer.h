#pragma once

#include "Layer.h"

class PlayerLayer : public BaseLayer<PlayerLayer>
{
public:
	PlayerLayer() : BaseLayer(true) {}
	void load();
};