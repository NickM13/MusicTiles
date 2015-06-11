#include "game\entity\MusicTile.h"

#include <random>

#include "gfx\particle\Particle.h"

MusicTile::MusicTile()
{
	tapped = false;
	height_ = -32;
	row_ = rand()%10;
	explode_ = 0;
	color_ = getColor(row_);
}

MusicTile::MusicTile(SDL_Renderer* renderer, int row, int height = 0)
{
	renderer_ = renderer;
	tapped = false;
	height_ = -32 - height;
	row_ = row;
	explode_ = 0;
	color_ = getColor(row_);
}

void MusicTile::setTexture(LTexture* texture)
{
	texture_ = texture;
}

SDL_Color MusicTile::getColor(int id)
{
	switch (id)
	{
	case 0:
		return{ 255, 0, 0 };
		break;
	case 1:
		return{ 255, 255, 0 };
		break;
	case 2:
		return{ 0, 255, 0 };
		break;
	case 3:
		return{ 0, 255, 255 };
		break;
	case 4:
		return{ 0, 0, 255 };
		break;



	case 5:
		return{ 255, 0, 0 };
		break;
	case 6:
		return{ 255, 255, 0 };
		break;
	case 7:
		return{ 0, 255, 0 };
		break;
	case 8:
		return{ 0, 255, 255 };
		break;
	case 9:
		return{ 0, 0, 255 };
		break;
	}
}

void MusicTile::update(float speed)
{
	if (!tapped)
		height_ += speed;
	else
		explode_+=0.5f;
}

int offsetX;

void MusicTile::render(int scale)
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

		SDL_SetRenderDrawColor(renderer_, (int)(color_.r + explode_ / 8.f * (255 - color_.r)), (int)(color_.g + explode_ / 8.f * (255 - color_.g)), (int)(color_.b + explode_ / 8.f * (255 - color_.b)), 255);

		SDL_RenderFillRects(renderer_, tiles_, 4);
	}
	else
	{
		if (height_ > -scale) {
			if (texture_ != nullptr)
			{
				texture_->render( row_ * (scale + 1) + offsetX, (int)height_);
			}
			else
			{
				SDL_Rect tile_ = { row_ * (scale + 1) + offsetX, (int)height_, scale, scale / 2 };
				SDL_SetRenderDrawColor(renderer_, color_.r, color_.g, color_.b, 0xFF);
				SDL_RenderFillRect(renderer_, &tile_);
			}
		}
	}
}

int MusicTile::getExplode()
{
	return (int)explode_;
}

bool MusicTile::isTapped()
{
	return tapped;
}

void MusicTile::destroyTile(int x, int y)
{
	tapped = true;
	explode_ = 0;
	for (int i = 0; i < 150; i++)
		Particle::getInstance().create(x, y, rand() % 3 + 8, fmod(rand(), 9001.f) / 1800.2f * ((rand() % 2) * 2 - 1), -fmod(rand(), 9001.f) / 1800.2f, 150);
}

MusicTile::~MusicTile()
{

}
