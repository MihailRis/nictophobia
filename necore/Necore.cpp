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

int Necore::run(assets_asker_func assets_ask,
		build_game_func build_game,
		destruct_game_func destruct_game,
		const char* window_title) {
	// setting up filesystem
	mio::add_device("res", new DirDevice("res"));

	Window* window = GLWindow::create(900, 600, window_title);
	NeContext* context = new NeContext(window);


	// loading assets
	AssetsLoader loader;
	assets_ask(&loader);
	if (int status = loader.performAll(&context->assets)) {
		std::cerr << "fatal error: could not to load assets" << std::endl;
		return status;
	}

	if (int status = build_game(context)){
		return status;
	}
	mainloop(context);
	destruct_game(context);

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
