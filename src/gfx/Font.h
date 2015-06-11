#pragma once
#include <SDL_ttf.h>
#include <string>

#include "utils\general\Singleton.h"

enum TTFontAlignment
{
	ALIGN_LEFT,
	ALIGN_CENTER,
	ALIGN_RIGHT
};

class TTFont : public Singleton<TTFont>
{
public:
	TTFont();
	bool setFont(SDL_Renderer*, std::string, int);
	void reset();
	void setAlignment(TTFontAlignment);
	void setColor(SDL_Color);
	void setAlpha(Uint8);
	void setSize(int);
	SDL_Rect write(const char*, int, int);
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
	int defaultsize_ = 32;
	std::string fontname = "";
};










/*
#pragma once
#include <SDL_ttf.h>
#include <string>
#include <vector>

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
	int write(std::string, int, int, TTFontAlignment);
	int writeFast(std::string, int, int, TTFontAlignment);
	void render();
	~TTFont();
private:

	struct Message
	{
		std::string message;
		SDL_Surface* surface = nullptr;
		SDL_Texture* texture = nullptr;
		SDL_Rect textrect;
		Message(){};
	};

	std::vector<Message*> message;

	TTF_Font* ttfont_ = nullptr;
	SDL_Renderer* renderer_ = nullptr;
	SDL_Color color_;

	int fontsize_;
};
*/