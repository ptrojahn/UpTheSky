#pragma once

#include "Layer.h"
#include "MainMenuLayerGraphics.h"
#include "AudioManager.h"

class MainMenuLayerLogic : public BaseLayer<MainMenuLayerLogic>
{
public:
	MainMenuLayerLogic(MainMenuLayerGraphics* graphicsLayer) : BaseLayer(true), graphicsLayer(graphicsLayer), jumpSound(AudioManager::instance().loadAudio("jump.ogg")) {}
	void load();
	AudioAsset getJumpSound() { return jumpSound; }
	MainMenuLayerGraphics* getGraphicsLayer() { return graphicsLayer; }
private:
	MainMenuLayerGraphics* graphicsLayer;
	AudioAsset jumpSound;
};