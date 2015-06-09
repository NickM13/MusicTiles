#include "game/MusicTile.h"
#include <random>

MusicTile::MusicTile()
{
	tapped = false;
	color_ = Color3i(rand() % 256, rand() % 256, rand() % 256);
	height_ = -32;
	row_ = rand()%8;
	explode_ = 0;
}

MusicTile::MusicTile(int row)
{
	tapped = false;
	height_ = -32;
	row_ = row;
	color_ = Color3i(rand() % 256, rand() % 256, rand() % 256);
	explode_ = 0;
}

void MusicTile::update(float speed)
{
	if (!tapped)
		height_ += speed;
	else
		explode_+=0.5f;
}

void MusicTile::render(SDL_Renderer* screen, int scale)
{
	if (tapped)
	{
		SDL_Rect tiles_[4];

		tiles_[0] = { //top left
			row_ * (scale + 1),
			(int)height_, 
			(scale / 2) - explode_ * 2,
			(scale / 4) - explode_
		};

		tiles_[1] = { //bottom left
			row_ * (scale + 1),
			(int)height_ + (scale / 4) + explode_,
			(scale / 2) - explode_ * 2,
			(scale / 4) - explode_
		};

		tiles_[2] = { //bottom right
			row_ * (scale + 1) + (scale / 2) + explode_ * 2,
			(int)height_ + (scale / 4) + explode_,
			(scale / 2) - explode_ * 2,
			(scale / 4) - explode_
		};

		tiles_[3] = { //top right
			row_ * (scale + 1) + (scale / 2) + explode_ * 2,
			(int)height_,
			(scale / 2) - explode_ * 2,
			(scale / 4) - explode_
		};

		SDL_SetRenderDrawColor(screen, color_.r + explode_ / 8.f * (255 - color_.r), color_.g + explode_ / 8.f * (255 - color_.g), color_.b + explode_ / 8.f * (255 - color_.b), 255);

		SDL_RenderFillRects(screen, tiles_, 4);
	}
	else
	{
		SDL_Rect tile_ = { row_ * (scale + 1), (int)height_, scale, scale / 2 };
		SDL_SetRenderDrawColor(screen, color_.r, color_.g, color_.b, 0xFF);
		SDL_RenderFillRect(screen, &tile_);
	}
}

int MusicTile::getExplode()
{
	return explode_;
}

Uint8 MusicTile::checkCollision(bool* keystates)
{
	switch (row_)
	{
	case 0:
		if (keystates['q'])
		{
			tapped = true;
		}
		break;
	case 1:
		if (keystates['w'])
		{
			tapped = true;
		}
		break;
	case 2:
		if (keystates['e'])
		{
			tapped = true;
		}
		break;
	case 3:
		if (keystates['r'])
		{
			tapped = true;
		}
		break;
	case 4:
		if (keystates['a'])
		{
			tapped = true;
		}
		break;
	case 5:
		if (keystates['s'])
		{
			tapped = true;
		}
		break;
	case 6:
		if (keystates['d'])
		{
			tapped = true;
		}
		break;
	case 7:
		if (keystates['f'])
		{
			tapped = true;
		}
		break;
	}
	if (tapped) return row_ + 1;
	else return NULL;
}

bool MusicTile::isTapped()
{
	return tapped;
}

MusicTile::~MusicTile()
{

}
