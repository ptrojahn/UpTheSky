#include "ParticleSystem.h"

#include "ParticleComponent.h"
#include "Player.h"
#include "TransformComponent.h"

void ParticleSystem::update(LayersEngine& engine) {
	for (Entity* entity : engine.getEntities()){
		ParticleComponent* component = entity->getComponent<ParticleComponent>();
		if (component){
			component->speed.y += engine.getDeltaTime() * PlayerSystem::gravity;
			entity->getComponent<TransformComponent>()->position += component->speed * engine.getDeltaTime();
		}
	}
}