#ifndef NECORE_GLTEXTURE_H_
#define NECORE_GLTEXTURE_H_

#include "../Texture.h"

class GLTexture: public Texture {
	unsigned int id;
	int width;
	int height;
public:
	GLTexture(unsigned int id, int width, int height);
	virtual ~GLTexture();

	int getWidth() const;
	int getHeight() const;
	void bind();
};

#endif /* NECORE_GLTEXTURE_H_ */
