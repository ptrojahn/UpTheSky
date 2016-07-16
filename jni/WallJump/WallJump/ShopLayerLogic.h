#pragma once

#include "Layer.h"
#include "ShopLayerGraphics.h"
#include "AudioManager.h"

class ShopLayerLogic : public BaseLayer<ShopLayerLogic>
{
public:
	ShopLayerLogic(ShopLayerGraphics* graphicsLayer) : BaseLayer(false), graphicsLayer(graphicsLayer) {}
	void load();
	ShopLayerGraphics* getGraphicsLayer() { return graphicsLayer; }
	AudioAsset getUiInteractionSound() { return uiInteractionSound; }
private:
	ShopLayerGraphics* graphicsLayer;
	AudioAsset uiInteractionSound;
};