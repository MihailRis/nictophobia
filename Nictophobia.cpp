#include <iostream>


#include "necore/Window.h"
#include "necore/Batch2D.h"
#include "necore/Camera.h"
#include "necore/input/InputProcessor.h"
#include "necore/input/InputBinding.h"
#include "necore/input/input_constants.h"
#include "necore/gl/GLWindow.h"
#include "necore/gl/GLShader.h"
#include "necore/gl/GLMesh.h"
#include "miocpp/iopath.h"
#include "miocpp/DirDevice.h"

#include <glm/glm.hpp>


int main(int argc, char **argv) {
	DirDevice device("res");

	Window* window = GLWindow::create(900, 600, "<example>");
	Shader* shader = GLShader::create(
			device.readString("ui.glslv"),
			device.readString("ui.glslf"));

	Batch2D batch(1024);
	InputProcessor processor;
	window->setInputProcessor(&processor);
	window->swapInterval(1);

	Camera camera({0, 0, 0}, 1.0f, false);
	InputProcessor* processorPtr = &processor;
	InputBinding binding {[processorPtr](){return processorPtr->pressed(NC_KEY_W);}};

	while (!window->shouldClose()) {
		window->pollEvents();
		binding.update();
		int w = window->getWidth();
		int h = window->getHeight();
		camera.setFov(h);
		window->clear();

		shader->use();
		shader->uniformMatrix("u_proj", camera.getProjection(
				(float)w/(float)h
		));
		shader->uniformMatrix("u_view", camera.getView());

		batch.rect(w/2-50, h/2-50, 100, 100);
		batch.flush();

		window->swapBuffers();
	}
	delete shader;
	delete window;
	return 0;
}
