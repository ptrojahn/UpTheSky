#include "ParticleSystem.h"

#include "ParticleComponent.h"
#include "PlayerSystem.h"
#include "TransformComponent.h"

void ParticleSystem::update(LayersEngine& engine) {
	for (Entity* entity : engine.getEntities()){
		ParticleComponent* component = entity->getComponent<ParticleComponent>();
		if (component){
			component->velocity.y += engine.getDeltaTime() * PlayerSystem::gravity;
			TransformComponent* transformComponent = entity->getComponent<TransformComponent>();
			transformComponent->position += component->velocity * engine.getDeltaTime();
			transformComponent->rotation += (component->rotationVelocity * engine.getDeltaTime()) / (M_PI * 2.f) * 360.f;
		}
	}
}