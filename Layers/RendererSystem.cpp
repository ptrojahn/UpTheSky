#include "RendererSystem.h"

#include "RenderableComponent.h"
#include "TransformableComponent.h"
#include "UniformsComponent.h"

#include <math.h>

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
			TransformableComponent* transformable = entity->getComponent<TransformableComponent>();
			Matrix4x4 finalMatrix = data.projectionMatrix;
			if (transformable){
				Matrix4x4 scaleMatrix(transformable->scale.x, 0,                      0, 0,
				                      0,                      transformable->scale.y, 0, 0,
				                      0,                      0,                      1, 0,
				                      0,                      0,                      0, 1);
				float rotation = transformable->rotation * (3.14159265359 / 180.f);
				Matrix4x4 rotationMatrix(cos(rotation), -sin(rotation), 0, 0,
				                         sin(rotation), cos(rotation),  0, 0,
				                         0,             0,              1, 0,
				                         0,             0,              0, 1);
				Matrix4x4 translationMatrix(1, 0, 0, transformable->translation.x,
				                            0, 1, 0, transformable->translation.y,
				                            0, 0, 1, 0,
				                            0, 0, 0, 1);
				finalMatrix = finalMatrix * translationMatrix * rotationMatrix * scaleMatrix;
			}

			UniformsComponent* uniforms = entity->getComponent<UniformsComponent>();
			if (uniforms){
				for (Uniform uniform : uniforms->uniforms){
					if (uniform.type == UniformFloat){
						if (uniform.location == 0)
							uniform.location = glGetUniformLocation(renderable->shaderId, uniform.name.c_str());
						glUniform1f(uniform.location, *(GLfloat*)&uniform.data[0]);
					} else if (uniform.type == UniformFloat2){
						if (uniform.location == 0)
							uniform.location = glGetUniformLocation(renderable->shaderId, uniform.name.c_str());
						glUniform2fv(uniform.location, 1, (GLfloat*)&uniform.data[0]);
					} else if (uniform.type == UniformFloat3){
						if (uniform.location == 0)
							uniform.location = glGetUniformLocation(renderable->shaderId, uniform.name.c_str());
						glUniform3fv(uniform.location, 1, (GLfloat*)&uniform.data[0]);
					} else if (uniform.type == UniformFloat4){
						if (uniform.location == 0)
							uniform.location = glGetUniformLocation(renderable->shaderId, uniform.name.c_str());
						glUniform4fv(uniform.location, 1, (GLfloat*)&uniform.data[0]);
					}
				}
			}
			
			glUniformMatrix4fv(renderable->shaderMatrixId, 1, GL_FALSE, finalMatrix.values);
			glDrawArrays(GL_TRIANGLES, 0, BufferManager::instance().bufferSize(renderable->vboId) / stride);
			for (int index = 0; index < sizes.size(); index++)
				glDisableVertexAttribArray(index);
		}
	}
}