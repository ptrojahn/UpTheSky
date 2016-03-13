#include "LayersEngine.h"

int wmain(int argc, wchar_t* argv[]) {
	LayersEngine engine(9, 16, 2, 0);
	engine.run();
	return 0;
}