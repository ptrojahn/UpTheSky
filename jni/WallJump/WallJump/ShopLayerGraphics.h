#pragma once

#include "Layer.h"

class ShopLayerGraphics : public BaseLayer<ShopLayerGraphics>
{
public:
	ShopLayerGraphics() : BaseLayer(true) {}
	void load();
};