#include "Necore.h"

#include <chrono>
#include "Window.h"
#include "Batch2D.h"
#include "Mesh.h"
#include "NeContext.h"
#include "Camera.h"
#include "input/InputProcessor.h"
#include "stage/Stage.h"
#include "gl/GLWindow.h"
#include "../miocpp/mio.h"
#include "../miocpp/DirDevice.h"
#include "Shader.h"
#include "input/input_constants.h"
#include "NeAssets.h"

#include "version.h"

Necore::Necore() {

}

Necore::~Necore() {

}

void queue_default_assets(AssetsLoader* loader) {
	loader->queue("shaders/ui", [](){
		iopath path("res:ui");
		if (!path.isFile()) {
			path = iopath("def:ui");
		}
		return neassets::shader(path)();
	});

	loader->queue("shaders/g3d", [](){
		iopath path("res:ui");
		if (!path.isFile()) {
			path = iopath("def:g3d");
		}
		return neassets::shader(path)();
	});
}

inline std::string build_title(std::string name) {
	return name + " [nictophobia v" + NE_VERSION_STRING +
			" (" + __DATE__ + " " + __TIME__ + ")]";
}

int Necore::run(NeGameProject* project) {
	mio::add_device("def", new DirDevice("res")); // it's not a mistake
	mio::add_device("res", new DirDevice("res"));

	std::string title = build_title(project->name);
	Window* window = GLWindow::create(project->init_window_width, project->init_window_height, title.c_str());
	NeContext* context = new NeContext(window);

	InputBindings<std::string>* bindings = &context->bindings;
	InputProcessor* processor = context->window->getInputProcessor();
	bindings->bind("core:exit", [processor, window](){return processor->pressed(NC_KEY_ESCAPE);});
	bindings->bind("core:toggle_cursor", [processor, window](){return processor->pressed(NC_KEY_TAB);});
	bindings->bind("core:up", [processor](){return processor->pressed(NC_KEY_W) || processor->pressed(NC_KEY_UP);});
	bindings->bind("core:down", [processor](){return processor->pressed(NC_KEY_S) || processor->pressed(NC_KEY_DOWN);});
	bindings->bind("core:left", [processor](){return processor->pressed(NC_KEY_A) || processor->pressed(NC_KEY_LEFT);});
	bindings->bind("core:right", [processor](){return processor->pressed(NC_KEY_D) || processor->pressed(NC_KEY_RIGHT);});
	bindings->bind("core:elevate", [processor](){return processor->pressed(NC_KEY_SPACE);});
	bindings->bind("core:lower", [processor](){return processor->pressed(NC_KEY_LEFT_SHIFT);});

	bindings->hotkey("core:exit", [window](){window->setShouldClose(true);});
	bindings->hotkey("core:toggle_cursor", [window](){window->setCursorVisibility(!window->isCursorVisible());});

	// loading assets
	neassets::create_loaders(&context->assets);
	AssetsLoader loader;
	queue_default_assets(&loader);
	project->assets_ask(&loader);
	if (int status = loader.performAll(&context->assets)) {
		std::cerr << "fatal error: could not to load assets" << std::endl;
		return status;
	}
	std::cout << "assets loaded successfully" << std::endl;
	context->assets.cleanUp();

	if (int status = project->build_game(context)){
		return status;
	}
	mainloop(context);

	project->destruct_game(context);
	delete mio::pop_device("res");
	delete mio::pop_device("def");
	delete context;
	delete window;
	return 0;
}

void Necore::mainloop(NeContext* context) {
	Window* window = context->window;

	Batch2D batch(1024);

	while (!window->shouldClose()) {
		context->timer += 16;

		auto start = std::chrono::high_resolution_clock::now();
		window->pollEvents();
		context->bindings.update();
		context->freeCamera.update(context);
		context->stage->act(context);
		context->stage3d->act(context);
		auto elapsed = std::chrono::high_resolution_clock::now() - start;
		context->frameTimeMicros = std::chrono::duration_cast<std::chrono::microseconds>(
		        elapsed).count();

		window->clear();

		window->setDepthTest(true);
		batch.begin(window, &context->assets);
		batch.setShader("shaders/ui");

		context->stage3d->draw(context, &batch);

		window->setDepthTest(false);
		batch.begin(window, &context->assets);
		batch.setShader("shaders/ui");
		context->stage->draw(context, &batch);
		batch.end();
		window->swapBuffers();
	}
}
