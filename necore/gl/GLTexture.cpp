#include "GLTexture.h"

#include <GL/glew.h>
#include "../RasterImage.h"

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

GLTexture* GLTexture::fromImage(RasterImage* image) {
    unsigned int texture;
    int format = GL_RGB;
    switch (image->getFormat()) {
    case RGB:
    	break;
    case RGBA:
    	format = GL_RGBA;
    	break;
    }

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0,
        format, GL_UNSIGNED_BYTE, (GLvoid*)image->getRaster().ubyte);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, 0);
    return new GLTexture(texture, image->getWidth(), image->getHeight());
}
