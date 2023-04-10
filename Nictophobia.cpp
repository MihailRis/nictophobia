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
#include "necore/Font.h"
#include "necore/FreeTypeFont.h"

void queueAssets(AssetsLoader* loader) {
	FreeTypeFontLoader* ftloader = new FreeTypeFontLoader();
	loader->queue("<ftloader>", [ftloader]() {
		return NeResource(SIMPLE, ftloader, [](void* ptr){delete (FreeTypeFontLoader*)ptr;});
	});
	loader->queue("fonts/ubuntu", [ftloader]() {
		FreeTypeFont* font = ftloader->create(iopath("res:UbuntuMono-R.ttf"), 16);
		return NeResource(SIMPLE, font, [](void* ptr){delete (FreeTypeFont*)ptr;});
	});
}

int buildTheGame(NeContext* context) {
	// setting up input
	InputProcessor* processor = context->window->getInputProcessor();
	InputBindings<std::string>* bindings = &context->bindings;
	bindings->bind("up", [processor](){return processor->pressed(NC_KEY_W) || processor->pressed(NC_KEY_UP);});
	bindings->bind("down", [processor](){return processor->pressed(NC_KEY_S) || processor->pressed(NC_KEY_DOWN);});
	bindings->bind("left", [processor](){return processor->pressed(NC_KEY_A) || processor->pressed(NC_KEY_LEFT);});
	bindings->bind("right", [processor](){return processor->pressed(NC_KEY_D) || processor->pressed(NC_KEY_RIGHT);});

	// setting up stage
	Stage* stage = new Stage(new Camera({0, 0, 0}, 200.0f, false));
	context->stage = stage;

	Object* object = new Object({10, 150, 0});
	object->callback = [](NeContext* context, Object* object) {
		glm::vec2 motion {0.0f, 0.0f};
		float speed = 5.0f;
		if (context->bindings.isActive("up")) {motion.y += speed;};
		if (context->bindings.isActive("down")) {motion.y -= speed;};
		if (context->bindings.isActive("left")) {motion.x -= speed;};
		if (context->bindings.isActive("right")) {motion.x += speed;};
		object->translate(motion.x, motion.y, 0.0f);
	};
	std::string sourcetext = iopath("res:ui.glslf").readString();
	wchar_t* chars = new wchar_t[sourcetext.length()+1];
	for (int i = 0; i < sourcetext.length(); i++) {
		chars[i] = sourcetext[i];
	}
	chars[sourcetext.length()] = '\0';
	std::wstring text(chars);
	delete[] chars;

	object->draw2d = [text](NeContext* context, Batch2D* batch, Object* object) {
		glm::vec3 position = object->getPosition();
		batch->drawText("fonts/ubuntu",
				text,
				position.x, position.y, true, true, context->timer / 1000.0f);
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
