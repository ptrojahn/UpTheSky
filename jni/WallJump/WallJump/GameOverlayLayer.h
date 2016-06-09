#pragma once

#include "Layer.h"

class GameOverlayLayer : public BaseLayer<GameOverlayLayer>
{
public:
	GameOverlayLayer() : BaseLayer(true) {}
	void load();
};