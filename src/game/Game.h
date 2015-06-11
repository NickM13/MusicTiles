#pragma once

#include <vector>
#include <iostream>

#include "gfx\Font.h"
#include "gfx\particle\Particle.h"

#include "game\Level.h"
#include "game\entity\MusicTile.h"
#include "game\entity\Puncher.h"

#include "utils\general\Math.h"
#include "utils\general\Singleton.h"
#include "utils\struct\Vector2i.h"

#include "menu\SideMenu.h"

class Game : public Singleton<Game>
{
	public:

		void init(SDL_Renderer*, const int*, const int*, int*);

		void input();
		void update();
		void render();

	private:
		bool developer = true;

		const int* SCREEN_WIDTH;
		const int* SCREEN_HEIGHT;
		int* fps;

		SDL_Renderer* renderer;

		bool punchkeys[10];
		bool extrakeys[10];

		int offsetY = 64;

		std::vector<MusicTile> musictiles;

		LTexture* tiletex;

		int punchsize = 64;
		Puncher puncher[10];

		int tilesmissed = 0;
		int tilespunched = 0;
		int tilesperfect = 0;

		int streak = 0;
		int highstreak = 0;

		int doubles = 0;

		float speed = 2;


		Level level;

		bool inlevel = false;
		int stage = 0;
		int tilesremaining = 0;
		float levellength = 5;

		int score = 0;
};