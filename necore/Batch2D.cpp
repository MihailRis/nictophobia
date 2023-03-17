#include "Batch2D.h"

#include <GL/glew.h>
#include "gl/GLMesh.h"


#define VERTEX_SIZE (2+2+4)

Batch2D::Batch2D(size_t vertices) : position(0) {
	capacity = vertices * VERTEX_SIZE;
	buffer = new float[capacity];
	vattr_t attrs[] = {{2}, {2}, {4}, {0}};
	mesh = GLMesh::create(buffer, 0, attrs);
}

Batch2D::~Batch2D() {
	delete mesh;
	delete[] buffer;
}

void Batch2D::flush() {
	if (position == 0)
		return;
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
