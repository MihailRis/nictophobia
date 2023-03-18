#include "png_format.h"

#include <png.h>
#include "../RasterImage.h"

#include <iostream>
using namespace std;

void _read_from_bytes_fn(png_structp png_ptr, png_bytep out, png_size_t length){
	png_voidp io_ptr = png_get_io_ptr(png_ptr);
	if(io_ptr == NULL)
		return;
	unsigned char** input = (unsigned char**)io_ptr;
	for (int i = 0; i < length; i++) {
		out[i] = (*input)[i];
	}
	*input += length;
}

RasterImage* load_png_image(unsigned char* data){
    if (png_sig_cmp(data, 0, 8)) {
        return nullptr;
    }
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL,  NULL, NULL);
    if (!png_ptr) {
        return nullptr;
    }
    png_infop info_ptr = png_create_info_struct( png_ptr );
    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, (png_infopp) NULL, (png_infopp) NULL);
        return nullptr;
    }
    png_infop end_info = png_create_info_struct( png_ptr );
    if (!end_info) {
        png_destroy_read_struct(&png_ptr, (png_infopp) NULL, (png_infopp) NULL);
        return nullptr;
    }
    if (setjmp(png_jmpbuf( png_ptr ))) {
        png_destroy_read_struct( &png_ptr, &info_ptr, &end_info );
        return nullptr;
    }

    unsigned char** ptr = &data;
    *ptr += 8;
    png_set_read_fn(png_ptr, ptr, _read_from_bytes_fn);
    png_set_sig_bytes( png_ptr, 8 );
    png_read_info(png_ptr, info_ptr);

    png_uint_32 t_width, t_height;
    int bit_depth, color_type, row_bytes;
    png_get_IHDR( png_ptr, info_ptr, &t_width, &t_height, &bit_depth,
        &color_type, NULL, NULL, NULL );

    png_read_update_info(png_ptr, info_ptr);
    row_bytes = png_get_rowbytes(png_ptr, info_ptr);
    png_byte* image_data = new png_byte[row_bytes * t_height];
    if (!image_data) {
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        return nullptr;
    }
    png_bytepp row_pointers = new png_bytep[t_height];
    if (!row_pointers) {
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        delete[] image_data;
        return nullptr;
    }
    for (unsigned int i = 0; i < t_height; ++i ) {
        row_pointers[t_height - 1 - i] = image_data + i * row_bytes;
    }
    png_read_image(png_ptr, row_pointers);
    raster_format format;
    switch (png_get_color_type(png_ptr, info_ptr )) {
        case PNG_COLOR_TYPE_RGBA:
        	format = RGBA;
            break;
        case PNG_COLOR_TYPE_RGB:
        	format = RGB;
            break;
        default:
            printf( "Color type %d not supported!\n",
                png_get_color_type( png_ptr, info_ptr ) );
            png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
            return 0;
    }


    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    delete[] row_pointers;
    return new RasterImage(format, {image_data}, t_width, t_height);
}
