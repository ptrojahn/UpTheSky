#pragma once

#include "glFunctions.h"

#include <string>
#include <vector>

struct TextureData
{
	TextureData(GLuint id, std::string fileName) : id(id), fileName(fileName) {}
	GLuint id;
	std::string fileName;
};

class TextureManager
{
public:
	TextureManager() {}
	static TextureManager& instance() {
		static TextureManager manager;
		return manager;
	}
	GLuint createTexture(std::string texturePath, GLenum filter = GL_LINEAR, GLenum wrap = GL_CLAMP_TO_EDGE);
	void bindTexture(GLuint id, int textureUnit);
private:
	std::vector<TextureData> textures;
	std::vector<GLuint> currentTextureId;
};