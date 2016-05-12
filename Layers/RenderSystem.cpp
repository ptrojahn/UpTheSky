#include "RenderSystem.h"

#include "RenderComponent.h"
#include "TransformComponent.h"
#include "UniformsComponent.h"
#include "TextureComponent.h"

#include <math.h>

void RenderSystem::update(LayersEngine& engine) {
	for (Entity* entity : engine.getEntities()){
		RenderComponent* renderComponent = entity->getComponent<RenderComponent>();
		if (renderComponent){
			ShaderManager::instance().useShader(renderComponent->shaderId);
			BufferManager::instance().bindBuffer(renderComponent->vboId);
			std::vector<int> sizes = ShaderManager::instance().getAttributesSize(renderComponent->shaderId);
			int stride = 0;
			for (int s : sizes)
				stride += s;
			int offset = 0;
			for (int index = 0; index < sizes.size(); ++index){
				glEnableVertexAttribArray(index);
				glVertexAttribPointer(index, sizes[index], GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (void*)(offset * sizeof(GLfloat)));
				offset += sizes[index];
			}
			TransformComponent* transformComponent = entity->getComponent<TransformComponent>();
			Matrix4x4 finalMatrix = engine.getProjectionMatrix();
			if (transformComponent){
				Matrix4x4 scaleMatrix(transformComponent->scale.x, 0,                           0, 0,
				                      0,                           transformComponent->scale.y, 0, 0,
				                      0,                           0,                           1, 0,
				                      0,                           0,                           0, 1);
				float rotation = transformComponent->rotation * 3.14159265359 / 180.f;
				Matrix4x4 rotationMatrix(cos(rotation), -sin(rotation), 0, 0,
				                         sin(rotation), cos(rotation),  0, 0,
				                         0,             0,              1, 0,
				                         0,             0,              0, 1);
				Matrix4x4 translationMatrix(1, 0, 0, transformComponent->position.x,
				                            0, 1, 0, transformComponent->position.y,
				                            0, 0, 1, 0,
				                            0, 0, 0, 1);
				finalMatrix = finalMatrix * translationMatrix * rotationMatrix * scaleMatrix;
			}

			UniformsComponent* uniforms = entity->getComponent<UniformsComponent>();
			if (uniforms){
				for (Uniform uniform : uniforms->uniforms){
					if (uniform.type == UniformFloat){
						if (uniform.location == 0)
							uniform.location = glGetUniformLocation(renderComponent->shaderId, uniform.name.c_str());
						glUniform1f(uniform.location, *(GLfloat*)&uniform.data[0]);
					} else if (uniform.type == UniformFloat2){
						if (uniform.location == 0)
							uniform.location = glGetUniformLocation(renderComponent->shaderId, uniform.name.c_str());
						glUniform2fv(uniform.location, 1, (GLfloat*)&uniform.data[0]);
					} else if (uniform.type == UniformFloat3){
						if (uniform.location == 0)
							uniform.location = glGetUniformLocation(renderComponent->shaderId, uniform.name.c_str());
						glUniform3fv(uniform.location, 1, (GLfloat*)&uniform.data[0]);
					} else if (uniform.type == UniformFloat4){
						if (uniform.location == 0)
							uniform.location = glGetUniformLocation(renderComponent->shaderId, uniform.name.c_str());
						glUniform4fv(uniform.location, 1, (GLfloat*)&uniform.data[0]);
					} else if (uniform.type == UniformBool){
						if (uniform.location == 0)
							uniform.location = glGetUniformLocation(renderComponent->shaderId, uniform.name.c_str());
						glUniform1i(uniform.location, *(bool*)&uniform.data[0] == true ? 1 : 0);
					}
				}
			}

			TextureComponent* textureComponent = entity->getComponent<TextureComponent>();
			if (textureComponent){
				TextureManager::instance().bindTexture(textureComponent->textureId);
			}
			
			glUniformMatrix4fv(renderComponent->shaderMatrixId, 1, GL_FALSE, finalMatrix.values);
			glDrawArrays(GL_TRIANGLES, 0, BufferManager::instance().bufferSize(renderComponent->vboId) / stride);
			for (int index = 0; index < sizes.size(); index++)
				glDisableVertexAttribArray(index);
		}
	}
}