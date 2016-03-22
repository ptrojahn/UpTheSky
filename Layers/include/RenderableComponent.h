#pragma once

#include "Component.h"
#include "Vector2.h"
#include "ShaderManager.h"
#include "BufferManager.h"

class RenderableComponent : public BaseComponent<RenderableComponent>
{
public:
	RenderableComponent(GLuint shader, GLuint vbo) {
		shaderId = shader;
		vboId = vbo;
		shaderMatrixId = glGetUniformLocation(shader, "LE_matrix");
	}
	GLuint shaderId;
	GLuint shaderMatrixId;
	GLuint vboId;
};