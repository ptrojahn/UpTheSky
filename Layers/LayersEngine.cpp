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

	//Transform the origin to the top left corner and set width and height to the aspect ratio
	Matrix4x4 logicalMatrix(2.f / (float)sceneData.logicalScreenSize.x, 0,                                           0, -1,
	                        0,                                          -2.f / (float)sceneData.logicalScreenSize.y, 0, 1,
	                        0,                                          0,                                           1, 0,
	                        0,                                          0,                                           0, 1);
	//Transform logical coordinates to physical coordinates. The aspect ratio stays the same.
	float width = (float)sceneData.logicalScreenSize.x / (float)sceneData.logicalScreenSize.y > (float)sceneData.physicalScreenSize.x / (float)sceneData.physicalScreenSize.y ?
		(float)sceneData.physicalScreenSize.x : (float)sceneData.logicalScreenSize.x / (float)sceneData.logicalScreenSize.y * (float)sceneData.physicalScreenSize.y;
	float height = (float)sceneData.logicalScreenSize.x / (float)sceneData.logicalScreenSize.y > (float)sceneData.physicalScreenSize.x / (float)sceneData.physicalScreenSize.y ?
		(float)sceneData.logicalScreenSize.y / (float)sceneData.logicalScreenSize.x * (float)sceneData.physicalScreenSize.x : (float)sceneData.physicalScreenSize.y;
	Matrix4x4 physicalMatrix(width / (float)sceneData.physicalScreenSize.x, 0,                                              0, 0,
	                         0,                                             height / (float)sceneData.physicalScreenSize.y, 0, 0,
	                         0,                                             0,                                              1, 0,
	                         0,                                             0,                                              0, 1);

	sceneData.projectionMatrix = physicalMatrix * logicalMatrix;
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