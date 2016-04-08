#include "LayersEngine.h"

#include "MainMenuLayer.h"
#include "PlayerLayer.h"
#include "glFunctions.h"

int main(int argc, char* argv[]) {
	LayersEngine engine(9, 16);
	glClearColor(0.63922, 0.89804, 0.89804, 1);
	engine.addLayer(new MainMenuLayer());
	engine.addLayer(new PlayerLayer());
	engine.run();
	return 0;
}