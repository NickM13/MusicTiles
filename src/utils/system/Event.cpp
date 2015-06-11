#include "utils\system\Event.h"

SDL_Event Event::getEvent()
{
	return e;
}

void Event::pollEvents()
{
	mouse->moved = false;
	for (int i = 0; i < pressid.size(); i++)
	{
		keystates[pressid[i]].tap = false;
	}
	pressid.clear();
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			exit = true;
		}
		else if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym < 65536) {
				keystates[e.key.keysym.sym].down = true;
				keystates[e.key.keysym.sym].tap = true;
				pressid.push_back(e.key.keysym.sym);
			}
		}
		else if (e.type == SDL_KEYUP)
		{
			if (e.key.keysym.sym < 65536) {
				keystates[e.key.keysym.sym].down = false;
			}
		}
		else if (e.type == SDL_MOUSEMOTION)
		{
			mouse->x = e.motion.x;
			mouse->y = e.motion.y;
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			mousestates[e.button.button].down = true;
		}
		else if (e.type == SDL_MOUSEBUTTONUP)
		{
			mousestates[e.button.button].down = false;
		}
	}
}

bool Event::getExit()
{
	return exit;
}

Uint8 Event::getKey(Uint16 id)
{
	Uint8 keydata = 0;
	keydata += (keystates[id].down ? 1 : 0);
	keydata += (keystates[id].tap ? 2 : 0);
	return keydata;
}

Uint8 Event::getMouse(Uint8 id)
{
	Uint8 mousedata = 0;
	mousedata += (mousestates[id].down ? 1 : 0);
	return mousedata;
}

Event::Mouse Event::getMousePos()
{
	return *mouse;
}
