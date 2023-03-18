#ifndef NECORE_RASTERIMAGE_H_
#define NECORE_RASTERIMAGE_H_

#include "Image.h"

enum raster_format {
	RGB, RGBA
};

union raster_u {
	unsigned char* ubyte;
	float* floats;
};

class RasterImage : public Image {
	raster_format format;
	raster_u raster;
	unsigned int width;
	unsigned int height;
public:
	RasterImage(raster_format format, raster_u raster, unsigned int width, unsigned int height);
	virtual ~RasterImage();

	raster_u getRaster() {
		return raster;
	}

	raster_format getFormat() {
		return format;
	}

	virtual unsigned int getWidth() const;

	virtual unsigned int getHeight() const;
};

#endif /* NECORE_RASTERIMAGE_H_ */
