#pragma once

#include "Component.h"

class ScrollComponent : public BaseComponent<ScrollComponent>
{
public:
	ScrollComponent(float factor = 1.f) : factor(factor) {}
	float factor;
};