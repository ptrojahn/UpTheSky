#pragma once

#include "Layer.h"

class BackgroundLayer : public BaseLayer<BackgroundLayer>
{
public:
	BackgroundLayer() : BaseLayer(true) {}
	void load();
};