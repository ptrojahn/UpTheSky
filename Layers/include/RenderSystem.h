#pragma once

#include "System.h"
#include "ShaderManager.h"
#include "BufferManager.h"
#include "Matrix4x4.h"

class RenderSystem : public System
{
public:
	RenderSystem(int updatePriority) : System(updatePriority){
	}
	void update(LayersEngine& engine);
};