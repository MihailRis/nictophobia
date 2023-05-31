#ifndef NECORE_GL_GLMESH_H_
#define NECORE_GL_GLMESH_H_

#include <stdlib.h>
#include <string>
#include <vector>
#include "../common.h"
#include "../Mesh.h"

class MeshData;

class GLMesh : public Mesh {
	uint vao;
	uint vbo;
	uint vertices;
	uint vertexSize;
	MeshData* data;
	GLMesh(unsigned int vao, unsigned int vbo,
		   unsigned int vertices, unsigned int vertexSize, MeshData* data);
public:
	virtual ~GLMesh();

	void reload(const float* buffer, unsigned int vertices);
	void draw(unsigned int primitive);
	void draw();

	MeshData* getData();

	static GLMesh* create(const float* buffer, uint vertices, const vattr_t attrs[], bool stream=true);
	static GLMesh* create(std::string name, std::vector<float> data, uint vertices, const vattr_t attrs[]);
};

#endif /* NECORE_GL_GLMESH_H_ */
