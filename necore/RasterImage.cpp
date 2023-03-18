#include "RasterImage.h"

RasterImage::RasterImage(raster_format format, raster_u raster, unsigned int width, unsigned int height)
	: format(format), raster(raster), width(width), height(height) {
}

RasterImage::~RasterImage() {
	delete[] raster.ubyte;
}

unsigned int RasterImage::getWidth() const {
	return width;
}

unsigned int RasterImage::getHeight() const {
	return height;
}
