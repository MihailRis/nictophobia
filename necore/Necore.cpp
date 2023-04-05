#include "Necore.h"

#include "Window.h"
#include "Batch2D.h"
#include "NeContext.h"
#include "stage/Stage.h"
#include "gl/GLWindow.h"
#include "../miocpp/mio.h"
#include "../miocpp/DirDevice.h"

#include "version.h"

Necore::Necore() {

}

Necore::~Necore() {

}

inline std::string build_title(std::string name) {
	return name + " [nictophobia v" + NE_VERSION_STRING + " (" + __DATE__ + " " + __TIME__ + ")]";
}

int Necore::run(NeGameProject* project) {
	mio::add_device("res", new DirDevice("res"));

	std::string title = build_title(project->name);
	Window* window = GLWindow::create(900, 600, title.c_str());
	NeContext* context = new NeContext(window);


	// loading assets
	AssetsLoader loader;
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
	delete context;
	delete window;
	return 0;
}

void Necore::mainloop(NeContext* context) {
	Window* window = context->window;

	Batch2D batch(1024);

	while (!window->shouldClose()) {
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
