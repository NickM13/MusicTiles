#pragma once
#include <SDL.h>

struct MusicTile
{
	public:
		MusicTile();
		MusicTile(int, int);
		static SDL_Color getColor(int);
		void update(float speed);
		void render(SDL_Renderer*, int scale);
		void setDelay(Uint16 delay);
		int getExplode();
		Uint8 checkCollision(bool*);
		int getHeight() { return (int)height_; }
		int getRow() { return row_; }
		bool isTapped();
		void destroyTile();
		~MusicTile();
	private:
		float height_;
		bool tapped;
		int row_;
		SDL_Color color_;
		float explode_;
};
