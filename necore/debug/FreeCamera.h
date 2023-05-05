#ifndef NECORE_DEBUG_FREECAMERA_H_
#define NECORE_DEBUG_FREECAMERA_H_

class Camera;
class NeContext;

class FreeCamera {
	Camera* camera = nullptr;
	float mx = 0.0f;
	float my = 0.0f;
public:
	void setCamera(Camera* camera);
	void update(NeContext* context);
};

#endif /* NECORE_DEBUG_FREECAMERA_H_ */
