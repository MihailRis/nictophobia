#ifndef NECORE_STAGE_OBJECT_H_
#define NECORE_STAGE_OBJECT_H_

#include <functional>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Object;
class NeContext;
class Batch2D;
class Batch3D;

typedef std::function<void(NeContext*, Batch2D*, Batch3D*, Object*)> draw_func;
typedef std::function<void(NeContext*, Object*)> update_callback;

class Object {
	glm::vec3 position;
	glm::mat4 rotation;
public:
	update_callback callback = nullptr;
	draw_func drawCallback = nullptr;

	Object(glm::vec3 position) : position(position), rotation(1.0f) {}

	void translate(float dx, float dy, float dz) {
		position.x += dx;
		position.y += dy;
		position.z += dz;
	}

	void setPosition(glm::vec3 position) {
		this->position = position;
	}

	void setRotation(glm::mat4 rotation) {
		this->rotation = rotation;
	}

	glm::vec3 getPosition() const {
		return position;
	}

	glm::mat4 getMatrix() const {
		return glm::translate(glm::mat4(1.0f), position) * rotation;
	}
};

#endif /* NECORE_STAGE_OBJECT_H_ */
