#include "Startup.h"

void Startup::init(int width, int height)
{
	counter = 0;
	width_ = width;
	height_ = height;
}

void Startup::update()
{

}

void Startup::render()
{
	int s = 0;
	counter++;
	TTFont::getInstance().setSize(32);
	TTFont::getInstance().setAlignment(ALIGN_CENTER);
	TTFont::getInstance().setColor({ 100, 255, 255 });
	s += TTFont::getInstance().write(project.c_str(), width_ / 2, height_ / 2).h;
	TTFont::getInstance().setSize(14);
	s += TTFont::getInstance().write(description.c_str(), width_ / 2, height_ / 2 + s).h;
	TTFont::getInstance().write(developer.c_str(), width_ / 2, height_ / 2 + s);
}

int Startup::getTime()
{
	return counter;
}
