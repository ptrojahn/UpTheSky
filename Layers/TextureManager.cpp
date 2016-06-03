#include "TextureManager.h"

#include <SDL.h>

#include <vector>
#include <iostream>

GLuint TextureManager::createTexture(std::string fileName, GLenum filter) {
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
	textures.push_back(TextureData(textureId, fileName));
	currentTextureId = textureId;
	return textureId;
}

void TextureManager::bindTexture(GLuint id) {
	if (id != currentTextureId){
		glBindTexture(GL_TEXTURE_2D, id);
		currentTextureId = id;
	}
}