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
	void update(SceneData& data) {
		for (Entity* entity : data.entities){
			RenderableComponent* renderable = entity->getComponent<RenderableComponent>();
			if (renderable){
				ShaderManager::instance().useShader(renderable->shaderId);
				BufferManager::instance().bindBuffer(renderable->vboId);
				std::vector<int> sizes = ShaderManager::instance().getAttributesSize(renderable->shaderId);
				int stride = 0;
				for (int s : sizes)
					stride += s;
				int offset = 0;
				for (int index = 0; index < sizes.size(); ++index){
					glEnableVertexAttribArray(index);
					glVertexAttribPointer(index, sizes[index], GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (void*)offset);
					offset += sizes[index];
				}

				glDrawArrays(GL_TRIANGLES, 0, BufferManager::instance().bufferSize(renderable->vboId) / stride);
				for (int index = 0; index < sizes.size(); index++)
					glDisableVertexAttribArray(index);
			}
		}
	}
};