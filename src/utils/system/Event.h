#pragma once

#include "utils\general\Singleton.h"
#include <SDL_events.h>
#include <vector>

class Event : public Singleton <Event>
{
	private:

		typedef bool Flag;
		struct Mouse
		{
			Flag moved = false;
			Sint32 x = 0, y = 0;
		}* mouse = new Mouse();

		std::vector<Uint16> pressid;

	public:
		SDL_Event getEvent();

		void pollEvents();

		bool getExit();

		Uint8 getKey(Uint16 id);

		Uint8 getMouse(Uint8 id);

		Mouse getMousePos();

	protected:

		SDL_Event e;
		struct KeyState
		{
			Flag tap = false;
			Flag down = false;
		}*keystates = new KeyState[65536];

		Flag exit = false;

		struct MouseState
		{
			Flag down = false;
		}*mousestates = new MouseState[256];

};