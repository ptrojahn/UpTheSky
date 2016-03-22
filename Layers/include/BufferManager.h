#pragma once

#include "glFunctions.h"

#include <vector>

struct BufferData
{
	GLuint id;
	GLenum target;
	std::vector<GLfloat> data;
};

class BufferManager
{
public:
	static BufferManager& instance() {
		static BufferManager manager;
		return manager;
	}
	static std::vector<GLfloat> rectangleVertices2D(float x, float y, float width, float height);
	GLuint createBuffer(std::vector<GLfloat> data, GLenum target = GL_ARRAY_BUFFER, GLenum usage = GL_STATIC_DRAW);
	int bufferSize(GLuint buffer);
	void bindBuffer(GLuint buffer);
private:
	std::vector<std::pair<GLenum, GLuint>> currentBuffers;
	std::vector<BufferData> buffers;
};