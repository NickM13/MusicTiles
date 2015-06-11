#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "utils\general\Singleton.h"

#include <string>

class LTexture
{
	public:

		~LTexture()
		{
			SDL_DestroyTexture(image_);
			renderer_ = nullptr;
			image_ = nullptr;
		}

		void init(SDL_Renderer* renderer)
		{
			printf("init texture\n");
			renderer_ = renderer;
		}

		void loadIMG(std::string filename)
		{
			printf("load texture\n");
			SDL_Surface* surface_ = SDL_LoadBMP(filename.c_str());
			image_ = IMG_LoadTexture(renderer_, (filename).c_str());
			image_ = SDL_CreateTextureFromSurface(renderer_, surface_);
			SDL_QueryTexture(image_, NULL, NULL, &imgrect.w, &imgrect.h);
			SDL_SetTextureColorMod(image_, 255, 255, 255);
		}

		void render(int x, int y)
		{
			imgrect.x = x;
			imgrect.y = y;
			if (image_ != nullptr && renderer_ != nullptr)
			{
				SDL_RenderCopy(renderer_, image_, nullptr, &imgrect);
			}
		}

		bool isLoaded()
		{
			return image_ != nullptr;
		}

	private:
		SDL_Surface* surface_ = nullptr;
		SDL_Renderer* renderer_ = nullptr;
		SDL_Texture* image_ = nullptr;
		SDL_Rect imgrect;

};
