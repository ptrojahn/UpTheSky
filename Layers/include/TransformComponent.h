#pragma once

#include "Component.h"
#include "Vector2.h"

class TransformComponent : public BaseComponent<TransformComponent>
{
public:
	TransformComponent(Vector2<float> scale, float rotation, Vector2<float> position) : scale(scale), position(position), rotation(rotation) {

	}
	Vector2<float> scale;
	Vector2<float> position;
	float rotation;
};