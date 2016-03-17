#pragma once

#include "Entity.h"
#include "System.h"

#include <vector>

class Layer;

struct SceneData
{
	std::vector<Entity*> entities;
	std::vector<System*> systems;
};