#ifndef NECORE_STAGE_STAGE_H_
#define NECORE_STAGE_STAGE_H_

#include <vector>
#include <functional>

class Object;
class NeContext;
class Batch2D;
class Batch3D;
class Camera;

class Stage {
	std::vector<Object*> objects;
	Camera* camera;
	std::string mainShader;
public:
	Stage(Camera* camera, std::string mainShader);
	virtual ~Stage();

	// just for debug
	Object* get(int index);

	void add(Object* object);
	void act(NeContext* context);

	void draw(NeContext* context, Batch2D* batch, Batch3D* batch3d);

	Camera* getCamera() const {
		return camera;
	}
};

#endif /* NECORE_STAGE_STAGE_H_ */
