#ifndef NECORE_BATCH2D_H_
#define NECORE_BATCH2D_H_

#include <stdlib.h>
#include <string>
#include <glm/glm.hpp>

class Mesh;
class Assets;
class Texture;
class Camera;
class Shader;

class Batch2D {
	Mesh* mesh;
	float* buffer;
	size_t capacity;
	size_t position;
	glm::vec4 tint {1.0f, 1.0f, 1.0f, 1.0f};
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

	void begin(Assets* assets);

	void setShader(Shader* shader);

	void setShader(std::string name);

	void setCamera(float ar, Camera* camera);

	void end();

	void color(float r, float g, float b, float a);

	void rect(float x, float y, float w, float h);

	void texture(Texture* texture);

	void texture(std::string name);

	void untexture();

	void flush();
};

#endif /* NECORE_BATCH2D_H_ */
