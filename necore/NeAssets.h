#ifndef NECORE_NEASSETS_H_
#define NECORE_NEASSETS_H_

#include "assets/AssetsLoader.h"

class iopath;
class Texture;
class Shader;
class FreeTypeFontLoader;
class Assets;

namespace neassets {
	void create_loaders(Assets* assets);
	resource_loader_func texture(iopath);
	resource_loader_func shader(iopath);
	resource_loader_func font(iopath, int size);


	Texture* load_texture(iopath);
	Shader* load_shader(iopath);

};

#endif /* NECORE_NEASSETS_H_ */
