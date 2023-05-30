#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <functional>

#include "miocpp/iopath.h"
#include "necore/assets/Assets.h"
#include "necore/assets/AssetsLoader.h"
#include "necore/Camera.h"
#include "necore/debug/FreeCamera.h"
#include "necore/Mesh.h"
#include "necore/NeAssets.h"
#include "necore/Necore.h"
#include "necore/NeContext.h"
#include "necore/stage/Object.h"
#include "necore/stage/Stage.h"
#include "necore/Window.h"

void queueAssets(AssetsLoader* loader) {
	loader->queue("fonts/ubuntu", neassets::font(iopath("res:UbuntuMono-R.ttf"), 16));
	loader->queue("textures/font", neassets::texture(iopath("res:font.png")));
	loader->queue("meshes/cube", neassets::mesh(iopath("res:cube.obj")));
}


int buildTheGame(NeContext* context) {
	Stage* stage2d = new Stage(new Camera({0, 0, 0}, context->window->getHeight(), false), "shaders/ui");
	context->stage = stage2d;

	context->camera = new Camera(glm::vec3(0, 2, 10), 3.141592/3, true);
	Stage* stage = new Stage(context->camera, "shaders/g3d");
	context->stage3d = stage;

	Object* object = new Object({0, 0, 0});
	object->callback = [](NeContext*, Object*) {
	};
	object->drawCallback = [](NeContext* context, Batch2D*, Object*) {
		Mesh* mesh = (Mesh*) context->assets.get("meshes/cube");
		mesh->draw();
	};
	stage->add(object);
	context->freeCamera.setCamera(context->camera);
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
