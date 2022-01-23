#pragma once

#include "Component.h"
#include "Entity.h"

#include <SDL.h>

class OnWaitFinishedComponent : public BaseComponent<OnWaitFinishedComponent>
{
public:
	OnWaitFinishedComponent(uint32_t millisecs, void(*function)(Entity* entity)) : millisecs(millisecs), function(function), startTime(SDL_GetTicks()) {}
	uint32_t millisecs;
	uint32_t startTime;
	void(*function)(Entity* entity);
};