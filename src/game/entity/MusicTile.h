#pragma once
#include <SDL.h>
#include <gfx\LTexture.h>

struct MusicTile
{
	public:
		MusicTile();
		MusicTile(SDL_Renderer*, int, int);
		void setTexture(LTexture*);
		static SDL_Color getColor(int);
		void update(float speed);
		void render(int scale);
		void setDelay(Uint16 delay);
		int getExplode();
		int getHeight() { return (int)height_; }
		int getRow() { return row_; }
		bool isTapped();
		void destroyTile(int, int);
		~MusicTile();
	private:
		SDL_Renderer* renderer_ = nullptr;
		LTexture* texture_ = nullptr;
		SDL_Color color_;

		float height_;
		int row_;

		bool tapped;
		float explode_;
};
