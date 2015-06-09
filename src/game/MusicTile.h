#pragma once
#include "utils/Color.h"
#include <SDL.h>

struct MusicTile
{
	public:
		MusicTile();
		MusicTile(int);
		void update(float speed);
		void render(SDL_Renderer*, int scale);
		void setDelay(Uint16 delay);
		int getExplode();
		Uint8 checkCollision(bool*);
		int getHeight() { return height_; }
		int getRow() { return row_; }
		bool isTapped();
		void destroyTile();
		~MusicTile();
	private:
		float height_;
		bool tapped;
		int row_;
		Color3i color_;
		float explode_;
};
