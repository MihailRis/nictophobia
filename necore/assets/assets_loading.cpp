#include "assets_loading.h"

#include <iostream>

#include "../../miocpp/mio.h"
#include "../gl/GLTexture.h"
#include "../gl/GLShader.h"
#include "../formats/png_format.h"
#include "../RasterImage.h"

Texture* load_texture(iopath path) {
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

Shader* load_shader(iopath path) {
	Shader* shader = GLShader::create(
			path.extended(".glslv").readString(),
			path.extended(".glslf").readString());
	return shader;
}
