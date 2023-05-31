#ifndef NECORE_G3D_BATCH3D_H_
#define NECORE_G3D_BATCH3D_H_

#include "../common.h"

#include <string>
#include <glm/glm.hpp>
#include "../uvregion.h"

class Mesh;
class Window;
class Assets;
class Texture;
class Shader;
class Camera;
class MeshData;

class Batch3D {
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

	void vertex(float x, float y, float z, float u, float v, float r, float g, float b, float a);
public:
	Batch3D(size_t vertices);
	virtual ~Batch3D();

	void begin(Window* window, Assets* assets);

	void setShader(Shader* shader);

	void setShader(std::string name);

	void setCamera(Camera* camera);

	void setCamera(float ar, Camera* camera);

	void color(float r, float g, float b, float a);

	// Coords-TexCoords-Normals Mesh
	void putCTN(MeshData* mesh, glm::mat4 matrix);
	void putCTN(MeshData* mesh, glm::vec3 tsl);

	void texture(Texture* texture);

	void texture(std::string name);

	void flush();

	void end();

	static uint drawCalls;
};

#endif /* NECORE_G3D_BATCH3D_H_ */
