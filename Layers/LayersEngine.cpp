#include "LayersEngine.h"
#include "glFunctions.h"

LayersEngine::LayersEngine(int aspectX, int aspectY) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	window = SDL_CreateWindow("GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, aspectX > aspectY ? 500 : ((float)aspectX / (float)aspectY * 500.f), aspectY > aspectX ? 500 : ((float)aspectY / (float)aspectX * 500.f), SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	SDL_GL_CreateContext(window);
	SDL_GetWindowSize(window, &sceneData.physicalScreenSize.x, &sceneData.physicalScreenSize.y);
	sceneData.logicalScreenSize.x = aspectX;
	sceneData.logicalScreenSize.y = aspectY;
	loadGLFunctions(SDL_GL_GetProcAddress);
	glClearColor(0, 0, 0, 1);
}

void LayersEngine::addLayer(Layer* layer) {
	layers.push_back(layer);
	layer->setSceneData(&sceneData);
	layer->load();
}

//Takes control of the mainloop. Should be called at the end of main()
void LayersEngine::run() {
	bool quit = false;
	while (!quit){
		SDL_Event event;
		while (SDL_PollEvent(&event)){
			
		}
		glClear(GL_COLOR_BUFFER_BIT);

		for (System* system : sceneData.systems){
			system->update(sceneData);
		}

		SDL_GL_SwapWindow(window);
	}
}