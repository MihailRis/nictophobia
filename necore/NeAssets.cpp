#include "NeAssets.h"

#include <iostream>

#include "../miocpp/mio.h"
#include "gl/GLTexture.h"
#include "gl/GLShader.h"
#include "formats/png_format.h"
#include "RasterImage.h"
#include "FreeTypeFont.h"

static FreeTypeFontLoader* ftloader = nullptr;

void neassets::create_loaders(Assets* assets) {
	ftloader = new FreeTypeFontLoader();
	assets->put("<ftloader>", NeResource(SIMPLE, ftloader, [](void* ptr){
		delete (FreeTypeFontLoader*)ptr;
		ftloader = nullptr;
	}));
}

resource_loader_func neassets::texture(iopath path) {
	return [=]() {
		return NeResource(SIMPLE, neassets::load_texture(path), [](void* ptr){delete (Texture*)ptr;});
	};
}

resource_loader_func neassets::shader(iopath path) {
	return [=]() {
		return NeResource(SIMPLE, neassets::load_shader(path), [](void* ptr){delete (Shader*)ptr;});
	};
}

resource_loader_func neassets::font(iopath path, int size) {
	return [=]() {
		FreeTypeFont* font = ftloader->create(path, size);
		return NeResource(SIMPLE, font, [](void* ptr){delete (FreeTypeFont*)ptr;});
	};
}

Texture* neassets::load_texture(iopath path) {
	if (!path.isFile()) {
		std::cerr << "file "+path.toStr()+" not found" << std::endl;
		return nullptr;
	}
	size_t datalength;
	unsigned char* bytes = path.readBytes(&datalength);
	RasterImage* image = load_png_image(bytes);
	delete[] bytes;

	Texture* texture = GLTexture::fromImage(image);
	delete image;
	return texture;
}

Shader* neassets::load_shader(iopath path) {
	Shader* shader = GLShader::create(
			path.extended(".glslv").readString(),
			path.extended(".glslf").readString());
	return shader;
}
