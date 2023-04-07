#ifndef NECORE_BATCH2D_H_
#define NECORE_BATCH2D_H_

#include <stdlib.h>
#include <string>
#include <glm/glm.hpp>
#include "uvregion.h"

class Mesh;
class Font;
class Assets;
class Texture;
class Camera;
class Shader;
class Sprite;
class Window;

class Batch2D {
	Mesh* mesh;
	float* buffer;
	size_t capacity;
	size_t position;
	glm::vec4 tint {1.0f, 1.0f, 1.0f, 1.0f};
	Window* window = nullptr;
	Assets* assets = nullptr;
	Texture* _texture = nullptr;
	Texture* _blank;
	Shader* shader = nullptr;
	Camera* camera = nullptr;

	void vertex(float x, float y, float u, float v) {
		vertex(x, y, u, v, tint.r, tint.g, tint.b, tint.a);
	}
	void vertex(float x, float y, float u, float v, float r, float g, float b, float a);
public:
	Batch2D(size_t vertices);
	virtual ~Batch2D();

	void begin(Window* window, Assets* assets);

	void setShader(Shader* shader);

	void setShader(std::string name);

	void setCamera(Camera* camera);

	void setCamera(float ar, Camera* camera);

	void end();

	void color(float r, float g, float b, float a);

	void rect(float x, float y, float w, float h);

	void rect(float x, float y,float w, float h, float ox, float oy,
			float angle,
			uvregion region,
			bool flippedX,
			bool flippedY,
			glm::vec4 tint);

	void draw(Sprite* sprite);

	void drawText(std::string fontName, std::wstring text, float x, float y, bool format, bool yap, float timer);

	void texture(Texture* texture);

	void texture(std::string name);

	void untexture();

	void flush();
};

#endif /* NECORE_BATCH2D_H_ */
