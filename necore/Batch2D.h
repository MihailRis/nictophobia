#ifndef NECORE_BATCH2D_H_
#define NECORE_BATCH2D_H_

#include <stdlib.h>
#include <glm/glm.hpp>

class Mesh;

class Batch2D {
	Mesh* mesh;
	float* buffer;
	size_t capacity;
	size_t position;
	glm::vec4 tint {1.0f, 1.0f, 1.0f, 1.0f};

	void vertex(float x, float y, float u, float v) {
		vertex(x, y, u, v, tint.r, tint.g, tint.b, tint.a);
	}
	void vertex(float x, float y, float u, float v, float r, float g, float b, float a);
public:
	Batch2D(size_t vertices);
	virtual ~Batch2D();

	void color(float r, float g, float b, float a);
	void rect(float x, float y, float w, float h);

	void flush();
};

#endif /* NECORE_BATCH2D_H_ */
