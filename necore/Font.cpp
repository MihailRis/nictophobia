#include "Font.h"

bool Font::isPrintable(wchar_t character) {
	switch (character) {
	case '\0':
	case ' ':
	case '\b':
	case '\r':
	case '\n':
	case '\t':
	case '\f':
		return false;
	default:
		return true;
	}
}

BitmapFont::BitmapFont(int size, std::vector<Texture*> pages, std::unordered_map<wchar_t, int> advances) : Font(size), pages(pages), advances(advances){
}

#define FONT_GLYPH_MUL (1.0f/16.0f)

glyph* BitmapFont::getGlyph(wchar_t character) {
	auto found = glyphs.find(character);
	if (found == glyphs.end()) {
		int pageid = character >> 8;
		if (pageid > pages.size()){
			return nullptr;
		}
		int index = character & 0xFF;
		uvregion region = {
			(index % 16) * FONT_GLYPH_MUL, 1.0f - (index / 16 + 1) * FONT_GLYPH_MUL,
			(index % 16 + 1) * FONT_GLYPH_MUL, 1.0f - (index / 16 + 0) * FONT_GLYPH_MUL

		};
		auto advance = advances.find(character);
		int advancePercent = 80;
		if (advance != advances.end()) {
			advancePercent = advance->second;
		}
		glyph g {
			pages[pageid],
			region,
			character,
			(int)((advancePercent / 100.0f) * size),
					0};
		glyphs[character] = g;
		return &glyphs[character];
	}
	return &found->second;
}
