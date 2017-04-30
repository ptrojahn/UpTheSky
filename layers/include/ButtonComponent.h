#pragma once

#include "Component.h"

#include "Vector2.h"
#include "Entity.h"

class ButtonComponent : public BaseComponent < ButtonComponent >
{
public:
	ButtonComponent(Vector2<float> size, void(*onClick)(Entity* entity)) : size(size), onClick(onClick) {
	}
	Vector2<float> size;
	void(*onClick)(Entity* entity);
};