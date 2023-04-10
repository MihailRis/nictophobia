#ifndef FREETYPEFONT_H_
#define FREETYPEFONT_H_

#include "../miocpp/iopath.h"
#include "Font.h"

class FreeTypeFont;

class FreeTypeFontLoader {
	void* lib = nullptr;
public:
	FreeTypeFontLoader();
	~FreeTypeFontLoader();
	FreeTypeFont* create(iopath path, int size);
};

class FreeTypeFont : Font {
	void* face;
public:
	FreeTypeFont(void* face, int size, int height);
	virtual ~FreeTypeFont();

	virtual glyph* getGlyph(wchar_t character);
	virtual int getKerning(wchar_t left, wchar_t right);
};

#endif /* FREETYPEFONT_H_ */
