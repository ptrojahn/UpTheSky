#pragma once

#include "Layer.h"

class MainMenuLayer : public BaseLayer<MainMenuLayer>
{
public:
	MainMenuLayer() : BaseLayer(true) {}
	void load();
};