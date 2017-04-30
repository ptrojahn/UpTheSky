#pragma once

#include "Component.h"

class CloudComponent : public BaseComponent<CloudComponent>
{
public:
	CloudComponent(float velocity) : velocity(velocity) {}
	float velocity;
};