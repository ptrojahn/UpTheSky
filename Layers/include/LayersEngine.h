#pragma once

#include "Vector2.h"
#include <SDL.h>

class LayersEngine
{
public:
	LayersEngine(int aspectX, int aspectY);
	void run();
	Vector2<float> getWindowSize() { return windowSize; }
private:
	Vector2<float> windowSize;
	Vector2<int> nativeSize;
	SDL_Window* window;
};