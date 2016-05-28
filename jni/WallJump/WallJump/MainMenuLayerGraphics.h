#pragma once

#include "Layer.h"

class MainMenuLayerGraphics : public BaseLayer<MainMenuLayerGraphics>
{
public:
	MainMenuLayerGraphics() : BaseLayer(true) {}
	void load();
};