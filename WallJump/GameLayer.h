#pragma once

#include "Layer.h"

class GameLayer : public Layer
{
public:
	GameLayer() : Layer(true) {}
	void load();
};