#ifndef NECORE_GLTEXTURE_H_
#define NECORE_GLTEXTURE_H_

#include "../Texture.h"

class RasterImage;

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
	void setSmooth(bool flag);

	static GLTexture* fromImage(RasterImage* image);
};

#endif /* NECORE_GLTEXTURE_H_ */
