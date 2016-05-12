#include "TextureManager.h"

#include <SDL.h>

#include <vector>
#include <iostream>

GLuint TextureManager::createTexture(std::string texturePath, GLenum filter) {
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	SDL_Surface* bmpData = SDL_LoadBMP(texturePath.c_str());
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmpData->w, bmpData->h, 0, GL_RGB, GL_UNSIGNED_BYTE, bmpData->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	return 0;
}

void TextureManager::bindTexture(GLuint id) {
	if (id != currentTextureId){
		glBindTexture(GL_TEXTURE_2D, id);
		currentTextureId = id;
	}
}