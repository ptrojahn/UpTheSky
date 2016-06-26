#include "LayersEngine.h"

#include "MainMenuLayerLogic.h"
#include "MainMenuLayerGraphics.h"
#include "ShopLayerLogic.h"
#include "ShopLayerGraphics.h"
#include "PlayerLayer.h"
#include "GameLayer.h"
#include "BackgroundLayer.h"
#include "glFunctions.h"
#include "GameOverlayLayer.h"

int main(int argc, char* argv[]) {
	LayersEngine engine(9, 16);
	glClearColor(0.63922, 0.89804, 0.89804, 1);
	engine.addLayer(new MainMenuLayerLogic());
	engine.addLayer(new MainMenuLayerGraphics());
	engine.addLayer(new ShopLayerLogic());
	engine.addLayer(new ShopLayerGraphics());
	engine.addLayer(new GameOverlayLayer());
	engine.addLayer(new PlayerLayer());
	engine.addLayer(new GameLayer());
	engine.addLayer(new BackgroundLayer());
	engine.run();
	return 0;
}