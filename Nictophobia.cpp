#include <iostream>


#include "necore/Window.h"
#include "necore/Batch2D.h"
#include "necore/Camera.h"
#include "necore/RasterImage.h"
#include "necore/Texture.h"
#include "necore/NeContext.h"
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
#include "miocpp/mio.h"

#include <glm/glm.hpp>

Texture* load_texture(iopath);
Shader* load_shader(iopath);

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

void buildTheGame(NeContext* context) {
	mio::add_device("res", new DirDevice("res"));

	AssetsLoader loader;
	queueAssets(&loader);
	loader.performAll(&context->assets);

	InputProcessor* processor = new InputProcessor();
	context->window->setInputProcessor(processor);

	InputBindings<std::string>* bindings = &context->bindings;
	bindings->bind("up", [processor](){return processor->pressed(NC_KEY_W);});
	bindings->bind("down", [processor](){return processor->pressed(NC_KEY_S);});
	bindings->bind("left", [processor](){return processor->pressed(NC_KEY_A);});
	bindings->bind("right", [processor](){return processor->pressed(NC_KEY_D);});
}

void finishTheGame(NeContext* context) {
	delete mio::pop_device("res");
	delete context->window->getInputProcessor();
	context->window->setInputProcessor(nullptr);
}


int main(int argc, char **argv) {
	Window* window = GLWindow::create(900, 600, "<example>");
	NeContext* context = new NeContext(window);
	buildTheGame(context);

	Batch2D batch(1024);
	window->swapInterval(1);

	Texture* texture = (Texture*)context->assets.get("textures/test");
	Shader* shader = (Shader*)context->assets.get("shaders/ui");

	Camera camera({0, 0, 0}, 1.0f, false);

	float x = 200;
	float y = 200;

	while (!window->shouldClose()) {
		window->pollEvents();
		context->bindings.update();

		float speed = 5.0f;
		if (context->bindings.isActive("up")) {y += speed;};
		if (context->bindings.isActive("down")) {y -= speed;};
		if (context->bindings.isActive("left")) {x -= speed;};
		if (context->bindings.isActive("right")) {x += speed;};

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
	finishTheGame(context);
	delete context;
	delete window;
	return 0;
}

Texture* load_texture(iopath path) {
	size_t datalength;
	unsigned char* bytes = path.readBytes(&datalength);
	RasterImage* image = load_png_image(bytes);
	delete[] bytes;

	Texture* texture = GLTexture::fromImage(image);
	delete image;
	return texture;
}

Shader* load_shader(iopath path) {
	Shader* shader = GLShader::create(
			path.extended(".glslv").readString(),
			path.extended(".glslf").readString());
	return shader;
}
