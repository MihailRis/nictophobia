#include "../stage/Stage.h"

#include "../g2d/Sprite.h"
#include "Object.h"

#include "../Batch2D.h"


Stage::Stage(Camera* camera) : camera(camera) {}

Stage::~Stage() {
}

Object* Stage::get(int index) {
	return objects[index];
}

void Stage::add(Object* object) {
	objects.push_back(object);
}

void Stage::act(NeContext* context) {
	for (Object* object : objects) {
		if (object->callback) {
			object->callback(context, object);
		}
	}
}

void Stage::draw(NeContext* context, Batch2D* batch) {
	batch->setCamera(camera);
	for (Object* object : objects) {
		batch->draw(object->sprite);
	}
}
