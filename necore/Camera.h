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
	bool perspective;
	bool flipped;
	float fov;
	float zoom = 1.0f;
public:
	Camera(glm::vec3 position, float fov, bool perspective);

	glm::mat4 getProjection(float aspect);
	glm::mat4 getView();

	void setFov(float fov);
	glm::vec3 getPosition() const;
	void setPosition(glm::vec3 position);

	void rotate(float x, float y, float z);
};

#endif /* NECORE_CAMERA_H_ */
