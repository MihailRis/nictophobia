#ifndef NECORE_CAMERA_H_
#define NECORE_CAMERA_H_

#include <glm/glm.hpp>

class Camera {
	void updateVectors();
	glm::vec3 front {0, 0, -1};
	glm::vec3 up {0, 1, 0};
	glm::vec3 right {-1, 0, 0};
	glm::vec3 position;
	glm::mat4 rotation {1.0f};
	float fov;
	bool perspective;
	bool flipped;
	float zoom = 1.0f;
public:
	Camera(glm::vec3 position, float fov, bool perspective);

	glm::mat4 getProjection(float aspect);
	glm::mat4 getView();

	void setFlipped(bool flag) {
		flipped = flag;
	}

	void setFov(float fov);
	glm::vec3 getPosition() const;
	void setPosition(glm::vec3 position);

	void rotate(float x, float y, float z);
	void setRotation(glm::mat4 rotation) {
		this->rotation = rotation;
	}

	void translate(glm::vec3 delta) {
		position += delta;
	}

	glm::vec3 getFront() const {
		return front;
	}

	glm::vec3 getRight() const {
		return right;
	}

	glm::vec3 getUp() const {
		return up;
	}
};

#endif /* NECORE_CAMERA_H_ */
