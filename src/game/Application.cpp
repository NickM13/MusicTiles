#include "game\Application.h"
#include "utils\Math.h"
#include <stdio.h>
#include <iostream>
#include <math.h>

void Application::init()
{
	window = nullptr;
	surface = nullptr;

	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow("Rhythm Game Indev v0.0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	TTF_Init();

	surface = SDL_GetWindowSurface(window);
	renderer = SDL_CreateRenderer(window, 0, 0);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	SideMenu::getInstance().init(renderer, punchsize*11+11, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	font.setFont(renderer, "new_courier/cour.ttf", 32);

	for (int i = 0; i < 256; i++)
	{
		keystates[i] = false;
		keytaps[i] = false;
	}
	for (int i = 0; i < 32; i++)
	{
		mousestates[i] = false;
	}
	for (int i = 0; i < 5; i++)
	{
		puncher[i].x = i * (punchsize + 1);
	}
	for (int i = 5; i < 10; i++)
	{
		puncher[i].x = i * (punchsize + 1) + punchsize;
	}

	mainLoop();
}

void Application::input()
{
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			gamestate = STATE_EXITTING;
		}
		else if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym < 256)
			{
				keystates[e.key.keysym.sym] = true;
				keytaps[e.key.keysym.sym] = true;
				keystapped.push_back(e.key.keysym.sym);
			}
		}
		else if (e.type == SDL_KEYUP)
		{
			if (e.key.keysym.sym < 256)
				keystates[e.key.keysym.sym] = false;
		}
		else if (e.type == SDL_MOUSEMOTION)
		{
			mouse.x = e.button.x;
			mouse.y = e.button.y;
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			mousestates[e.button.button] = true;
		}
		else if (e.type == SDL_MOUSEBUTTONUP)
		{
			mousestates[e.button.button] = false;
		}
	}
}

bool levelLoaded = false;

void Application::update()
{
	if (developer && keystates['q'])
		gamestate = STATE_EXITTING;
	if (keytaps[27])
	{
		if (gamestate == STATE_INGAME)
			gamestate = STATE_PAUSED;
		else if (STATE_PAUSED)
			gamestate = STATE_INGAME;
	}
	if (gamestate == STATE_INGAME) {
		if (!inlevel || developer && (keytaps['r'])) {
			if ((developer && keytaps['r'])) {
				musictiles.clear();
				tilesremaining = 0;
			}
			levelLoaded = false;
			stage++;
			level.generateRandom((int)levellength);
			inlevel = true;
			levellength += 3.5f;
		}
		if (!levelLoaded)
		{
			int spacing = 0;
			while (level.getByte() < level.getSize())
			{
				int currLength = level.readByte();
				for (int i = 0; i < currLength; i++) {
					musictiles.push_back(MusicTile(level.readByte(), spacing));
					tilesremaining++;
				}
				spacing += (int)((punchsize * (8.f / stage)) + punchsize / 1.9f);
			}
			levelLoaded = true;
			std::cout << "Level loaded" << std::endl;
			std::cout << "Awaiting tile destruction..." << std::endl;
		}
		if (tilesremaining <= 0)
		{
			inlevel = false;
		}

		if (keystapped.size() > 0)
		{
			for (unsigned int i = 0; i < keystapped.size(); i++)
			{
				switch (keystapped[i])
				{
				case 'a':
					puncher[0].pressed(ANIM_MISS);
					score -= 25;
					tilesmissed++;
					break;
				case 's':
					puncher[1].pressed(ANIM_MISS);
					score -= 25;
					tilesmissed++;
					break;
				case 'd':
					puncher[2].pressed(ANIM_MISS);
					score -= 25;
					tilesmissed++;
					break;
				case 'f':
					puncher[3].pressed(ANIM_MISS);
					score -= 25;
					tilesmissed++;
					break;
				case 'g':
					puncher[4].pressed(ANIM_MISS);
					score -= 25;
					tilesmissed++;
					break;
				case 'h':
					puncher[5].pressed(ANIM_MISS);
					score -= 25;
					tilesmissed++;
					break;
				case 'j':
					puncher[6].pressed(ANIM_MISS);
					score -= 25;
					tilesmissed++;
					break;
				case 'k':
					puncher[7].pressed(ANIM_MISS);
					score -= 25;
					tilesmissed++;
					break;
				case 'l':
					puncher[8].pressed(ANIM_MISS);
					score -= 25;
					tilesmissed++;
					break;
				case ';':
					puncher[9].pressed(ANIM_MISS);
					score -= 25;
					tilesmissed++;
					break;
				}
			}
		}

		for (int i = musictiles.size() - 1; i >= 0; i--)
		{
			if (keystates['z'])
				musictiles[i].update((speed + (stage / 4.f)) * 8);
			else
				musictiles[i].update(speed + (stage / 4.f));

			if (musictiles[i].isTapped())
			{
				if (musictiles[i].getExplode() >= 8)
					musictiles.erase(musictiles.begin() + i);
			}
			else
			{
				if (keystapped.size() > 0)
				if (musictiles[i].getHeight() >= SCREEN_HEIGHT - punchsize / 2 - offsetY && musictiles[i].getHeight() <= SCREEN_HEIGHT + punchsize - offsetY) {
					int p = musictiles[i].checkCollision(keytaps);
					if (p != NULL)	{
						if (musictiles[i].getHeight() >= SCREEN_HEIGHT - offsetY && musictiles[i].getHeight() <= SCREEN_HEIGHT - offsetY + punchsize / 2)
						{
							puncher[p - 1].pressed(ANIM_PERFECT);
							score += 125;
							tilesperfect++;
						}
						else
						{
							puncher[p - 1].pressed(ANIM_HIT);
							score += 75;
						}
						tilesremaining--;
						tilesmissed--;
						tilespunched++;
					}
				}
				else
				{
					int p = musictiles[i].checkCollision(keytaps);
					if (p != NULL)	{
						if (musictiles[i].getHeight() >= SCREEN_HEIGHT - offsetY && musictiles[i].getHeight() <= SCREEN_HEIGHT - offsetY + punchsize / 2)
						{
							puncher[p - 1].pressed(ANIM_PERFECT);
							score += 125;
							tilesperfect++;
						}
						else
						{
							puncher[p - 1].pressed(ANIM_HIT);
							score += 75;
						}
						tilesremaining--;
						tilesmissed--;
						tilespunched++;
					}
				}

				if (musictiles[i].getHeight() > SCREEN_HEIGHT)
				{
					puncher[musictiles[i].getRow()].pressed(ANIM_MISS);
					musictiles.erase(musictiles.begin() + i);
					score -= 50;
					tilesremaining--;
				}
			}
		}
		for (int i = 0; i < 10; i++)
		{
			puncher[i].update();
		}
	}

	if (keystapped.size() > 0)
	{
		for (unsigned int i = 0; i < keystapped.size(); i++)
		{
			keytaps[keystapped[i]] = false;
		}
		keystapped.clear();
	}
}

int fps;

void Application::render()
{
	SDL_SetRenderDrawColor(renderer, 0x1F, 0x1F, 0x1F, 0xFF);
	SDL_RenderClear(renderer);

	if (STATE_INGAME) {
		SDL_SetRenderDrawColor(renderer, 0xBB, 0xBB, 0xBB, 0xFF);
		for (int i = 0; i < 10; i++)
		{
			puncher[i].render(renderer, punchsize, SCREEN_HEIGHT - offsetY, MusicTile::getColor(i));
		}

		for (unsigned int i = 0; i < musictiles.size(); i++)
		{
			musictiles[i].render(renderer, punchsize);
		}
	}

	SideMenu::getInstance().render();

	font.setAlignment(ALIGN_RIGHT);
	font.write(std::string("Score: " + Math::numToString(score)), SCREEN_WIDTH - 16, 10);
	font.write(std::string("Stage: " + Math::numToString(stage)), SCREEN_WIDTH - 16, 48);
	font.write(std::string("Hit: " + Math::numToString(tilespunched)), SCREEN_WIDTH - 16, 86);
	font.write(std::string("Missed: " + Math::numToString(tilesmissed)), SCREEN_WIDTH - 16, 124);
	font.write(std::string("Remaining: " + Math::numToString(tilesremaining)), SCREEN_WIDTH - 16, 162);
	font.write(std::string("Perfect: " + Math::numToString(tilesperfect)), SCREEN_WIDTH - 16, 200);
	font.write(std::string("FPS: " + Math::numToString(fps)), SCREEN_WIDTH - 16, 238);

	font.setAlignment(ALIGN_CENTER);

	font.write(std::string("A"), (punchsize + 1) * 1 - punchsize / 2, SCREEN_HEIGHT - offsetY + punchsize / 4);
	font.write(std::string("S"), (punchsize + 1) * 2 - punchsize / 2, SCREEN_HEIGHT - offsetY + punchsize / 4);
	font.write(std::string("D"), (punchsize + 1) * 3 - punchsize / 2, SCREEN_HEIGHT - offsetY + punchsize / 4);
	font.write(std::string("F"), (punchsize + 1) * 4 - punchsize / 2, SCREEN_HEIGHT - offsetY + punchsize / 4);
	font.write(std::string("G"), (punchsize + 1) * 5 - punchsize / 2, SCREEN_HEIGHT - offsetY + punchsize / 4);
	font.write(std::string("H"), (punchsize + 1) * 7 - punchsize / 2, SCREEN_HEIGHT - offsetY + punchsize / 4);
	font.write(std::string("J"), (punchsize + 1) * 8 - punchsize / 2, SCREEN_HEIGHT - offsetY + punchsize / 4);
	font.write(std::string("K"), (punchsize + 1) * 9 - punchsize / 2, SCREEN_HEIGHT - offsetY + punchsize / 4);
	font.write(std::string("L"), (punchsize + 1) * 10 - punchsize / 2, SCREEN_HEIGHT - offsetY + punchsize / 4);
	font.write(std::string(";"), (punchsize + 1) * 11 - punchsize / 2, SCREEN_HEIGHT - offsetY + punchsize / 4);

	font.setAlignment(ALIGN_LEFT);

	SDL_RenderPresent(renderer);
}

int fpsdelay = 0;

void Application::mainLoop()
{
	while (gamestate != STATE_EXITTING)
	{
		float start = SDL_GetTicks();
		input();
		update();
		render();
		SDL_Delay(  (Uint32) (std::fmaxf(0, (1000.f / SCREEN_FPS)  -  (SDL_GetTicks() - start)))  );
		if (fpsdelay == 0)
		{
			fps = 1000.f / (SDL_GetTicks() - start);
			fpsdelay = 20;
		}
		else
			fpsdelay--;
	}
}

void Application::destroy()
{
	printf("Deconstructing Application Window...");
	font.~TTFont();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = nullptr;
	renderer = nullptr;
	surface = nullptr;
	texture = nullptr;
	TTF_Quit();
	SDL_Quit();
}
