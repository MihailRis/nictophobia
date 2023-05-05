
#ifndef NECORE_MESH_H_
#define NECORE_MESH_H_

struct vattr_t {
	unsigned char size;
};

class Mesh {
public:
	virtual ~Mesh();
	virtual void reload(const float* buffer, unsigned int vertices) = 0;
	virtual void draw(unsigned int primitive) = 0;
	virtual void draw() = 0;
};

#endif /* NECORE_MESH_H_ */
