#pragma once

#include "Component.h"

class CoinComponent : public BaseComponent<CoinComponent>
{
public:
	CoinComponent() : collected(false) {}
	bool collected;
};