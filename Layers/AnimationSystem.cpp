#include "AnimationSystem.h"

#include "AnimationComponent.h"

void AnimationSystem::update(LayersEngine& engine) {
	for (Entity* entity : engine.getEntities()){
		AnimationComponent* animationComponent = entity->getComponent<AnimationComponent>();
		if (animationComponent){
			if (animationComponent->stateIndex == animationComponent->states.size())
				return;

			animationComponent->stateTime += engine.getDeltaTime();

			AnimationState currentState = animationComponent->states[animationComponent->stateIndex];
			if (animationComponent->stateTime < currentState.length){
				//Update current value
				for (AnimationChange& change : currentState.animationChanges){
					*change.pointer += (change.endValue - change.startValue) * (engine.getDeltaTime() / currentState.length);
				}
			} else {
				//Update current value and update next value if possible
				for (AnimationChange& change : currentState.animationChanges){
					*change.pointer += (change.endValue - change.startValue) * (engine.getDeltaTime() - (animationComponent->stateTime - currentState.length));
				}
				animationComponent->stateIndex++;
				if (animationComponent->stateIndex == animationComponent->states.size()){
					if (animationComponent->animationType == AnimationComponent::Once)
						return;
					else if (animationComponent->animationType == AnimationComponent::Loop)
						animationComponent->stateIndex = 0;
				}
				AnimationState newState = animationComponent->states[animationComponent->stateIndex];
				for (AnimationChange& change : newState.animationChanges){
					*change.pointer += (change.endValue - change.startValue) * ((animationComponent->stateTime - currentState.length) / newState.length);
				}
				animationComponent->stateTime = 0;
			}
		}
	}
}