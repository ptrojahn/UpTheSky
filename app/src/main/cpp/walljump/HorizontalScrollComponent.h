#pragma once

#include "Component.h"

class HorizontalScrollComponent : public BaseComponent<HorizontalScrollComponent>
{
public:
	HorizontalScrollComponent(float minValue, float maxValue, float* currentValue, Vector2<float> size, float step) : minValue(minValue), maxValue(maxValue), size(size), currentValue(currentValue), step(step), lastValue(*currentValue) {}
	float minValue;
	float maxValue;
	float step;
	Vector2<float> size;
	float* currentValue;
	float lastValue;
};