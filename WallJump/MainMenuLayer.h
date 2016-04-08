#pragma once

#include "Layer.h"

class MainMenuLayer : public Layer
{
public:
	MainMenuLayer() : Layer(10000) {}
	void load();
};