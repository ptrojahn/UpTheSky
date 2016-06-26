#pragma once

#include "Layer.h"

class ShopLayerLogic : public BaseLayer<ShopLayerLogic>
{
public:
	ShopLayerLogic() : BaseLayer(false) {}
	void load();
};