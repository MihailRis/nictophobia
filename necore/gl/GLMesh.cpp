#include "GLMesh.h"

#include <GL/glew.h>

GLMesh::GLMesh(unsigned int vao, unsigned int vbo, unsigned int vertices, unsigned int vertexSize)
	: vao(vao), vbo(vbo), vertices(vertices), vertexSize(vertexSize) {
}

GLMesh::~GLMesh() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}


void GLMesh::reload(const float* buffer, unsigned int vertices) {
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexSize * vertices, buffer, GL_STATIC_DRAW);
	this->vertices = vertices;
}

void GLMesh::draw(unsigned int primitive) {
	glBindVertexArray(vao);
	glDrawArrays(primitive, 0, vertices);
	glBindVertexArray(0);
}

void GLMesh::draw() {
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, vertices);
	glBindVertexArray(0);
}


GLMesh* GLMesh::create(const float* buffer, unsigned int vertices, const vattr_t attrs[]) {
	unsigned int vertexSize = 0;
	unsigned int vao = 0;
	unsigned int vbo = 0;
	for (int i = 0; attrs[i].size; i++){
		vertexSize += attrs[i].size;
	}
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	if (buffer){
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexSize * vertices, buffer, GL_STATIC_DRAW);
	} else {
		glBufferData(GL_ARRAY_BUFFER, 0, {}, GL_STATIC_DRAW);
	}
	unsigned int offset = 0;
	for (int i = 0; attrs[i].size; i++){
		int size = attrs[i].size;
		glVertexAttribPointer(i, size, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), (GLvoid*)(offset * sizeof(float)));
		glEnableVertexAttribArray(i);
		offset += size;
	}

	glBindVertexArray(0);
	return new GLMesh(vao, vbo, vertices, vertexSize);
}
