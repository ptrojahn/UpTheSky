#pragma once

#include "Component.h"
#include "Vector2.h"

class StaticColliderComponent : public BaseComponent<StaticColliderComponent>
{
public:
	StaticColliderComponent(Vector2<float> size) : size(size){}
	Vector2<float> size;
};