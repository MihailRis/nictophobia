#include <iostream>
#include <functional>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "necore/Window.h"
#include "necore/Batch2D.h"
#include "necore/Camera.h"
#include "necore/Texture.h"
#include "necore/Shader.h"
#include "necore/Mesh.h"
#include "necore/NeContext.h"
#include "necore/formats/png_format.h"
#include "necore/formats/obj_format.h"
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
#include "necore/debug/FreeCamera.h"
#include "necore/gl/GLTexture.h"
#include "necore/gl/GLMesh.h"
#include "necore/g2d/LMPacker.h"
#include "necore/RasterImage.h"

void queueAssets(AssetsLoader* loader) {
	FreeTypeFontLoader* ftloader = new FreeTypeFontLoader();
	loader->queue("<ftloader>", [ftloader]() {
		return NeResource(SIMPLE, ftloader, [](void* ptr){delete (FreeTypeFontLoader*)ptr;});
	});
	loader->queue("fonts/ubuntu", [ftloader]() {
		FreeTypeFont* font = ftloader->create(iopath("res:UbuntuMono-R.ttf"), 16);
		return NeResource(SIMPLE, font, [](void* ptr){delete (FreeTypeFont*)ptr;});
	});
	loader->queue("textures/font", []() {
		return NeResource(SIMPLE, load_texture(iopath("res:font.png")), [](void* ptr){delete (Texture*)ptr;});
	});
}


int buildTheGame(NeContext* context) {
	// setting up stage
	Stage* stage2d = new Stage(new Camera({0, 0, 0}, context->window->getHeight(), false), "shaders/ui");
	context->stage = stage2d;

	context->camera = new Camera(glm::vec3(0, 2, 10), 3.141592/3, true);
	Stage* stage = new Stage(context->camera, "shaders/g3d");
	context->stage3d = stage;

	for (int i = 0; i < 1; i++) {
		Object* object = new Object({i*2, 0, 0});
		glm::vec3 initpos = object->getPosition();
		object->callback = [i, initpos](NeContext*, Object*) {
		};
		object->drawCallback = [](NeContext* context, Batch2D*, Object* object) {
			glm::vec3 position = object->getPosition();
			Shader* shader = (Shader*) context->assets.get("shaders/g3d");
			shader->uniformMatrix("u_model", glm::translate(glm::mat4(1.0f), position));
		};
		stage->add(object);
	}

	return 0;
}

void finishTheGame(NeContext* context) {
	delete context->stage;
}

int main(int, char*[]) {
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
