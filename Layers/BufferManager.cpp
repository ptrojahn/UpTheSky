#include "BufferManager.h"

GLuint BufferManager::createBuffer(std::vector<GLfloat> data, GLenum target, GLenum usage) {
	for (BufferData vbd : buffers){
		if (vbd.data == data)
			return vbd.id;
	}
	GLuint bufferId;
	glGenBuffers(1, &bufferId);
	glBindBuffer(target, bufferId);
	glBufferData(target, sizeof(GLfloat) * data.size(), &data[0], usage);
	buffers.push_back({bufferId, target, data});
}

void BufferManager::bindBuffer(GLuint buffer) {
	GLuint target = 0;
	for (BufferData data : buffers){
		if (data.id == buffer){
			target = data.target;
			break;
		}
	}
	for (std::pair<GLenum, GLuint>& targetBuffer : currentBuffers){
		if (targetBuffer.first == target){
			if (targetBuffer.second != buffer){
				glBindBuffer(target, buffer);
				targetBuffer.second = buffer;
				return;
			}
		}
	}
	currentBuffers.push_back(std::pair<GLenum, GLuint>(target, buffer));
}

std::vector<GLfloat> BufferManager::rectangleVertices2D(float x, float y, float w, float h) {
	return {x		, y,
			x + w	, y,
			x + w	, y + h,
			x + w	, y + w,
			x		, y + h,
			x		,y};
}