#pragma once

#include "Component.h"
#include "Vector2.h"

class TransformComponent : public BaseComponent<TransformComponent>
{
public:
	TransformComponent(Vector2<float> position = Vector2<float>(0, 0), float rotation = 0, Vector2<float> scale = Vector2<float>(1, 1)) : scale(scale), position(position), rotation(rotation) {
	}
	Vector2<float> scale;
	Vector2<float> position;
	float rotation;
};