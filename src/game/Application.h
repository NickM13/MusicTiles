#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <vector>
#include <iostream>

#include "game\Game.h"

#include "gfx\Font.h"

#include "menu\SideMenu.h"

#include "utils\struct\Vector2i.h"
#include "utils\general\Singleton.h"
#include "utils\system\Event.h"


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

		static Event e;

		bool developer = true;

		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_Texture* texture;

		enum GAME_STATE
		{
			STATE_STARTING,
			STATE_INMENU,
			STATE_INGAME,
			STATE_PAUSED,
			STATE_EXITTING
		};

		GAME_STATE gamestate = STATE_STARTING;
		//int statetime = 0;

		const int SCREEN_FPS = 60;
		const int SCREEN_WIDTH = 1280;
		const int SCREEN_HEIGHT = 960;

		int fps = 0;

		SideMenu sidemenu;
};