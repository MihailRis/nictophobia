#ifndef NECORE_STAGE_OBJECT_H_
#define NECORE_STAGE_OBJECT_H_

#include <functional>

class Object;
class NeContext;

typedef std::function<void(NeContext*, Object*)> update_callback;

class Sprite;

class Object {
public:
	Sprite* sprite;
	update_callback callback = nullptr;

	Object(Sprite* sprite) : sprite(sprite) {}
};

#endif /* NECORE_STAGE_OBJECT_H_ */
