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
#include "SharedPreferences.h"

int main(int argc, char* argv[]) {
	LayersEngine engine(9, 16);
	glClearColor(0.6f, 1.f, 1.f, 1);
	engine.addLayer(new MainMenuLayerLogic());
	engine.addLayer(new MainMenuLayerGraphics());
	ShopLayerGraphics* graphicsLayer = new ShopLayerGraphics();
	engine.addLayer(graphicsLayer);
	engine.addLayer(new ShopLayerLogic(graphicsLayer));
	engine.addLayer(new GameOverlayLayer());
	engine.addLayer(new PlayerLayer());
	engine.addLayer(new GameLayer());
	engine.addLayer(new BackgroundLayer());
	engine.run();
	return 0;
}