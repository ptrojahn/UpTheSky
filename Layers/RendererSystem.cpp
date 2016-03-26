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
			//Transform the origin to the top left corner and set width and height to the aspect ratio
			Matrix4x4 logicalMatrix(2.f / (float)data.logicalScreenSize.x, 0,                                      0, -1,
			                        0,                                     -2.f / (float)data.logicalScreenSize.y, 0, 1,
			                        0,                                     0,                                      1, 0,
			                        0,                                     0,                                      0, 1);
			//Transform logical coordinates to physical coordinates. The aspect ratio stays the same.
			float width = (float)data.logicalScreenSize.x / (float)data.logicalScreenSize.y > (float)data.physicalScreenSize.x / (float)data.physicalScreenSize.y ?
				(float)data.physicalScreenSize.x : (float)data.logicalScreenSize.x / (float)data.logicalScreenSize.y * (float)data.physicalScreenSize.y;
			float height = data.logicalScreenSize.x / (float)data.logicalScreenSize.y > (float)data.physicalScreenSize.x / (float)data.physicalScreenSize.y ?
				(float)data.logicalScreenSize.y / (float)data.logicalScreenSize.x * (float)data.physicalScreenSize.x : (float)data.physicalScreenSize.y;
			Matrix4x4 physicalMatrix(width / (float)data.physicalScreenSize.x, 0,                                                 0, 0,
			                         0,                                        height / (float)data.physicalScreenSize.y,         0, 0,
									 0,                                        0,                                                 1, 0,
									 0,                                        0,                                                 0, 1);

			Matrix4x4 orthoMatrix = physicalMatrix * logicalMatrix;
			glUniformMatrix4fv(renderable->shaderMatrixId, 1, GL_FALSE, orthoMatrix.values);
			glDrawArrays(GL_TRIANGLES, 0, BufferManager::instance().bufferSize(renderable->vboId) / stride);
			for (int index = 0; index < sizes.size(); index++)
				glDisableVertexAttribArray(index);
		}
	}
}