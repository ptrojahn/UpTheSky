#pragma once

#include "RenderableComponent.h"
#include "System.h"
#include "ShaderManager.h"
#include "BufferManager.h"
#include "Matrix4x4.h"
#include "SceneData.h"

class RendererSystem : public System
{
public:
	RendererSystem(int updatePriority) : System(updatePriority){
	}
	void update(SceneData& data);
};