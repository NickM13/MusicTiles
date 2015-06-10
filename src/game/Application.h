#pragma once

#include "utils\Singleton.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "utils\Vector2i.h"
#include "game\Level.h"
#include "game\MusicTile.h"
#include "gfx\Font.h"
#include <vector>
#include <iostream>
#include "menu\SideMenu.h"

class Application : public Singleton<Application>
{
	public:
		void init();
		void mainLoop();

		void input();
		void update();
		void render();

		void destroy();
	private:

		bool developer = true; 

		SDL_Window* window;
		SDL_Surface* surface;
		SDL_Renderer* renderer;
		SDL_Texture* texture;

		TTFont font;

		enum GAME_STATE
		{
			STATE_INMENU,
			STATE_INGAME,
			STATE_PAUSED,
			STATE_EXITTING
		};

		GAME_STATE gamestate = STATE_INGAME;

		const int SCREEN_FPS = 60;
		const int SCREEN_WIDTH = 1280;
		const int SCREEN_HEIGHT = 960;

		SDL_Event e;
		bool mousestates[32];
		bool keystates[256];
		bool keytaps[256];
		std::vector<Uint8> keystapped;
		bool keydown = false;

		int offsetY = 128;

		std::vector<MusicTile> musictiles;

		enum PAnimation
		{
			ANIM_HIT,
			ANIM_MISS,
			ANIM_PERFECT
		};

		struct Puncher
		{
			int x = 0;
			PAnimation animation_ = ANIM_HIT;
			int ac_ = 0;

			void update()
			{
				if (ac_ > 0) ac_ -= 4;
			}

			void render(SDL_Renderer* renderer_, int size, int y, SDL_Color color_)
			{
				SDL_Rect rect = { x, y, size, size };
				SDL_Rect back = { x, 0, size, y };

				if (animation_ == ANIM_PERFECT)
				{
					SDL_SetRenderDrawColor(renderer_, color_.r - (ac_ / 128.f) * (color_.r),
						color_.g - (ac_ / 128.f) * (color_.g),
						color_.b + (ac_ / 128.f) * (255 - color_.b),
						127 + ac_);
				}
				else if (animation_ == ANIM_HIT)
				{
					SDL_SetRenderDrawColor(renderer_, color_.r - (ac_ / 128.f) * (color_.r),
						color_.g + (ac_ / 128.f) * (255 - color_.g),
						color_.b - (ac_ / 128.f) * (color_.b),
						127 + ac_);
				}
				else if (animation_ == ANIM_MISS)
				{
					SDL_SetRenderDrawColor(renderer_,
						color_.r + (ac_ / 128.f) * (255 - color_.r),
						color_.g - (ac_ / 128.f) * (color_.g),
						color_.b - (ac_ / 128.f) * (color_.b),
						127 + ac_);
				}
				SDL_RenderFillRect(renderer_, &back);

				SDL_SetRenderDrawColor(renderer_, 127 + (ac_ * (int)(animation_ == ANIM_MISS)), 127 + (ac_ * (int)(animation_ == ANIM_HIT)), 127, 255);
				SDL_RenderFillRect(renderer_, &rect);
			}

			void pressed(PAnimation animation)
			{
				ac_ = 128;
				animation_ = animation;
			}
		};

		int punchsize = 64;
		Puncher puncher[10];

		int tilesmissed = 0;
		int tilespunched = 0;
		int tilesperfect = 0;

		float speed = 2;


		Level level;

		bool inlevel = false;
		int stage = 0;
		int tilesremaining = 0;
		float levellength = 5;

		int score = 0;


		Vector2i mouse;

		SideMenu sidemenu;
};