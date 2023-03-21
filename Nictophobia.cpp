#include <iostream>


#include "necore/Window.h"
#include "necore/Batch2D.h"
#include "necore/Camera.h"
#include "necore/RasterImage.h"
#include "necore/Texture.h"
#include "necore/formats/png_format.h"
#include "necore/assets/Assets.h"
#include "necore/assets/AssetsLoader.h"
#include "necore/input/InputProcessor.h"
#include "necore/input/InputBinding.h"
#include "necore/input/input_constants.h"
#include "necore/gl/GLWindow.h"
#include "necore/gl/GLShader.h"
#include "necore/gl/GLMesh.h"
#include "necore/gl/GLTexture.h"
#include "miocpp/iopath.h"
#include "miocpp/DirDevice.h"

#include <glm/glm.hpp>

int main(int argc, char **argv) {
	DirDevice device("res");
	DirDevice* devicePtr = &device;

	Window* window = GLWindow::create(900, 600, "<example>");
	Shader* shader = GLShader::create(
			device.readString("ui.glslv"),
			device.readString("ui.glslf"));

	Batch2D batch(1024);
	InputProcessor processor;
	window->setInputProcessor(&processor);
	window->swapInterval(1);


	Assets assets;
	AssetsLoader loader;
	loader.queue("textures/test", [devicePtr](){
		size_t datalength;
		unsigned char* bytes = devicePtr->readBytes("test.png", datalength);
		RasterImage* image = load_png_image(bytes);
		delete[] bytes;

		Texture* texture = GLTexture::fromImage(image);
		delete image;
		return NeResource(SIMPLE, texture, [](void* ptr){delete (Texture*)ptr;});
	});
	loader.performAll(&assets);

	Texture* texture = (Texture*)assets.get("textures/test");


	Camera camera({0, 0, 0}, 1.0f, false);
	InputProcessor* processorPtr = &processor;

	InputBindings<std::string> bindings;
	bindings.bind("up", [processorPtr](){return processorPtr->pressed(NC_KEY_W);});
	bindings.bind("down", [processorPtr](){return processorPtr->pressed(NC_KEY_S);});
	bindings.bind("left", [processorPtr](){return processorPtr->pressed(NC_KEY_A);});
	bindings.bind("right", [processorPtr](){return processorPtr->pressed(NC_KEY_D);});

	float x = 200;
	float y = 200;

	while (!window->shouldClose()) {
		window->pollEvents();
		bindings.update();

		float speed = 5.0f;
		if (bindings.isActive("up")) {y += speed;};
		if (bindings.isActive("down")) {y -= speed;};
		if (bindings.isActive("left")) {x -= speed;};
		if (bindings.isActive("right")) {x += speed;};

		int w = window->getWidth();
		int h = window->getHeight();
		camera.setFov(h);

		window->clear();

		shader->use();
		shader->uniformMatrix("u_proj", camera.getProjection(
				(float)w/(float)h
		));
		shader->uniformMatrix("u_view", camera.getView());

		batch.rect(x, y, 260, 160);
		texture->bind();
		batch.flush();

		window->swapBuffers();
	}
	delete shader;
	delete window;
	return 0;
}
