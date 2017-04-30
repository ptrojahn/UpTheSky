#pragma once

#include "Layer.h"

class GameLayer : public BaseLayer<GameLayer>
{
public:
	GameLayer() : BaseLayer(false) {}
	void load();
};