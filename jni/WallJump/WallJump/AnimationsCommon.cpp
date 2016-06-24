#include "AnimationsCommon.h"

void entityFadeOut(Entity* entity) {
	for (Uniform& uniform : entity->getComponent<UniformsComponent>()->uniforms){
		if (uniform.name == "alpha"){
			entity->addComponent(new AnimationComponent({ AnimationState({ AnimationChange((float*)&uniform.data[0], 1.f, 0.f) }, 0.1f) }, AnimationComponent::Once));
			break;
		}
	}
}

void entityFadeIn(Entity* entity) {
	for (Uniform& uniform : entity->getComponent<UniformsComponent>()->uniforms){
		if (uniform.name == "alpha"){
			entity->addComponent(new AnimationComponent({ AnimationState({ AnimationChange((float*)&uniform.data[0], 0.f, 1.f) }, 0.1f) }, AnimationComponent::Once));
			break;
		}
	}
}