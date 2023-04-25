#ifndef NECORE_FONT_H_
#define NECORE_FONT_H_

#include "uvregion.h"

#include <vector>
#include <unordered_map>

class Texture;

struct glyph {
	Texture* texture;
	uvregion region;
	wchar_t character;
	int advance;
	int bearingY;
};

class Font {
protected:
	std::unordered_map<wchar_t, glyph> glyphs;
	int size;
	int advanceY;
public:
	Font(int size) : size(size), advanceY(size*1.5) {
	}

	Font(int size, int advanceY) : size(size), advanceY(advanceY) {
	}

	virtual ~Font(){}

	virtual int getSize() const {
		return size;
	}

	virtual int getAdvanceY() const {
		return advanceY;
	}
	virtual glyph* getGlyph(wchar_t character) = 0;
	virtual int getKerning(wchar_t left, wchar_t right);
	virtual bool isPrintable(wchar_t character);
};

class BitmapFont : public Font {
	std::vector<Texture*> pages;
	std::unordered_map<wchar_t, int> advances;
	int basicAdvancePercent;
public:
	BitmapFont(int size, std::vector<Texture*> pages, std::unordered_map<wchar_t, int> advances, int basicAdvancePercent);
	virtual ~BitmapFont();

	virtual glyph* getGlyph(wchar_t character);
};


#endif /* NECORE_FONT_H_ */
