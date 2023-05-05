#include "../stage/Stage.h"

#include "../g2d/Sprite.h"
#include "Object.h"

#include "../Camera.h"
#include "../Batch2D.h"

#include <iostream>


Stage::Stage(Camera* camera) : camera(camera) {}

Stage::~Stage() {
	for (Object* object : objects) {
		delete object;
	}
	delete camera;
}

Object* Stage::get(int index) {
	return objects[index];
}

void Stage::add(Object* object) {
	objects.push_back(object);
}

void Stage::act(NeContext* context) {
	for (Object* object : objects) {
		if (object && object->callback) {
			object->callback(context, object);
		} else {
			std::cout << "wtf" << std::endl;
		}
	}
}

void Stage::draw(NeContext* context, Batch2D* batch) {
	batch->setCamera(camera);
	for (Object* object : objects) {
		if (object->drawCallback) {
			object->drawCallback(context, batch, object);
		}
	}
}
