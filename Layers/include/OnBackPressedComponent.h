#pragma once

#include "Component.h"
#include "Entity.h"

class OnBackPressedComponent : public BaseComponent<OnBackPressedComponent>
{
public:
	OnBackPressedComponent(void(*onBackPressed)(Entity* entity)) : onBackPressed(onBackPressed) {}
	void(*onBackPressed)(Entity* entity);
};