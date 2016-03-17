#pragma once

#include "Vector2.h"
#include "Layer.h"
#include "SceneData.h"

#include <SDL.h>

#include <vector>

class LayersEngine
{
public:
	LayersEngine(int aspectX, int aspectY);
	void addLayer(Layer* layer);
	void run();
	Vector2<float> getWindowSize() { return windowSize; }
private:
	Vector2<float> windowSize;
	Vector2<int> nativeSize;
	SDL_Window* window;
	std::vector<Layer*> layers;
	SceneData sceneData;
};