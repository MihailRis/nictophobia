#include "FreeTypeFont.h"
#include <iostream>

#include "Font.h"
#include "Texture.h"
#include "gl/GLTexture.h"
#include "RasterImage.h"

#include <ft2build.h>
#include FT_FREETYPE_H

FreeTypeFontLoader::FreeTypeFontLoader() {
	FT_Library library;
	int error = FT_Init_FreeType(&library);
	if (error) {
		std::cerr << "FT_Init_FreeType: an error ocurred (code: " << error << ")" << std::endl;
		return;
	}
	lib = library;
}

FreeTypeFontLoader::~FreeTypeFontLoader() {
	FT_Done_FreeType((FT_Library)lib);
}

FreeTypeFont* FreeTypeFontLoader::create(iopath path, int font_size) {
	FT_Library library = (FT_Library)lib;
	FT_Face face;
	unsigned char* bytes;
	{
		size_t size;
		bytes = path.readBytes(&size);
		int error = FT_New_Memory_Face(library, bytes, size, 0, &face);
		if (error == FT_Err_Unknown_File_Format){
		  std::cerr << "font " << path.toStr() << " loading error: FT_Err_Unknown_File_Format" << std::endl;
		  delete[] bytes;
		  return nullptr;
		} else if (error) {
		  std::cerr << "font " << path.toStr() << " loading error (code: " << error << ")" << std::endl;
		  delete[] bytes;
		  return nullptr;
		}
		// bytes are used until FT_Done_Face call
	}

	int error = FT_Set_Char_Size( face, font_size * 64, 0,
	                            64, 0 );
	if (error) {
		std::cerr << "font loading error (FT_Set_Pixel_Sizes) (code: " << error << ")" << std::endl;
		return nullptr;
	}
	return new FreeTypeFont((void*)face, font_size, face->height/64, bytes);
}

FreeTypeFont::FreeTypeFont(void* face, int font_size, int height, unsigned char* data) :
		Font(font_size, height), face(face), data(data) {
}

FreeTypeFont::~FreeTypeFont() {
	FT_Done_Face((FT_Face)face);
	for (auto const& [key, val] : glyphs) {
		delete val.texture;
	}
	delete[] data;
}

int FreeTypeFont::getKerning(wchar_t left, wchar_t right) {
	FT_Face face = (FT_Face)this->face;
	if(FT_HAS_KERNING(face)){
	    FT_Vector delta;
	    FT_UInt glyph_index = FT_Get_Char_Index(face, left);
	    FT_UInt prev_index = FT_Get_Char_Index(face, right);
	    FT_Get_Kerning(face, prev_index, glyph_index,
	                        FT_KERNING_DEFAULT, &delta);
	    return delta.x >> 6;
	}
	return 0;

}

glyph* FreeTypeFont::getGlyph(wchar_t character) {
	if (!isPrintable(character))
		return nullptr;
	auto found = glyphs.find(character);
	if (found == glyphs.end()) {
		FT_Face face = (FT_Face)this->face;
		int error = FT_Load_Char(face, character, FT_LOAD_RENDER);
		if (error) {
			return nullptr;
		}
		FT_GlyphSlot slot = face->glyph;
	    int advance = slot->advance.x / 64;

	    int width = slot->bitmap.width;
	    int height = slot->bitmap.rows;

	    int res = size;
	    raster_u raster = {new unsigned char[4 * res * res]};
	    for (int i = 0; i < res*res*4; i++) {
	    	raster.ubyte[i] = 0;
	    }

	    int bbox_ymax = face->bbox.yMax / 64;
	    int y_off = bbox_ymax - face->glyph->metrics.horiBearingY / 64;
		int bearing = y_off;

	    for (int y = 0; y < height; y++) {
	    	for (int x = 0; x < width; x++) {
	    		int pixel = (((res-y-1)) * res) + x;
	    		raster.ubyte[pixel * 4] = 255;
	    		raster.ubyte[pixel * 4 + 1] = 255;
	    		raster.ubyte[pixel * 4 + 2] = 255;

	    		raster.ubyte[pixel * 4 + 3] = slot->bitmap.buffer[y * width + x];
	    	}
	    }
	    RasterImage image(RGBA, raster, res, res);
	    Texture* texture = GLTexture::fromImage(&image);
	    glyph g{texture, {}, character, advance, -bearing};
	    glyphs[character] = g;
	    return &glyphs[character];
	}
	else {
		return &found->second;
	}
}
