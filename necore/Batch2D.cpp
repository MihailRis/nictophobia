#include "Batch2D.h"

#include <GL/glew.h>
#include "gl/GLMesh.h"
#include "gl/GLTexture.h"
#include "Texture.h"
#include "Shader.h"
#include "Window.h"
#include "Camera.h"
#include "RasterImage.h"
#include "assets/Assets.h"
#include "g2d/Sprite.h"


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

void Batch2D::rect(
		float x, float y,
		float w, float h,
		float ox, float oy,
		float angle,
		uvregion region,
		bool flippedX,
		bool flippedY,
		glm::vec4 tint) {
	if (position + 6*VERTEX_SIZE >= capacity)
		flush();

    float centerX = w*ox;
    float centerY = h*oy;
    float acenterX = w-centerX;
    float acenterY = h-centerY;

    float _x1 = -centerX;
    float _y1 = -centerY;

    float _x2 = -centerX;
    float _y2 = +acenterY;

    float _x3 = +acenterX;
    float _y3 = +acenterY;

    float _x4 = +acenterX;
    float _y4 = -centerY;

    float x1,y1,x2,y2,x3,y3,x4,y4;

    if (angle != 0) {
        float s = sin(angle);
        float c = cos(angle);

        x1 = c * _x1 - s * _y1;
        y1 = s * _x1 + c * _y1;

        x2 = c * _x2 - s * _y2;
        y2 = s * _x2 + c * _y2;

        x3 = c * _x3 - s * _y3;
        y3 = s * _x3 + c * _y3;

        x4 = x1 + (x3 - x2);
        y4 = y3 - (y2 - y1);
    } else {
        x1 = _x1;
        y1 = _y1;
        x2 = _x2;
        y2 = _y2;
        x3 = _x3;
        y3 = _y3;
        x4 = _x4;
        y4 = _y4;
    }

    x1 += x; x2 += x; x3 += x; x4 += x;
    y1 += y; y2 += y; y3 += y; y4 += y;

    float u1 = region.u1;
    float v1 = region.v1;
    float u2 = region.u1;
    float v2 = region.v2;
    float u3 = region.u2;
    float v3 = region.v2;
    float u4 = region.u2;
    float v4 = region.v1;

    if (flippedX) {
        float temp = u1;
        u1 = u3;
        u4 = temp;
        u2 = u3;
        u3 = temp;
    }
    if (flippedY) {
        float temp = v1;
        v1 = v2;
        v4 = v2;
        v2 = temp;
        v3 = temp;
    }

    vertex(x1, y1, u1, v1, tint.r, tint.g, tint.b, tint.a);
    vertex(x2, y2, u2, v2, tint.r, tint.g, tint.b, tint.a);
    vertex(x3, y3, u3, v3, tint.r, tint.g, tint.b, tint.a);

    /* Right down triangle */
    vertex(x1, y1, u1, v1, tint.r, tint.g, tint.b, tint.a);
    vertex(x3, y3, u3, v3, tint.r, tint.g, tint.b, tint.a);
    vertex(x4, y4, u4, v4, tint.r, tint.g, tint.b, tint.a);
}

void Batch2D::draw(Sprite* sprite) {
	glm::vec2 position = sprite->getPosition();
	glm::vec2 size = sprite->getSize();
	glm::vec2 origin = sprite->getOrigin();
	std::string textureName = sprite->getTextureName();
	if (textureName.empty()) {
		texture(sprite->getTexture());
	} else {
		texture(textureName);
	}
	rect(
		position.x, position.y,
		size.x, size.y,
		origin.x, origin.y,
		sprite->getRotation(),
		sprite->getRegion(),
		sprite->flippedX,
		sprite->flippedY,
		sprite->getColor());
}

void Batch2D::begin(Window* window, Assets* assets) {
	this->window = window;
	this->assets = assets;
	_texture = nullptr;
	tint = {1.0f, 1.0f, 1.0f, 1.0f};
}

void Batch2D::setShader(Shader* shader) {
	this->shader = shader;
	shader->use();
}

void Batch2D::setShader(std::string name) {
	Shader* shader = (Shader*)assets->get(name);
	if (shader != nullptr) {
		setShader(shader);
	}
}

void Batch2D::setCamera(float ar, Camera* camera) {
	shader->uniformMatrix("u_proj", camera->getProjection(ar));
	shader->uniformMatrix("u_view", camera->getView());
}

void Batch2D::setCamera(Camera* camera) {
	int w = window->getWidth();
	int h = window->getHeight();
	setCamera((float)w/(float)h, camera);
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
