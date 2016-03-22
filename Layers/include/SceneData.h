#pragma once

#include "Matrix4x4.h"
#include "Vector2.h"

#include <vector>

class Layer;
class System;
class Entity;

struct SceneData
{
	std::vector<Entity*> entities;
	std::vector<System*> systems;
	float deltaTime;
	Vector2<float> logicalScreenSize;
};