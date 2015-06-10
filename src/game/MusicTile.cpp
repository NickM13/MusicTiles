#include "game/MusicTile.h"
#include <random>

MusicTile::MusicTile()
{
	tapped = false;
	height_ = -32;
	row_ = rand()%10;
	explode_ = 0;
	color_ = getColor(row_);
}

MusicTile::MusicTile(int row, int height = 0)
{
	tapped = false;
	height_ = -32 - height;
	row_ = row;
	explode_ = 0;
	color_ = getColor(row_);
}

SDL_Color MusicTile::getColor(int id)
{
	SDL_Color tempcolor_;
	switch (id)
	{
	case 0:
		tempcolor_ = { 255, 0, 0 };
		break;
	case 1:
		tempcolor_ = { 255, 255, 0 };
		break;
	case 2:
		tempcolor_ = { 0, 255, 0 };
		break;
	case 3:
		tempcolor_ = { 0, 255, 255 };
		break;
	case 4:
		tempcolor_ = { 0, 0, 255 };
		break;



	case 5:
		tempcolor_ = { 255, 0, 0 };
		break;
	case 6:
		tempcolor_ = { 255, 255, 0 };
		break;
	case 7:
		tempcolor_ = { 0, 255, 0 };
		break;
	case 8:
		tempcolor_ = { 0, 255, 255 };
		break;
	case 9:
		tempcolor_ = { 0, 0, 255 };
		break;
	}
	return tempcolor_;
}

void MusicTile::update(float speed)
{
	if (!tapped)
		height_ += speed;
	else
		explode_+=0.5f;
}

int offsetX;

void MusicTile::render(SDL_Renderer* screen, int scale)
{
	if (row_ >= 5)
		offsetX = scale;
	else
		offsetX = 0;
	if (tapped)
	{
		SDL_Rect tiles_[4];

		tiles_[0] = { //top left
			row_ * (scale + 1) + offsetX,
			(int)height_, 
			(scale / 2) - explode_ * 2,
			(scale / 4) - explode_
		};

		tiles_[1] = { //bottom left
			row_ * (scale + 1) + offsetX,
			(int)height_ + (scale / 4) + explode_,
			(scale / 2) - explode_ * 2,
			(scale / 4) - explode_
		};

		tiles_[2] = { //bottom right
			(int)(row_ * (scale + 1) + (scale / 2) + explode_ * 2) + offsetX,
			(int)height_ + (scale / 4) + explode_,
			(int)((scale / 2) - explode_ * 2),
			(int)((scale / 4) - explode_)
		};

		tiles_[3] = { //top right
			(int)(row_ * (scale + 1) + (scale / 2) + explode_ * 2) + offsetX,
			(int)height_,
			(int)((scale / 2) - explode_ * 2),
			(int)((scale / 4) - explode_)
		};

		SDL_SetRenderDrawColor(screen, (int)(color_.r + explode_ / 8.f * (255 - color_.r)), (int)(color_.g + explode_ / 8.f * (255 - color_.g)), (int)(color_.b + explode_ / 8.f * (255 - color_.b)), 255);

		SDL_RenderFillRects(screen, tiles_, 4);
	}
	else
	{
		SDL_Rect tile_ = { row_ * (scale + 1) + offsetX, (int)height_, scale, scale / 2 };
		SDL_SetRenderDrawColor(screen, color_.r, color_.g, color_.b, 0xFF);
		SDL_RenderFillRect(screen, &tile_);
	}
}

int MusicTile::getExplode()
{
	return (int)explode_;
}

Uint8 MusicTile::checkCollision(bool* keystates)
{
	switch (row_)
	{
	case 0:
		if (keystates['a'])
		{
			tapped = true;
		}
		break;
	case 1:
		if (keystates['s'])
		{
			tapped = true;
		}
		break;
	case 2:
		if (keystates['d'])
		{
			tapped = true;
		}
		break;
	case 3:
		if (keystates['f'])
		{
			tapped = true;
		}
		break;
	case 4:
		if (keystates['g'])
		{
			tapped = true;
		}
		break;
	case 5:
		if (keystates['h'])
		{
			tapped = true;
		}
		break;
	case 6:
		if (keystates['j'])
		{
			tapped = true;
		}
		break;
	case 7:
		if (keystates['k'])
		{
			tapped = true;
		}
		break;
	case 8:
		if (keystates['l'])
		{
			tapped = true;
		}
		break;
	case 9:
		if (keystates[';'])
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
