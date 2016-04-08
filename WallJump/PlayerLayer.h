#pragma once

#include "Layer.h"

class PlayerLayer : public Layer
{
public:
	PlayerLayer() : Layer(true) {}
	void load();
};