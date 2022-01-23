#include "AnimationSystem.h"

#include "AnimationComponent.h"

#include <vector>

void AnimationSystem::update(LayersEngine& engine) {
	for (Entity* entity : engine.getEntities()){
        for(std::vector<Component*>::iterator component = entity->getComponents().begin(); component != entity->getComponents().end();) {
            if ((*component)->getId() == classId<AnimationComponent>()) {
                AnimationComponent *animationComponent = dynamic_cast<AnimationComponent *>(*component);
                if (animationComponent) {
                    animationComponent->stateTime += engine.getDeltaTime();

                    AnimationState &currentState = animationComponent->states[animationComponent->stateIndex];
                    if (animationComponent->stateTime < currentState.length) {
                        //Update current values
                        for (AnimationChange &change : currentState.animationChanges) {
                            float delta = (change.endValue - change.startValue) * (engine.getDeltaTime() / currentState.length);
                            *change.pointer += delta;
                            change.currentValue += delta;
                        }
                    } else {
                        //Finalize current values
                        for (AnimationChange &change : currentState.animationChanges) {
                            *change.pointer += change.endValue - (change.currentValue + change.startValue);
                            change.currentValue = 0.f;
                        }
                        animationComponent->stateIndex++;
                        //Update next values if possible
                        if (animationComponent->stateIndex == animationComponent->states.size()) {
                            if (animationComponent->animationType == AnimationComponent::Once) {
                                component = entity->deleteComponent(animationComponent);
                                continue;
                            } else if (animationComponent->animationType == AnimationComponent::Loop) {
                                animationComponent->stateIndex = 0;
                            }
                        }
                        float deltaTimeLeft = engine.getDeltaTime() - (currentState.length - (animationComponent->stateTime - engine.getDeltaTime()));
                        AnimationState &newState = animationComponent->states[animationComponent->stateIndex];
                        for (AnimationChange &change : newState.animationChanges) {
                            float delta = (change.endValue - change.startValue) * (deltaTimeLeft / newState.length);
                            *change.pointer += delta;
                            change.currentValue += delta;
                        }
                        animationComponent->stateTime = deltaTimeLeft;
                    }
                }
            }
            component++;
        }
	}
}