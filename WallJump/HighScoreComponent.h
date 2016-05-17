#pragma once

#include "Component.h"

class HighScoreComponent : public BaseComponent<HighScoreComponent>
{
public:
	HighScoreComponent() : BaseComponent(), updated(false) {}
	bool updated;
};