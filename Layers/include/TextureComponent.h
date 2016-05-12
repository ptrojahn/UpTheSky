#pragma once

#include "Component.h"
#include "TextureManager.h"

#include <string>

class TextureComponent : public BaseComponent<TextureComponent>
{
public:
	TextureComponent(std::string texturePath, GLenum filter = GL_LINEAR) : textureId(TextureManager::instance().createTexture(texturePath, filter)) {}
	GLuint textureId;
};