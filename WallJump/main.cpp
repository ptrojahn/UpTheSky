#include "LayersEngine.h"

#include "glFunctions.h"

int main(int argc, char* argv[]) {
	LayersEngine engine(9, 16);
	glClearColor(0.643, 0.776, 0.224, 1);
	engine.run();
	return 0;
}