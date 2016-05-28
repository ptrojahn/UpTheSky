#pragma once

#include "Layer.h"

class MainMenuLayerLogic : public BaseLayer<MainMenuLayerLogic>
{
public:
	MainMenuLayerLogic() : BaseLayer(true) {}
	void load();
};