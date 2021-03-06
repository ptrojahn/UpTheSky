#pragma once

#include "Component.h"

#include <vector>

struct AnimationChange{
	AnimationChange(float* pointer, float startValue, float endValue) : pointer(pointer), startValue(startValue), endValue(endValue), currentValue(0) {}
	float* pointer;
	float startValue;
	float endValue;
	float currentValue;
};

struct AnimationState
{
	AnimationState(std::vector<AnimationChange> animationChanges, float length) : animationChanges(animationChanges), length(length){}
	std::vector<AnimationChange> animationChanges;
	float length;
};

class AnimationComponent : public BaseComponent<AnimationComponent>
{
public:
	enum AnimationType{
		Once,
		Loop
	} animationType;
	AnimationComponent(std::vector<AnimationState> states, AnimationType animationType) : states(states), animationType(animationType), stateIndex(0), stateTime(0) {}
	std::vector<AnimationState> states;
	unsigned int stateIndex;
	float stateTime;
};