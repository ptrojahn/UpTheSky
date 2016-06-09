#pragma once

#include "Component.h"

class ParticleComponent : public BaseComponent<ParticleComponent>
{
public:
	ParticleComponent(Vector2<float> speed) : speed(speed) {}
	Vector2<float> speed;
};