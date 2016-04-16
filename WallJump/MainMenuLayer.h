#pragma once

#include "Layer.h"

class MainMenuLayer : public Layer
{
public:
	MainMenuLayer() : Layer(true) {}
	void load();
};