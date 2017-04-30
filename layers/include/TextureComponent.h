#pragma once

#include "Component.h"
#include "TextureManager.h"

#include <string>
#include <initializer_list>
#include <vector>

class Texture
{
public:
	Texture(std::string texturePath, std::string uniformName, GLenum filter = GL_LINEAR, GLenum wrap = GL_CLAMP_TO_EDGE) : texturePath(texturePath), uniformName(uniformName), filter(filter), wrap(wrap) {}
	std::string texturePath;
	GLenum filter;
	GLenum wrap;
	std::string uniformName;
};

class TextureInfo
{
public:
	TextureInfo(GLuint id, std::string uniformName) : id(id), location(0), uniformName(uniformName) {}
	GLuint id;
	GLuint location;
	std::string uniformName;
};

class TextureComponent : public BaseComponent<TextureComponent>
{
public:
	TextureComponent(std::initializer_list<Texture> textureData) {
		for (Texture texture : textureData){
			textures.push_back(TextureInfo(TextureManager::instance().createTexture(texture.texturePath, texture.filter, texture.wrap), texture.uniformName));
		}
	}
	std::vector<TextureInfo> textures;
};