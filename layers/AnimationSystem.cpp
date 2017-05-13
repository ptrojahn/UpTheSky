#include "AnimationSystem.h"

#include "AnimationComponent.h"

void AnimationSystem::update(LayersEngine& engine) {
	for (Entity* entity : engine.getEntities()){
        for(Component* component : entity->getComponents()) {
            if (component->getId() == classId<AnimationComponent>()) {
                AnimationComponent *animationComponent = dynamic_cast<AnimationComponent *>(component);
                if (animationComponent) {
                    animationComponent->stateTime += engine.getDeltaTime();

                    AnimationState &currentState = animationComponent->states[animationComponent->stateIndex];
                    if (animationComponent->stateTime < currentState.length) {
                        //Update current value
                        for (AnimationChange &change : currentState.animationChanges) {
                            float delta = (change.endValue - change.startValue) * (engine.getDeltaTime() / currentState.length);
                            *change.pointer += delta;
                            change.currentValue += delta;
                        }
                    } else {
                        //Update current value and update next value if possible
                        for (AnimationChange &change : currentState.animationChanges) {
                            *change.pointer += change.endValue - (change.currentValue + change.startValue);
                        }
                        animationComponent->stateIndex++;
                        if (animationComponent->stateIndex == animationComponent->states.size()) {
                            if (animationComponent->animationType == AnimationComponent::Once) {
                                entity->deleteComponent(animationComponent);
                                continue;
                            } else if (animationComponent->animationType == AnimationComponent::Loop) {
                                animationComponent->stateIndex = 0;
                            }
                        }
                        AnimationState &newState = animationComponent->states[animationComponent->stateIndex];
                        for (AnimationChange &change : newState.animationChanges) {
                            float delta = (change.endValue - change.startValue) * ((animationComponent->stateTime - currentState.length) / newState.length);
                            *change.pointer += delta;
                            change.currentValue += delta;
                        }
                        animationComponent->stateTime = animationComponent->stateTime - currentState.length;
                    }
                }
            }
        }
	}
}