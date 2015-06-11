#pragma once

#include "utils\general\Singleton.h"
#include "gfx\Font.h"
#include <SDL.h>
#include <string>

class Startup : public Singleton < Startup >
{
	public:
		void init(int, int);
		void update();
		void render();
		int getTime();

	private:
		int counter;
		int width_, height_;

		std::string project = "A Rhythmatic Game";
		std::string description = "Indev v1.0";
		std::string developer = "By Nick Mead";

};