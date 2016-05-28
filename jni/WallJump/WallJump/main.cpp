#include "LayersEngine.h"

#include "MainMenuLayerLogic.h"
#include "MainMenuLayerGraphics.h"
#include "PlayerLayer.h"
#include "GameLayer.h"
#include "glFunctions.h"

int main(int argc, char* argv[]) {
	LayersEngine engine(9, 16);
	glClearColor(0.63922, 0.89804, 0.89804, 1);
	engine.addLayer(new MainMenuLayerLogic());
	engine.addLayer(new MainMenuLayerGraphics());
	engine.addLayer(new PlayerLayer());
	engine.addLayer(new GameLayer());
	engine.run();
	return 0;
}