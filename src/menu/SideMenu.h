#pragma once
#include "utils\Singleton.h"
#include <SDL.h>

class SideMenu : public Singleton<SideMenu>
{
	public:
		void init(SDL_Renderer*, int, int, int, int);
		void render();

	private:
		SDL_Renderer* renderer_;
		SDL_Rect background_;


};