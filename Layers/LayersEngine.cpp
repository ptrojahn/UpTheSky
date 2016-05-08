#include "LayersEngine.h"

#include "Layer.h"
#include "glFunctions.h"
#include "System.h"

LayersEngine::LayersEngine(int aspectX, int aspectY) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	window = SDL_CreateWindow("GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, aspectX > aspectY ? 500 : ((float)aspectX / (float)aspectY * 500.f), aspectY > aspectX ? 500 : ((float)aspectY / (float)aspectX * 500.f), SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	SDL_GL_CreateContext(window);
	SDL_GetWindowSize(window, &physicalScreenSize.x, &physicalScreenSize.y);
	logicalScreenSize.x = aspectX;
	logicalScreenSize.y = aspectY;
	lastTick = SDL_GetTicks();
	loadGLFunctions(SDL_GL_GetProcAddress);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Transform the origin to the top left corner and set width and height to the aspect ratio
	Matrix4x4 logicalMatrix(2.f / (float)logicalScreenSize.x, 0,                                           0, -1,
	                        0,                                -2.f / (float)logicalScreenSize.y,           0, 1,
	                        0,                                0,                                           1, 0,
	                        0,                                0,                                           0, 1);
	//Transform logical coordinates to physical coordinates. The aspect ratio stays the same.
	float width = (float)logicalScreenSize.x / (float)logicalScreenSize.y > (float)physicalScreenSize.x / (float)physicalScreenSize.y ?
		(float)physicalScreenSize.x : (float)logicalScreenSize.x / (float)logicalScreenSize.y * (float)physicalScreenSize.y;
	float height = (float)logicalScreenSize.x / (float)logicalScreenSize.y > (float)physicalScreenSize.x / (float)physicalScreenSize.y ?
		(float)logicalScreenSize.y / (float)logicalScreenSize.x * (float)physicalScreenSize.x : (float)physicalScreenSize.y;
	Matrix4x4 physicalMatrix(width / (float)physicalScreenSize.x, 0,                                              0, 0,
	                         0,                                   height / (float)physicalScreenSize.y,           0, 0,
	                         0,                                   0,                                              1, 0,
	                         0,                                   0,                                              0, 1);

	projectionMatrix = physicalMatrix * logicalMatrix;
}

void LayersEngine::addLayer(Layer* layer) {
	layers.push_back(layer);
	layer->setEngine(this);
	layer->load();
}

void LayersEngine::addEntity(Entity* entity) {
	for (std::vector<Entity*>::iterator iterEntities = entities.begin(); iterEntities != entities.end(); iterEntities++){
		if ((*iterEntities)->getPriority() < entity->getPriority()){
			entities.insert(iterEntities, entity);
			updateActiveEntities();
			return;
		}
	}
	entities.push_back(entity);
	updateActiveEntities();
}

void LayersEngine::addSystem(System* system) {
	for (std::vector<System*>::iterator iterSystems = systems.begin(); iterSystems != systems.end(); iterSystems++){
		if ((*iterSystems)->getPriority() < system->getPriority()){
			systems.insert(iterSystems, system);
			updateActiveSystems();
			return;
		}
	}
	systems.push_back(system);
	updateActiveSystems();
}

std::vector<Entity*>::iterator LayersEngine::deleteEntity(Entity* entity) {
	for (std::vector<Entity*>::iterator iterEntities = entities.begin(); iterEntities != entities.end(); iterEntities++){
		if ((*iterEntities) == entity){
			delete entity;
			entities.erase(iterEntities);
			break;
		}
	}
	for (std::vector<Entity*>::iterator iterEntities = activeEntities.begin(); iterEntities != activeEntities.end(); iterEntities++){
		if ((*iterEntities) == entity)
			return activeEntities.erase(iterEntities);
	}
	return activeEntities.end();
}

//Takes control of the mainloop. Should be called at the end of main()
void LayersEngine::run() {
	bool quit = false;
	while (!quit){
		SDL_Event event;
		while (SDL_PollEvent(&event)){
		}
		Vector2<int> touchPosPhys;
		if (SDL_GetMouseState(&touchPosPhys.x, &touchPosPhys.y) == SDL_BUTTON(SDL_BUTTON_LEFT)){
			touchActive = true;
			float width = (float)logicalScreenSize.x / (float)logicalScreenSize.y > (float)physicalScreenSize.x / (float)physicalScreenSize.y ?
				(float)physicalScreenSize.x : (float)logicalScreenSize.x / (float)logicalScreenSize.y * (float)physicalScreenSize.y;
			float height = logicalScreenSize.x / (float)logicalScreenSize.y > (float)physicalScreenSize.x > (float)physicalScreenSize.y ?
				(float)logicalScreenSize.y / (float)logicalScreenSize.x * (float)physicalScreenSize.x : (float)physicalScreenSize.y;
			touchPosition = (Vector2<float>(touchPosPhys.x, touchPosPhys.y) - Vector2<float>((physicalScreenSize.x - width) / 2, (physicalScreenSize.y - height) / 2)) 
				/ Vector2<float>(width, height) * Vector2<float>(logicalScreenSize.x, logicalScreenSize.y);
		} else
			touchActive = false;

		uint32_t currentTick = SDL_GetTicks();
		deltaTime = (currentTick - lastTick) / 1000.f;
		lastTick = currentTick;

		glClear(GL_COLOR_BUFFER_BIT);
		std::vector<ClassId> runSystems;
		for (System* system : activeSystems){
			bool found = false;
			for (ClassId id : runSystems)
				if (id == system->getId()){
					found = true;
					break;
				}
			if (found)
				continue;
			system->update(*this);
			runSystems.push_back(system->getId());
		}

		SDL_GL_SwapWindow(window);
	}
}

void LayersEngine::updateActiveEntities() {
	activeEntities.clear();
	for (Entity* entity : entities){
		if (entity->getLayer()->isEnabled())
			activeEntities.push_back(entity);
	}
}
void LayersEngine::updateActiveSystems() {
	activeSystems.clear();
	for (System* system : systems){
		if (system->getLayer()->isEnabled())
			activeSystems.push_back(system);
	}
}