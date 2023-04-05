#include <iostream>
#include <functional>
#include <glm/glm.hpp>
#include "necore/Window.h"
#include "necore/Batch2D.h"
#include "necore/Camera.h"
#include "necore/Texture.h"
#include "necore/Shader.h"
#include "necore/NeContext.h"
#include "necore/formats/png_format.h"
#include "necore/assets/Assets.h"
#include "necore/assets/AssetsLoader.h"
#include "necore/assets/assets_loading.h"
#include "necore/input/InputProcessor.h"
#include "necore/input/InputBinding.h"
#include "necore/input/input_constants.h"
#include "necore/stage/Stage.h"
#include "necore/stage/Object.h"
#include "miocpp/iopath.h"
#include "necore/Necore.h"
#include "necore/colors.h"
#include "necore/version.h"

void queueAssets(AssetsLoader* loader) {
	loader->queue("textures/test", [](){
		Texture* texture = load_texture(iopath("res:test.png"));
		return NeResource(SIMPLE, texture, [](void* ptr){delete (Texture*)ptr;});
	});
	loader->queue("shaders/ui", [](){
		Shader* shader = load_shader(iopath("res:ui"));
		return NeResource(SIMPLE, shader, [](void* ptr){delete (Shader*)ptr;});
	});
}

int buildTheGame(NeContext* context) {
	std::cout << "assets loaded successfully" << std::endl;

	// setting up input
	InputProcessor* processor = context->window->getInputProcessor();
	InputBindings<std::string>* bindings = &context->bindings;
	bindings->bind("up", [processor](){return processor->pressed(NC_KEY_W) || processor->pressed(NC_KEY_UP);});
	bindings->bind("down", [processor](){return processor->pressed(NC_KEY_S) || processor->pressed(NC_KEY_DOWN);});
	bindings->bind("left", [processor](){return processor->pressed(NC_KEY_A) || processor->pressed(NC_KEY_LEFT);});
	bindings->bind("right", [processor](){return processor->pressed(NC_KEY_D) || processor->pressed(NC_KEY_RIGHT);});

	// setting up stage
	Stage* stage = new Stage(new Camera({0, 0, 0}, 600.0f, false));
	context->stage = stage;

	Object* object = new Object({200, 200, 0});
	object->callback = [](NeContext* context, Object* object) {
		glm::vec2 motion {0.0f, 0.0f};
		float speed = 5.0f;
		if (context->bindings.isActive("up")) {motion.y += speed;};
		if (context->bindings.isActive("down")) {motion.y -= speed;};
		if (context->bindings.isActive("left")) {motion.x -= speed;};
		if (context->bindings.isActive("right")) {motion.x += speed;};
		object->translate(motion.x, motion.y, 0.0f);
	};
	object->draw2d = [](NeContext* context, Batch2D* batch, Object* object) {
		glm::vec3 position = object->getPosition();
		batch->texture("textures/test");
		batch->rect(position.x, position.y, 260, 160, 0.5f, 0.5f, 0, uvregion(), false, false, COLOR_WHITE);
	};
	stage->add(object);

	return 0;
}

void finishTheGame(NeContext* context) {
	delete context->stage;
}

int main(int argc, char* argv[]) {
	Necore core;
	NeGameProject project {"test project"};
	project.assets_ask = queueAssets;
	project.build_game = buildTheGame;
	project.destruct_game = finishTheGame;
	if (int status = core.run(&project)) {
		return status;
	}
	return 0;
}
