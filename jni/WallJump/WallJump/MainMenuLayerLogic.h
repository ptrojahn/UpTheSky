#pragma once

#include "Layer.h"
#include "MainMenuLayerGraphics.h"
#include "AudioManager.h"

class MainMenuLayerLogic : public BaseLayer<MainMenuLayerLogic>
{
public:
	MainMenuLayerLogic(MainMenuLayerGraphics* graphicsLayer) : BaseLayer(true), graphicsLayer(graphicsLayer) {}
	void load();
	AudioAsset getJumpSound() { return jumpSound; }
	AudioAsset getUiInteractionSound() { return uiInteractionSound; }
	MainMenuLayerGraphics* getGraphicsLayer() { return graphicsLayer; }
private:
	MainMenuLayerGraphics* graphicsLayer;
	AudioAsset jumpSound;
	AudioAsset uiInteractionSound;
};