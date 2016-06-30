#pragma once

#include "Component.h"

class ColorChooserComponent : public BaseComponent<ColorChooserComponent>
{
public:
	ColorChooserComponent(int* offsetPointer) : offsetPointer(offsetPointer) {}
	int* offsetPointer;
};