#include "Necore.h"

#include "Window.h"
#include "Batch2D.h"
#include "NeContext.h"
#include "stage/Stage.h"

Necore::Necore() {

}

Necore::~Necore() {

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
