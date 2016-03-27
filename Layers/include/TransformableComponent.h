#pragma once

#include "Component.h"
#include "Vector2.h"

class TransformableComponent : public BaseComponent<TransformableComponent>
{
public:
	TransformableComponent(Vector2<float> scale, float rotation, Vector2<float> translation) : scale(scale), translation(translation), rotation(rotation) {

	}
	Vector2<float> scale;
	Vector2<float> translation;
	float rotation;
};