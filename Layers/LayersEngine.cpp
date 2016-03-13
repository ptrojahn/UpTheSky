#include "LayersEngine.h"

LayersEngine::LayersEngine(int aspectX, int aspectY, int glesMajor, int glesMinor) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, glesMajor);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, glesMinor);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	window = SDL_CreateWindow("GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, aspectX > aspectY ? 500 : ((float)aspectX / (float)aspectY * 500.f), aspectY > aspectX ? 500 : ((float)aspectY / (float)aspectX * 500.f), SDL_WINDOW_OPENGL);
	SDL_GetWindowSize(window, &nativeSize.x, &nativeSize.y);
	windowSize.x = aspectX;
	windowSize.y = aspectY;
}

void LayersEngine::run() {
	bool quit = false;
	while (!quit){
		SDL_GL_SwapWindow(window);
	}
}