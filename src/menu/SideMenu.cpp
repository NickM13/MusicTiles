#include "menu\SideMenu.h"

void SideMenu::init(SDL_Renderer* renderer, int x0, int y0, int x1, int y1)
{
	renderer_ = renderer;
	background_ = { x0, y0, x1 - x0, y1 - y0 };
}

void SideMenu::render()
{
	SDL_SetRenderDrawColor(renderer_, 0x00, 0x00, 0x00, 0x40);
	SDL_RenderFillRect(renderer_, &background_);
	SDL_SetRenderDrawColor(renderer_, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderDrawRect(renderer_, &background_);
}
