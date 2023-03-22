#include <iostream>
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
#include "necore/gl/GLWindow.h"
#include "necore/gl/GLMesh.h"
#include "miocpp/iopath.h"
#include "miocpp/DirDevice.h"
#include "miocpp/mio.h"


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
	mio::add_device("res", new DirDevice("res"));

	AssetsLoader loader;
	queueAssets(&loader);
	if (int status = loader.performAll(&context->assets)) {
		std::cerr << "fatal error: could not to load assets" << std::endl;
		return status;
	}
	std::cout << "assets loaded successfully" << std::endl;

	InputProcessor* processor = new InputProcessor();
	context->window->setInputProcessor(processor);

	InputBindings<std::string>* bindings = &context->bindings;
	bindings->bind("up", [processor](){return processor->pressed(NC_KEY_W);});
	bindings->bind("down", [processor](){return processor->pressed(NC_KEY_S);});
	bindings->bind("left", [processor](){return processor->pressed(NC_KEY_A);});
	bindings->bind("right", [processor](){return processor->pressed(NC_KEY_D);});
	return 0;
}

// todo: remove
void finishTheGame(NeContext* context) {
	delete mio::pop_device("res");
	delete context->window->getInputProcessor();
	context->window->setInputProcessor(nullptr);
}

int main(int argc, char **argv) {
	Window* window = GLWindow::create(900, 600, "<example>");
	NeContext* context = new NeContext(window);
	window->swapInterval(1);

	if (int status = buildTheGame(context)){
		return status;
	}

	Batch2D batch(1024);
	Camera camera({0, 0, 0}, 1.0f, false);

	float x = 200;
	float y = 200;
	float speed = 5.0f;

	while (!window->shouldClose()) {
		window->pollEvents();
		context->bindings.update();

		if (context->bindings.isActive("up")) {y += speed;};
		if (context->bindings.isActive("down")) {y -= speed;};
		if (context->bindings.isActive("left")) {x -= speed;};
		if (context->bindings.isActive("right")) {x += speed;};

		// draw part
		int w = window->getWidth();
		int h = window->getHeight();

		camera.setFov(h);

		window->clear();
		batch.begin(&context->assets);
		batch.setShader("shaders/ui");
		batch.setCamera((float)w/(float)h, &camera);
		batch.texture("textures/test");
		batch.rect(x, y, 260, 160);
		batch.flush();

		window->swapBuffers();
	}
	finishTheGame(context);
	delete context;
	delete window;
	return 0;
}
