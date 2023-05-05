#ifndef NECORE_GL_GLMESH_H_
#define NECORE_GL_GLMESH_H_

#include <stdlib.h>
#include "../Mesh.h"

class GLMesh : public Mesh {
	unsigned int vao;
	unsigned int vbo;
	unsigned int vertices;
	unsigned int vertexSize;
public:
	GLMesh(unsigned int vao, unsigned int vbo,
		   unsigned int vertices, unsigned int vertexSize);
	virtual ~GLMesh();

	void reload(const float* buffer, unsigned int vertices);
	void draw(unsigned int primitive);
	void draw();

	static GLMesh* create(const float* buffer, unsigned int vertices, const vattr_t attrs[]);
};

#endif /* NECORE_GL_GLMESH_H_ */
