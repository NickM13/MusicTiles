#pragma once
#include <SDL_ttf.h>
#include <string>

class TTFont
{
	TTFont();
	void write(std::string);
	bool setFont();
	~TTFont();
};
