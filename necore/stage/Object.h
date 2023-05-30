#ifndef NECORE_STAGE_OBJECT_H_
#define NECORE_STAGE_OBJECT_H_

#include <functional>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Object;
class NeContext;
class Batch2D;

typedef std::function<void(NeContext*, Batch2D*, Object*)> draw_func;
typedef std::function<void(NeContext*, Object*)> update_callback;

class Object {
	glm::vec3 position;
public:
	update_callback callback = nullptr;
	draw_func drawCallback = nullptr;

	Object(glm::vec3 position) : position(position) {}

	void translate(float dx, float dy, float dz) {
		position.x += dx;
		position.y += dy;
		position.z += dz;
	}

	void setPosition(glm::vec3 position) {
		this->position = position;
	}

	glm::vec3 getPosition() const {
		return position;
	}

	glm::mat4 getMatrix() const {
		return glm::translate(glm::mat4(1.0f), position);
	}
};

#endif /* NECORE_STAGE_OBJECT_H_ */
