#include "Batch3D.h"

#include <GL/glew.h>
#include "../gl/GLMesh.h"
#include "../gl/GLTexture.h"
#include "../Texture.h"
#include "../Shader.h"
#include "../Window.h"
#include "../Camera.h"
#include "../Font.h"
#include "../MeshData.h"
#include "../RasterImage.h"
#include "../assets/Assets.h"

#define VERTEX_SIZE (3+2+4)

uint Batch3D::drawCalls = 0;


Batch3D::Batch3D(size_t vertices) : position(0) {
	capacity = vertices * VERTEX_SIZE;
	buffer = new float[capacity];
	vattr_t attrs[] = {{3}, {2}, {4}, {0}};
	mesh = GLMesh::create(buffer, 0, attrs);

	unsigned char* data = new unsigned char[4];
	*((int32_t*)data) = -1;
	RasterImage image(RGBA, {data}, 1, 1);
	_blank = GLTexture::fromImage(&image);
}

Batch3D::~Batch3D() {
	delete _blank;
	delete mesh;
	delete[] buffer;
}

void Batch3D::flush() {
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
	drawCalls++;
}

void Batch3D::vertex(float x, float y, float z, float u, float v, float r, float g, float b, float a) {
	buffer[position++] = x;
	buffer[position++] = y;
	buffer[position++] = z;
	buffer[position++] = u;
	buffer[position++] = v;
	buffer[position++] = r;
	buffer[position++] = g;
	buffer[position++] = b;
	buffer[position++] = a;
}

void Batch3D::color(float r, float g, float b, float a) {
	tint = {r, g, b, a};
}

void Batch3D::begin(Window* window, Assets* assets) {
	this->window = window;
	this->assets = assets;
	_texture = nullptr;
	tint = {1.0f, 1.0f, 1.0f, 1.0f};
	drawCalls = 0;
}

void Batch3D::setShader(Shader* shader) {
	this->shader = shader;
	shader->use();
}

void Batch3D::setShader(std::string name) {
	Shader* shader = (Shader*)assets->get(name);
	if (shader != nullptr) {
		setShader(shader);
	}
}

void Batch3D::setCamera(float ar, Camera* camera) {
	shader->uniformMatrix("u_proj", camera->getProjection(ar));
	shader->uniformMatrix("u_view", camera->getView());
}

void Batch3D::setCamera(Camera* camera) {
	setCamera(window->getRatio(), camera);
}

void Batch3D::end() {
	flush();
	assets = nullptr;
	_texture = nullptr;
}

void Batch3D::texture(Texture* texture) {
	if (texture == _texture) {
		return;
	}
	flush();
	_texture = texture;
}

void Batch3D::texture(std::string name) {
	texture((Texture*)assets->get(name));
}

void Batch3D::putCTN(MeshData* mesh, glm::mat4 matrix) {
	auto vertexData = mesh->getData();
	const float* data = vertexData.data();
	uint vertexSize = mesh->getVertexSize();
	uint vertices = vertexData.size() / vertexSize;
	if (position + vertices*VERTEX_SIZE >= capacity)
		flush();
	for (uint i = 0; i < vertices; i++) {
		glm::vec3 coord = matrix * glm::vec4(*((glm::vec3*)(data + i * vertexSize)), 1.0f);
		float u = data[i * vertexSize + 3];
		float v = data[i * vertexSize + 4];
		float r = data[i * vertexSize + 5];
		float g = data[i * vertexSize + 6];
		float b = data[i * vertexSize + 7];
		float a = 1.0f;
		vertex(coord.x, coord.y, coord.z, u, v, r, g, b, a);
	}
}

void Batch3D::putCTN(MeshData* mesh, glm::vec3 tsl) {
	auto vertexData = mesh->getData();
	const float* data = vertexData.data();
	uint vertexSize = mesh->getVertexSize();
	uint vertices = vertexData.size() / vertexSize;
	if (position + vertices*VERTEX_SIZE >= capacity)
		flush();
	for (uint i = 0; i < vertices; i++) {
		float x = data[i * vertexSize + 0] + tsl.x;
		float y = data[i * vertexSize + 1] + tsl.y;
		float z = data[i * vertexSize + 2] + tsl.z;
		float u = data[i * vertexSize + 3];
		float v = data[i * vertexSize + 4];
		float r = data[i * vertexSize + 5];
		float g = data[i * vertexSize + 6];
		float b = data[i * vertexSize + 7];
		float a = 1.0f;
		vertex(x, y, z, u, v, r, g, b, a);
	}
}
