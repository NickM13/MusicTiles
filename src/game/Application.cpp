#include "game\Application.h"
#include "utils\general\Math.h"
#include "menu\Startup.h"
#include "menu\Pause.h"
#include <stdio.h>
#include <iostream>
#include <math.h>

Event Application::e = Event::getInstance();

void Application::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow("Rhythm Game Indev v1.0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	TTF_Init();
	IMG_Init(IMG_INIT_PNG);

	Startup::getInstance().init(SCREEN_WIDTH, SCREEN_HEIGHT);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	TTFont::getInstance().setFont(renderer, "new_courier/cour.ttf", 32);

	Game::getInstance().init(renderer, &SCREEN_WIDTH, &SCREEN_HEIGHT, &fps);

	mainLoop();
}

void Application::input()
{
	e.pollEvents();
	if (e.getExit())
		gamestate = STATE_EXITTING;
	Game::getInstance().input();

}

void Application::update()
{
	if (developer && e.getKey('q') & 1)
		gamestate = STATE_EXITTING;
	if (e.getKey(27) & 2)
	{
		if (gamestate == STATE_INGAME)
			gamestate = STATE_PAUSED;
		else if (gamestate == STATE_PAUSED)
			gamestate = STATE_INGAME;
	}
	if (gamestate == STATE_INGAME)
		Game::getInstance().update();
}

int timetostart = 200;

void Application::render()
{
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(renderer);

	TTFont::getInstance().reset();

	if (gamestate == STATE_STARTING)
	{
		Startup::getInstance().render();
		if (timetostart == 199)
			Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
		timetostart--;
		if (timetostart <= 0)
			gamestate = STATE_INGAME;
	}
	else if (gamestate == STATE_INGAME || gamestate == STATE_PAUSED) {
		if (gamestate == STATE_PAUSED)
		{
			Pause::getInstance().render();
		}
		SDL_SetRenderDrawColor(renderer, 0xBB, 0xBB, 0xBB, 0xFF);
		Game::getInstance().render();
		SideMenu::getInstance().render();
	}

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
		SDL_Delay((Uint32)(std::fmaxf(0, (1000.f / SCREEN_FPS) - (SDL_GetTicks() - start))));
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
	TTFont::getInstance().~TTFont();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = nullptr;
	renderer = nullptr;
	texture = nullptr;
	Mix_Quit();
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}
