#include "Batch2D.h"

#include <GL/glew.h>
#include "gl/GLMesh.h"
#include "gl/GLTexture.h"
#include "Texture.h"
#include "RasterImage.h"
#include "assets/Assets.h"


#define VERTEX_SIZE (2+2+4)

Batch2D::Batch2D(size_t vertices) : position(0) {
	capacity = vertices * VERTEX_SIZE;
	buffer = new float[capacity];
	vattr_t attrs[] = {{2}, {2}, {4}, {0}};
	mesh = GLMesh::create(buffer, 0, attrs);

	unsigned char* data = new unsigned char[4];
	*((int32_t*)data) = -1;
	RasterImage image(RGBA, {data}, 1, 1);
	_blank = GLTexture::fromImage(&image);
}

Batch2D::~Batch2D() {
	delete _blank;
	delete mesh;
	delete[] buffer;
}

void Batch2D::flush() {
	if (position == 0)
		return;
	if (_texture) {
		_texture->bind();
	} else {
		_blank->bind();
	}
	mesh->reload(buffer, position / VERTEX_SIZE);
	mesh->draw(GL_TRIANGLES);
	position = 0;
}

void Batch2D::vertex(float x, float y, float u, float v, float r, float g, float b, float a) {
	buffer[position++] = x;
	buffer[position++] = y;
	buffer[position++] = u;
	buffer[position++] = v;
	buffer[position++] = r;
	buffer[position++] = g;
	buffer[position++] = b;
	buffer[position++] = a;
}

void Batch2D::color(float r, float g, float b, float a) {
	tint = {r, g, b, a};
}

void Batch2D::rect(float x, float y, float w, float h) {
	vertex(x, y, 0, 0);
	vertex(x, y+h, 0, 1);
	vertex(x+w, y+h, 1, 1);

	vertex(x, y, 0, 0);
	vertex(x+w, y+h, 1, 1);
	vertex(x+w, y, 1, 0);
}

void Batch2D::begin(Assets* assets) {
	this->assets = assets;
	_texture = nullptr;
	tint = {1.0f, 1.0f, 1.0f, 1.0f};
}

void Batch2D::end() {
	flush();
	assets = nullptr;
	_texture = nullptr;
}

void Batch2D::texture(Texture* texture) {
	if (texture == _texture) {
		return;
	}
	flush();
	_texture = texture;
}

void Batch2D::texture(std::string name) {
	texture((Texture*)assets->get(name));
}

void Batch2D::untexture() {
	_texture = nullptr;
}
