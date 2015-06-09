#include "game\Application.h"
#include <stdio.h>
#include <iostream>

void Application::init()
{
	window = NULL;
	surface = NULL;
font = NULL;

SDL_Init(SDL_INIT_VIDEO);

window = SDL_CreateWindow("Rhythm Game Indev v0.0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

TTF_Init();

font = TTF_OpenFont("res\\font\\new_courier\\cour.ttf", 28);

surface = SDL_GetWindowSurface(window);
renderer = SDL_CreateRenderer(window, 0, 0);

for (int i = 0; i < 256; i++)
{
	keystates[i] = false;
	keytaps[i] = false;
}
for (int i = 0; i < 32; i++)
{
	mousestates[i] = false;
}
for (int i = 0; i < 8; i++)
{
	puncher[i].x = i;
}

mainLoop();

SDL_DestroyWindow(window);
TTF_Quit();
SDL_Quit();
}

void Application::input()
{
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			exitting = true;
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

int tiledelay = 0;

void Application::update()
{
	if (keystates[27])
		exitting = true;
	if (developer)
		if (keytaps[32])
			paused = !paused;
	if (!paused && ingame) {
		if (!inlevel || keytaps['g']) {
			level.generateRandom(levellength);
			inlevel = true;
		}
		if (inlevel && tiledelay == 0)
		{
			int currLength = level.readByte();
			for (int i = 0; i < currLength; i++) {
				musictiles.push_back(MusicTile(level.readByte()));
			}
			tiledelay = 32.f / speed;
			if (level.getByte() > level.getSize())
			{
				inlevel = false;
				std::cout << "Level finished" << std::endl;
			}
		}
		if (tiledelay > 0) tiledelay--;

		if (keystapped.size() > 0)
		{
			for (int i = 0; i < keystapped.size(); i++)
			{
				switch (keystapped[i])
				{
				case 'q':
					puncher[0].pressed(false);
					score -= 25;
					break;
				case 'w':
					puncher[1].pressed(false);
					score -= 25;
					break;
				case 'e':
					puncher[2].pressed(false);
					score -= 25;
					break;
				case 'r':
					puncher[3].pressed(false);
					score -= 25;
					break;
				case 'a':
					puncher[4].pressed(false);
					score -= 25;
					break;
				case 's':
					puncher[5].pressed(false);
					score -= 25;
					break;
				case 'd':
					puncher[6].pressed(false);
					score -= 25;
					break;
				case 'f':
					puncher[7].pressed(false);
					score -= 25;
					break;
				}
			}
		}

		for (int i = musictiles.size() - 1; i >= 0; i--)
		{
			musictiles[i].update(speed);

			if (musictiles[i].isTapped())
			{
				if (musictiles[i].getExplode() >= 8)
					musictiles.erase(musictiles.begin() + i);
			}
			else
			{
				if (keystapped.size() > 0)
				if (musictiles[i].getHeight() >= SCREEN_HEIGHT - punchsize/2 - offsetY && musictiles[i].getHeight() <= SCREEN_HEIGHT + punchsize - offsetY) {
					int p = musictiles[i].checkCollision(keytaps);
					if (p != NULL)	{
						puncher[p-1].pressed(true);
						score+= 125;
					}
				}

				if (musictiles[i].getHeight() > SCREEN_HEIGHT)
				{
					musictiles.erase(musictiles.begin() + i);
					score -= 50;
				}
			}
		}
		printf("Score: %i\n", score);
		for (int i = 0; i < 8; i++)
		{
			puncher[i].update();
		}
	}

	if (keystapped.size() > 0)
	{
		for (int i = 0; i < keystapped.size(); i++)
		{
			keytaps[keystapped[i]] = false;
		}
		keystapped.clear();
	}
}

void Application::render()
{
	SDL_SetRenderDrawColor(renderer, 0x11, 0x11, 0x11, 0xFF);
	SDL_RenderClear(renderer);

	if (ingame) {
		SDL_SetRenderDrawColor(renderer, 0xBB, 0xBB, 0xBB, 0xFF);
		for (int i = 0; i < 8; i++)
		{
			puncher[i].render(renderer, punchsize, SCREEN_HEIGHT - offsetY);
		}

		for (int i = 0; i < musictiles.size(); i++)
		{
			musictiles[i].render(renderer, punchsize);
		}
	}

	SDL_RenderPresent(renderer);
}

void Application::mainLoop()
{
	while (!exitting)
	{
		input();
		update();
		render();
		SDL_Delay((Uint32)(1000.f / 60));
	}
}
