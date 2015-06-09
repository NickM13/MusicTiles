#pragma once

#include "utils\Singleton.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "utils\Vector2i.h"
#include "game\Level.h"
#include "game\MusicTile.h"
#include <vector>
#include <iostream>

class Application : public Singleton<Application>
{
	public:
		void init();
		void mainLoop();

		void input();
		void update();
		void render();
	private:

		bool developer = true; 

		SDL_Window* window;
		SDL_Surface* surface;
		SDL_Renderer* renderer;
		SDL_Texture* texture;
		TTF_Font* font;
		SDL_Event e;

		bool exitting = false;
		bool paused = false;
		bool ingame = true;

		const int SCREEN_WIDTH = 1280;
		const int SCREEN_HEIGHT = 960;

		bool mousestates[32];
		bool keystates[256];
		bool keytaps[256];
		std::vector<Uint8> keystapped;
		bool keydown = false;

		std::vector<MusicTile> musictiles;

		struct Puncher
		{
			int x = 0;
			bool hit = false;
			int animcounter = 0;

			void update()
			{
				if (animcounter > 0) animcounter--;
			}

			void render(SDL_Renderer* renderer_, int size, int y)
			{
				SDL_Rect rect = { x * (size + 1), y, size, size };

				SDL_SetRenderDrawColor(renderer_, 127 + (animcounter * !hit), 127 + (animcounter * hit), 127, 255);
				SDL_RenderFillRect(renderer_, &rect);
			}

			void pressed(bool hitsomething)
			{
				animcounter = 64;
				hit = hitsomething;
			}
		};

		int punchsize = 32;

		int offsetY = 128;

		Puncher puncher[8];

		int tilesmissed = 0;
		int tilespunched = 0;

		float speed = 2;


		Level level;

		bool inlevel = false;
		bool levelstage = 0;
		int tilesremaining = 0;
		int levellength = 10;

		int score = 0;


		Vector2i mouse;
};