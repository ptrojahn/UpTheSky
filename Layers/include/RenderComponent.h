#pragma once

#include "Component.h"
#include "Vector2.h"
#include "ShaderManager.h"
#include "BufferManager.h"

class RenderComponent : public BaseComponent<RenderComponent>
{
public:
	RenderComponent(GLuint shaderId, GLuint vboId) : shaderId(shaderId), vboId(vboId){
		shaderMatrixId = glGetUniformLocation(shaderId, "LE_matrix");
	}
	GLuint shaderId;
	GLuint shaderMatrixId;
	GLuint vboId;
};