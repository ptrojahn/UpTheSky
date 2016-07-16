#pragma once

#include "Layer.h"
#include "AudioManager.h"

class ShopLayerGraphics : public BaseLayer<ShopLayerGraphics>
{
public:
	ShopLayerGraphics() : BaseLayer(true) {}
	void load();
	Entity* getLock() { return lock; }
	Entity* getSkinChooser() { return skinChooser; }
	Entity* getSkinPrice() { return skinPrice; }
	AudioAsset getUiInteractionSound() { return uiInteractionSound; }
private:
	Entity* lock;
	Entity* skinChooser;
	Entity* skinPrice;
	AudioAsset uiInteractionSound;
};