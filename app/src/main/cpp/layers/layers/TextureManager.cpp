#include "TextureManager.h"

#include <SDL.h>

#include <vector>
#include <iostream>

GLuint TextureManager::createTexture(std::string fileName, GLenum filter, GLenum wrap) {
	for (TextureData texture : textures){
		if (texture.fileName == fileName)
			return texture.id;
	}
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	SDL_Surface* bmpData = SDL_LoadBMP(fileName.c_str());
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmpData->w, bmpData->h, 0, GL_RGB, GL_UNSIGNED_BYTE, bmpData->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
	textures.push_back(TextureData(textureId, fileName));
	return textureId;
}

void TextureManager::bindTexture(GLuint id, int textureUnit) {
	if (textureUnit + 1 <= currentTextureId.size() && currentTextureId[textureUnit] == id)
		return;
	if (textureUnit + 1 > currentTextureId.size())
		currentTextureId.push_back(id);
	else if (currentTextureId[textureUnit] != id)
		currentTextureId[textureUnit] = id;
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, id);
}