#include "../stage/Stage.h"

#include "../g2d/Sprite.h"
#include "Object.h"

#include "../Camera.h"
#include "../Batch2D.h"
#include "../NeContext.h"
#include "../Camera.h"
#include "../Window.h"
#include "../Shader.h"

#include <iostream>


Stage::Stage(Camera* camera, std::string mainShader) : camera(camera), mainShader(mainShader) {}

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
		}
	}
}

void Stage::draw(NeContext* context, Batch2D* batch) {
	Shader* shader = (Shader*)context->assets.get("shaders/g3d");
	shader->use();
	shader->uniformMatrix("u_proj", camera->getProjection(context->window->getRatio()));
	shader->uniformMatrix("u_view", camera->getView());
	batch->setCamera(camera);
	for (Object* object : objects) {
		if (object->drawCallback) {
			shader->uniformMatrix("u_model", object->getMatrix());
			object->drawCallback(context, batch, object);
		}
	}
}
