#include "Necore.h"

#include "Window.h"
#include "Batch2D.h"
#include "NeContext.h"
#include "stage/Stage.h"
#include "gl/GLWindow.h"
#include "../miocpp/mio.h"
#include "../miocpp/DirDevice.h"
#include "Shader.h"
#include "assets/assets_loading.h"

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
		Shader* shader = load_shader(path);
		return NeResource(SIMPLE, shader, [](void* ptr){delete (Shader*)ptr;});
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
	Window* window = GLWindow::create(900, 200, title.c_str());
	NeContext* context = new NeContext(window);

	// loading assets
	AssetsLoader loader;
	queue_default_assets(&loader);
	project->assets_ask(&loader);
	if (int status = loader.performAll(&context->assets)) {
		std::cerr << "fatal error: could not to load assets" << std::endl;
		return status;
	}

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
		window->pollEvents();
		context->bindings.update();

		context->stage->act(context);

		window->clear();
		batch.begin(window, &context->assets);
		batch.setShader("shaders/ui");
		context->stage->draw(context, &batch);
		batch.end();

		window->swapBuffers();
	}
}
