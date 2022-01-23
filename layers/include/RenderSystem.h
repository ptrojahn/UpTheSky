#pragma once

#include "System.h"
#include "ShaderManager.h"
#include "BufferManager.h"
#include "Matrix4x4.h"

class RenderSystem : public BaseSystem<RenderSystem>
{
public:
	RenderSystem(int updatePriority) : BaseSystem(updatePriority){
	}
	void update(LayersEngine& engine);
};