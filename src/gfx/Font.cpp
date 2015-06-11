#include "gfx\Font.h"

#include <SDL.h>
#include <iostream>

TTFont::TTFont()
{

}

bool TTFont::setFont(SDL_Renderer* renderer, std::string font, int size)
{
	defaultsize_ = size;
	fontname = font;
	alignment_ = ALIGN_LEFT;
	fontsize_ = size;
	printf("LOADING FONT: res/font/%s\n", fontname.c_str());
	renderer_ = renderer;
	ttfont_ = TTF_OpenFont(("res/font/" + fontname).c_str(), fontsize_);
	surface_ = TTF_RenderText_Solid(ttfont_, "A", { 255, 128, 255, 255 });
	texture_ = SDL_CreateTextureFromSurface(renderer_, surface_);
	setColor({ 255, 255, 255, 255 });
	if (ttfont_ == NULL)
		printf("Error loading fonts: %s\n", TTF_GetError());
	return ((ttfont_ != NULL) && (renderer_ != NULL));
}

void TTFont::reset()
{
	setColor({ 255, 255, 255, 255 });
	alignment_ = ALIGN_LEFT;
	color_ = { 255, 255, 255, 255 };
	SDL_SetTextureBlendMode(texture_, SDL_BLENDMODE_NONE);
	setSize(defaultsize_);
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
		SDL_SetTextureBlendMode(texture_, SDL_BLENDMODE_NONE);
	else
		SDL_SetTextureBlendMode(texture_, SDL_BLENDMODE_BLEND);
	color_.a = a;
}

void TTFont::setSize(int size)
{
	fontsize_ = size;
	TTF_CloseFont(ttfont_);
	ttfont_ = TTF_OpenFont(("res/font/" + fontname).c_str(), fontsize_);
}

SDL_Rect TTFont::write(const char* message, int x, int y)
{
	if (alignment_ == ALIGN_CENTER || alignment_ == ALIGN_RIGHT)
	{
		int w, h;
		TTF_SizeText(ttfont_, message, &w, &h);
		if (alignment_ == ALIGN_CENTER)
			x -= w / 2;
		else if (alignment_ == ALIGN_RIGHT)
			x -= w;
	}
	SDL_DestroyTexture(texture_);
	surface_ = TTF_RenderText_Solid(ttfont_, message, color_);
	texture_ = SDL_CreateTextureFromSurface(renderer_, surface_);
	texturerect_ = { x, y };
	SDL_QueryTexture(texture_, NULL, NULL, &texturerect_.w, &texturerect_.h);
	render();
	SDL_FreeSurface(surface_);
	return texturerect_;
}

void TTFont::render()
{
	if (renderer_ != NULL && texture_ != NULL)
		SDL_RenderCopy(renderer_, texture_, NULL, &texturerect_);
}

TTFont::~TTFont()
{
	SDL_DestroyTexture(texture_);
	renderer_ = nullptr;
	surface_ = nullptr;
	texture_ = nullptr;
}







/*
#include "gfx\Font.h"

#include <SDL.h>

TTFont::TTFont()
{

}

bool TTFont::setFont(SDL_Renderer* renderer, std::string fontname, int size)
{
	fontsize_ = size;
	printf("LOADING FONT: res/font/%s\n", fontname.c_str());
	renderer_ = renderer;
	SDL_SetRenderDrawColor(renderer_, 255, 0, 255, 255);
	ttfont_ = TTF_OpenFont(("res/font/" + fontname).c_str(), fontsize_);
	if (ttfont_ == NULL)
		printf("Error loading fonts: %s\n", TTF_GetError());
	return ((ttfont_ != NULL) && (renderer_ != NULL));
}

void TTFont::reset()
{

}

int TTFont::write(std::string msg, int x, int y, TTFontAlignment alignment)
{
	message.push_back(new Message());
	message[message.size() - 1]->message = msg;
	message[message.size() - 1]->surface = TTF_RenderText_Solid(ttfont_, msg.c_str(), color_);
	message[message.size() - 1]->texture = SDL_CreateTextureFromSurface(renderer_, message[message.size() - 1]->surface);
	if (alignment == ALIGN_CENTER || alignment == ALIGN_RIGHT)
	{
		int w, h;
		TTF_SizeText(ttfont_, msg.c_str(), &w, &h);
		if (alignment == ALIGN_CENTER)
			x -= w / 2;
		else if (alignment == ALIGN_RIGHT)
			x -= w;
	}
	message[message.size() - 1]->textrect = { x, y, 0, 0 };
	SDL_QueryTexture(message[message.size() - 1]->texture, nullptr, nullptr, &message[message.size() - 1]->textrect.w, &message[message.size() - 1]->textrect.h);
	return message.size();
}

int TTFont::writeFast(std::string, int x, int y, TTFontAlignment alignment)
{

	return 1;
}

void TTFont::render()
{
	for (int i = 0; i < message.size(); i++)
	{
		if (renderer_ != nullptr && message[i]->texture != nullptr)
		{
			SDL_SetRenderDrawColor(renderer_, 255, 0, 255, 255);
			SDL_RenderCopy(renderer_, message[i]->texture, nullptr, &message[i]->textrect);
		}
	}
}

TTFont::~TTFont()
{
	for (int i = 0; i < message.size(); i++)
	{
		SDL_DestroyTexture(message[i]->texture);
		message[i]->texture = nullptr;
		message[i]->surface = nullptr;
	}
	renderer_ = nullptr;
}
*/