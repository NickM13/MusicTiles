#include "gfx\Font.h"

#include <SDL.h>

TTFont::TTFont()
{
	
}

bool TTFont::setFont(SDL_Renderer* renderer, std::string fontname, int size)
{
	alignment_ = ALIGN_LEFT;
	fontsize_ = size;
	printf("LOADING FONT: res/font/%s\n", fontname.c_str());
	renderer_ = renderer;
	ttfont_ = TTF_OpenFont(("res/font/" + fontname).c_str(), fontsize_);
	surface_ = TTF_RenderText_Solid(ttfont_, "", {255, 128, 255, 255});
	texture_ = SDL_CreateTextureFromSurface(renderer_, surface_);
	setColor({ 255, 255, 255, 255 });
	if (ttfont_ == NULL)
		printf("Error loading fonts: %s\n", TTF_GetError());
	return ((ttfont_ != NULL) && (renderer_ != NULL));
}

void TTFont::reset()
{
	alignment_ = ALIGN_LEFT;
	color_ = { 255, 255, 255, 255 };
	SDL_SetTextureBlendMode(texture_, SDL_BLENDMODE_NONE);
}

void TTFont::setAlignment(TTFontAlignment alignment)
{
	alignment_ = alignment;
}

void TTFont::setColor(SDL_Color color)
{
	color_ = color;
}

void TTFont::setAlpha(Uint8 a)
{
	if (a == 255)
		SDL_SetTextureBlendMode(texture_, SDL_BLENDMODE_BLEND);
	else
		SDL_SetTextureBlendMode(texture_, SDL_BLENDMODE_NONE);
	color_.a = a;
}

void TTFont::write(std::string message, int x, int y)
{
	if (alignment_ == ALIGN_CENTER || alignment_ == ALIGN_RIGHT)
	{
		int w, h;
		TTF_SizeText(ttfont_, message.c_str(), &w, &h);
		if (alignment_ == ALIGN_CENTER)
			x -= w / 2;
		else if (alignment_ == ALIGN_RIGHT)
			x -= w;
	}
	surface_ = TTF_RenderText_Solid(ttfont_, message.c_str(), color_);
	texture_ = SDL_CreateTextureFromSurface(renderer_, surface_);
	texturerect_ = { x, y };
	SDL_QueryTexture(texture_, NULL, NULL, &texturerect_.w, &texturerect_.h);
	if (renderer_ != NULL && texture_ != NULL);
		SDL_RenderCopy(renderer_, texture_, NULL, &texturerect_);
}

void TTFont::render()
{
	if (renderer_ != NULL && texture_ != NULL);
		SDL_RenderCopy(renderer_, texture_, NULL, &texturerect_);
}

TTFont::~TTFont()
{
	SDL_DestroyTexture(texture_);
	renderer_ = nullptr;
	surface_ = nullptr;
	texture_ = nullptr;
}
