#pragma once

#include "Vector2.h"
#include "Component.h"

class LethalTriggerComponent : public BaseComponent<LethalTriggerComponent>
{
public:
	LethalTriggerComponent(Vector2<float> size) : size(size) {}
	Vector2<float> size;
};