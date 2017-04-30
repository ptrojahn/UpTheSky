#pragma once

#include "Component.h"

class ParticleComponent : public BaseComponent<ParticleComponent>
{
public:
	ParticleComponent(Vector2<float> velocity, float rotationVelocity) : velocity(velocity), rotationVelocity(rotationVelocity) {}
	Vector2<float> velocity;
	float rotationVelocity;
};