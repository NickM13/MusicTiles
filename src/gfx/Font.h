#pragma once
#include <SDL_ttf.h>
#include <string>

enum TTFontAlignment
{
	ALIGN_LEFT,
	ALIGN_CENTER,
	ALIGN_RIGHT
};

class TTFont
{
	public:
		TTFont();
		bool setFont(SDL_Renderer*, std::string, int);
		void reset();
		void setAlignment(TTFontAlignment);
		void setColor(SDL_Color);
		void setAlpha(Uint8);
		void write(std::string, int, int);
		void render();
		~TTFont();
	private:
		TTF_Font* ttfont_ = NULL;
		SDL_Surface* surface_ = NULL;
		SDL_Texture* texture_ = NULL;
		SDL_Renderer* renderer_ = NULL;
		SDL_Rect texturerect_;
		SDL_Color color_;

		TTFontAlignment alignment_;
		int fontsize_;
};
