#pragma once

#include "Layer.h"
#include "ShopLayerGraphics.h"

class ShopLayerLogic : public BaseLayer<ShopLayerLogic>
{
public:
	ShopLayerLogic(ShopLayerGraphics* graphicsLayer) : BaseLayer(false), graphicsLayer(graphicsLayer) {}
	void load();
	ShopLayerGraphics* graphicsLayer;
};