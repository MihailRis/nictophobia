#include <iostream>
#include <functional>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "necore/Window.h"
#include "necore/Batch2D.h"
#include "necore/Camera.h"
#include "necore/Texture.h"
#include "necore/Shader.h"
#include "necore/Mesh.h"
#include "necore/NeContext.h"
#include "necore/formats/png_format.h"
#include "necore/formats/obj_format.h"
#include "necore/assets/Assets.h"
#include "necore/assets/AssetsLoader.h"
#include "necore/assets/assets_loading.h"
#include "necore/input/InputProcessor.h"
#include "necore/input/InputBinding.h"
#include "necore/input/input_constants.h"
#include "necore/stage/Stage.h"
#include "necore/stage/Object.h"
#include "miocpp/iopath.h"
#include "necore/Necore.h"
#include "necore/colors.h"
#include "necore/version.h"
#include "necore/Font.h"
#include "necore/FreeTypeFont.h"
#include "necore/debug/FreeCamera.h"
#include "necore/gl/GLTexture.h"
#include "necore/gl/GLMesh.h"
#include "necore/g2d/LMPacker.h"
#include "necore/RasterImage.h"

void queueAssets(AssetsLoader* loader) {
	FreeTypeFontLoader* ftloader = new FreeTypeFontLoader();
	loader->queue("<ftloader>", [ftloader]() {
		return NeResource(SIMPLE, ftloader, [](void* ptr){delete (FreeTypeFontLoader*)ptr;});
	});
	loader->queue("fonts/ubuntu", [ftloader]() {
		FreeTypeFont* font = ftloader->create(iopath("res:UbuntuMono-R.ttf"), 16);
		return NeResource(SIMPLE, font, [](void* ptr){delete (FreeTypeFont*)ptr;});
	});
	loader->queue("textures/font", []() {
		return NeResource(SIMPLE, load_texture(iopath("res:font.png")), [](void* ptr){delete (Texture*)ptr;});
	});
}

inline float area(int x1, int y1, int x2, int y2, int x3, int y3) {
   return abs((x1*(y2-y3) + x2*(y3-y1)+ x3*(y1-y2))/2.0);
}

inline bool isInside(const glm::vec2 p1, const glm::vec2 p2, const glm::vec2 p3, int x, int y) {
   float A = area(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);

   float A1 = area(x, y, p2.x, p2.y, p3.x, p3.y);

   float A2 = area(p1.x, p1.y, x, y, p3.x, p3.y);

   float A3 = area(p1.x, p1.y, p2.x, p2.y, x, y);

   return (A == A1 + A2 + A3);
}

inline float randf(int range) {
	return rand() % range;
}


int buildTheGame(NeContext* context) {
	// setting up stage
	Stage* stage2d = new Stage(new Camera({0, 0, 0}, context->window->getHeight(), false), "shaders/ui");
	context->stage = stage2d;

	context->camera = new Camera(glm::vec3(0, 2, 10), 3.141592/3, true);
	Stage* stage = new Stage(context->camera, "shaders/g3d");
	context->stage3d = stage;

	for (int i = 0; i < 1; i++) {
		Object* object = new Object({i*2, 0, 0});
		glm::vec3 initpos = object->getPosition();
		object->callback = [i, initpos](NeContext*, Object*) {
		};
		object->drawCallback = [](NeContext* context, Batch2D*, Object* object) {
			glm::vec3 position = object->getPosition();
			Shader* shader = (Shader*) context->assets.get("shaders/g3d");
			shader->uniformMatrix("u_model", glm::translate(glm::mat4(1.0f), position));
			Mesh* mesh = (Mesh*)context->assets.get("mesh");
			Texture* texture = (Texture*)context->assets.get("textures/lightmap");
			texture->bind();
			mesh->draw();
		};
		stage->add(object);
	}

	int w = 1024;
	int h = 1024;
	unsigned char* raster = new unsigned char[w * h * 4];
	for (int i = 0; i < w * h * 4; i++) {
		raster[i] = 0;
	}
	RasterImage image(RGBA, {raster}, w, h);

	glm::vec2 dimensions {w,h};
	std::vector<obj_object> objects = load_obj_model(iopath("res:room.obj").readString());
	for (obj_object obj : objects) {
		for (obj_mesh mesh : obj.meshes){
			std::vector<float>& buffer = mesh.data;
			const int vsize = 8;
			const int tcoord_offset = 3;
			// iterate triangles
			float* data = buffer.data();

			unsigned int triangle_c = buffer.size() / vsize / 3;
			std::cout << "faces: " << triangle_c << std::endl;
			uint32_t* sizes = new uint32_t[triangle_c*2];

			glm::vec3** rearranges = new glm::vec3*[triangle_c*3];

			float scale = 30;
			for (unsigned int t = 0; t < triangle_c; t++) {
				glm::vec3* v1 = ((glm::vec3*)(data + (t * 3 + 0) * vsize));
				glm::vec3* v2 = ((glm::vec3*)(data + (t * 3 + 1) * vsize));
				glm::vec3* v3 = ((glm::vec3*)(data + (t * 3 + 2) * vsize));


				/*while (glm::distance(*v1, *v2) < glm::distance(*v1, *v3) || glm::distance(*v1, *v2) < glm::distance(*v2, *v3)) {
					glm::vec3* p1 = v2;
					glm::vec3* p2 = v3;
					glm::vec3* p3 = v1;
					v1 = p1;
					v2 = p2;
					v3 = p3;
				}*/

				// now v1-v2 - is the longest edge
				float th = fmax(1, fmin(glm::distance(*v1, *v2), fmin(glm::distance(*v1, *v3), glm::distance(*v2, *v3))) * scale);
				float tw = fmax(1, fmax(glm::distance(*v1, *v2), fmax(glm::distance(*v1, *v3), glm::distance(*v2, *v3))) * scale);

				rearranges[t * 3 + 0] = v1;
				rearranges[t * 3 + 1] = v2;
				rearranges[t * 3 + 2] = v3;


				sizes[t*2 + 0] = scale;
				sizes[t*2 + 1] = scale;
			}

			LMPacker packer(sizes, triangle_c*2);
			packer.buildCompact(w, h, 1);

			auto rects = packer.getResult();
			for (unsigned int t = 0; t < triangle_c; t++) {
				rectangle rect = rects[t];
				float u1 = rect.x / (float)w;
				float v1 = rect.y / (float)h;
				float u2 = (rect.x+rect.width) / (float)w;
				float v2 = (rect.y+rect.height) / (float)h;

				*(glm::vec2*)(rearranges[t*3+0] + 1) = {u1, v1};
				*(glm::vec2*)(rearranges[t*3+1] + 1) = {u2, v2};
				*(glm::vec2*)(rearranges[t*3+2] + 1) = {u1, v2};
			}

			delete[] rearranges;

			for (unsigned int t = 0; t < triangle_c; t++) {
				glm::vec3 v1 = *((glm::vec3*)(data + (t * 3 + 0) * vsize));
				glm::vec3 v2 = *((glm::vec3*)(data + (t * 3 + 1) * vsize));
				glm::vec3 v3 = *((glm::vec3*)(data + (t * 3 + 2) * vsize));

				glm::vec2 t1 = *((glm::vec2*)(data + (t * 3 + 0) * vsize + tcoord_offset)) * dimensions;
				glm::vec2 t2 = *((glm::vec2*)(data + (t * 3 + 1) * vsize + tcoord_offset)) * dimensions;
				glm::vec2 t3 = *((glm::vec2*)(data + (t * 3 + 2) * vsize + tcoord_offset)) * dimensions;

				float minX = fmin(fmin(t1.x, t2.x), t3.x);
				float minY = fmin(fmin(t1.y, t2.y), t3.y);

				float maxX = fmax(fmax(t1.x, t2.x), t3.x);
				float maxY = fmax(fmax(t1.y, t2.y), t3.y);

				for (int y = minY; y < maxY; y++) {
					for (int x = minX; x < maxX; x++) {
						if (!isInside(t1, t2, t3, x, y)) {
							continue;
						}
						glm::vec2 p = {x, y};

						float w1 = ((t2.y - t3.y) * (p.x - t3.x) + (t3.x - t2.x) * (p.y - t3.y)) /
								   ((t2.y - t3.y) * (t1.x - t3.x) + (t3.x - t2.x) * (t1.y - t3.y));

						float w2 = ((t3.y - t1.y) * (p.x - t3.x) + (t1.x - t3.x) * (p.y - t3.y)) /
								   ((t2.y - t3.y) * (t1.x - t3.x) + (t3.x - t2.x) * (t1.y - t3.y));

						float w3 = 1.0f - w1 - w2;

						glm::vec3 coord = v1 * w1 + v2 * w2 + v3 * w3;
						float d = 1.0f/fmax(0.01f, length(coord));
						d = fmin(1.0f, d);
						glm::vec3 color = {d,d,d};
						//color = {w1, w2, w3};
						color *= 255;
						color = {(x-minX)/(float)(maxX-minX), (y-minY)/(float)(maxY-minY), 0.0f};
						color *= 255;

						raster[(y * w + x) * 4 + 0] = color.r;
						raster[(y * w + x) * 4 + 1] = color.g;
						raster[(y * w + x) * 4 + 2] = color.b;
						raster[(y * w + x) * 4 + 3] = 255;
					}
				}
			}
			vattr_t attrs[] = {{3}, {2}, {3}, {0}};
			Mesh* glmesh = GLMesh::create(buffer.data(), buffer.size() / 8, attrs);
			NeResource res = {SIMPLE, glmesh, [](void* v){delete (Mesh*)v;}};
			context->assets.put("mesh", res);
			//context->assets.put("mesh-"+std::to_string((uint64_t)glmesh), res);
		}
	}
	unsigned char* ebuffer = new unsigned char[w * h * 4];
	for (int k = 0; k < 1; k++) {
		for (int i = 0; i < w * h * 4; i++) {
			ebuffer[i] = raster[i];
		}

		for (int y = 1; y < h-1; y++) {
			for (int x = 1; x < w-1; x++) {
				int index = y * w + x;
				if (ebuffer[index * 4 + 3]){
					for (int r = -1; r <= 1; r++) {
						for (int c = -1; c <= 1; c++) {
							if (!(c|r)){
								continue;
							}
							for (int i = 0; i < 4; i++) {
								raster[((y + r) * w + x + c) * 4 + i] = ebuffer[index * 4 + i];
							}
						}
					}
				}
			}
		}
	}
	delete[] ebuffer;
	iopath("res:output.data").writeBytes(raster, w*h*4);

	Texture* texture = GLTexture::fromImage(&image);
	texture->setSmooth(true);
	context->assets.put("textures/lightmap", NeResource {SIMPLE, texture, [](void* ptr){delete (Texture*)ptr;}});
	context->freeCamera.setCamera(context->camera);

	return 0;
}

void finishTheGame(NeContext* context) {
	delete context->stage;
}

int main(int, char*[]) {
	Necore core;
	NeGameProject project {"test project"};
	project.assets_ask = queueAssets;
	project.build_game = buildTheGame;
	project.destruct_game = finishTheGame;
	if (int status = core.run(&project)) {
		return status;
	}
	return 0;
}
