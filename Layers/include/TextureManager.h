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
	TextureManager() : currentTextureId(0) {}
	static TextureManager& instance() {
		static TextureManager manager;
		return manager;
	}
	GLuint createTexture(std::string texturePath, GLenum filter = GL_LINEAR);
	void bindTexture(GLuint id);
private:
	std::vector<TextureData> textures;
	GLuint currentTextureId;
};