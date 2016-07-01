#pragma once

#include "Component.h"

class ColorChooserComponent : public BaseComponent<ColorChooserComponent>
{
public:
	ColorChooserComponent(int* colorOffset, float* skinOffset, float edge) : colorOffset(colorOffset), skinOffset(skinOffset), edge(edge) {}
	int* colorOffset;
	float* skinOffset;
	float edge;
};