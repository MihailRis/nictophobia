#ifndef NECORE_STAGE_OBJECT_H_
#define NECORE_STAGE_OBJECT_H_

#include <functional>
#include <glm/glm.hpp>

class Object;
class NeContext;
class Batch2D;

typedef std::function<void(NeContext*, Batch2D*, Object*)> draw2d_func;
typedef std::function<void(NeContext*, Object*)> update_callback;

class Object {
	glm::vec3 position;
public:
	update_callback callback = nullptr;
	draw2d_func draw2d = nullptr;

	Object(glm::vec3 position) : position(position) {}

	void translate(float dx, float dy, float dz) {
		position.x += dx;
		position.y += dy;
		position.z += dz;
	}

	glm::vec3 getPosition() const {
		return position;
	}
};

#endif /* NECORE_STAGE_OBJECT_H_ */
