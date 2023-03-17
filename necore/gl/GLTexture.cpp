#include "GLTexture.h"

#include <GL/glew.h>

GLTexture::GLTexture(unsigned int id, int width, int height) : id(id), width(width), height(height) {
}

GLTexture::~GLTexture() {
	glDeleteTextures(1, &id);
}

int GLTexture::getWidth() const {
	return width;
}

int GLTexture::getHeight() const {
	return height;
}

void GLTexture::bind() {
	glBindTexture(GL_TEXTURE_2D, id);
}
