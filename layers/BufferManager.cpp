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
	return bufferId;
}

void BufferManager::bindBuffer(GLuint bufferId) {
	GLuint target = 0;
	for (BufferData data : buffers){
		if (data.id == bufferId){
			target = data.target;
			break;
		}
	}
	for (std::pair<GLenum, GLuint>& targetBuffer : currentBuffers){
		if (targetBuffer.first == target){
			if (targetBuffer.second != bufferId){
				glBindBuffer(target, bufferId);
				targetBuffer.second = bufferId;
			}
			return;
		}
	}
	currentBuffers.push_back(std::pair<GLenum, GLuint>(target, bufferId));
	glBindBuffer(target, bufferId);
}

std::vector<GLfloat> BufferManager::rectangleVertices2D(float x, float y, float w, float h) {
	return {x		, y,
			x + w	, y,
			x + w	, y + h,
			x + w	, y + h,
			x		, y + h,
			x		,y};
}

std::vector<GLfloat> BufferManager::rectangleVertices2DUV(float x, float y, float w, float h, float uvWidth, float uvHeight) {
	return{ x, y,         0.f,		0.f,
	        x + w, y,     uvWidth,	0.f,
	        x + w, y + h, uvWidth,	uvHeight,
	        x + w, y + h, uvWidth,	uvHeight,
	        x, y + h,     0.f,		uvHeight,
	        x, y,         0.f,		0.f};
}

int BufferManager::bufferSize(GLuint buffer) {
	for (BufferData data : buffers){
		if (data.id == buffer)
			return data.data.size();
	}
	return 0;
}