#ifndef NECORE_STAGE_STAGE_H_
#define NECORE_STAGE_STAGE_H_

#include <vector>

class Object;
class NeContext;
class Batch2D;
class Camera;

class Stage {
	std::vector<Object*> objects;
	Camera* camera;
public:
	Stage(Camera* camera);
	virtual ~Stage();

	// just for debug
	Object* get(int index);

	void add(Object* object);
	void act(NeContext* context);

	void draw(NeContext* context, Batch2D* batch);

	Camera* getCamera() const {
		return camera;
	}
};

#endif /* NECORE_STAGE_STAGE_H_ */