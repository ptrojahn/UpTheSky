#pragma once

#include "Layer.h"
#include "MainMenuLayerGraphics.h"

class MainMenuLayerLogic : public BaseLayer<MainMenuLayerLogic>
{
public:
	MainMenuLayerLogic(MainMenuLayerGraphics* graphicsLayer) : BaseLayer(true), graphicsLayer(graphicsLayer) {}
	void load();
	MainMenuLayerGraphics* graphicsLayer;
};