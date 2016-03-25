#include "include\RendererSystem.h"

void RendererSystem::update(SceneData& data) {
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
			Matrix4x4 orthoMatrix(2.f / data.logicalScreenSize.x, 0,                               0,	  -1.f,
		                          0,                              -2.f / data.logicalScreenSize.y, 0,	  1.f,
		                          0,                              0,                               1.f,   0,
		                          0,                              0,                               0,	  1.f);
			glUniformMatrix4fv(renderable->shaderMatrixId, 1, GL_FALSE, orthoMatrix.values);

			glDrawArrays(GL_TRIANGLES, 0, BufferManager::instance().bufferSize(renderable->vboId) / stride);
			for (int index = 0; index < sizes.size(); index++)
				glDisableVertexAttribArray(index);
		}
	}
}