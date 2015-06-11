#pragma once

#include <SDL.h>
#include <vector>

#include "utils\struct\Vector2i.h"
#include "utils\general\Singleton.h"

class Particle : public Singleton <Particle>
{
public:
	void init(SDL_Renderer* renderer)
	{
		renderer_ = renderer;
	}

	void create(int x, int y, int size, float vx, float vy, int lifespan, SDL_Color color)
	{
		SDL_Rect r = { x, y, size, size };
		particles.push_back({ r, vx, vy, 0, lifespan, color });
	}

	void create(int x, int y, int size, float vx, float vy, int lifespan)
	{
		SDL_Rect r = { x, y, size, size };
		particles.push_back({ r, vx, vy, 0, lifespan, { rand() % 200 + 56, rand() % 200 + 56, rand() % 200 + 56, rand() % 56 + 200 } });
	}

	void update()
	{
		for (int i = particles.size() - 1; i >= 0; i--)
		{
			particles[i].life++;
			if (particles[i].life >= particles[i].mlife)
			{
				particles.erase(particles.begin() + i);
				continue;
			}
			particles[i].x += particles[i].vx;
			particles[i].y += particles[i].vy;
			particles[i].partrect.x = (int)particles[i].x;
			particles[i].partrect.y = (int)particles[i].y;
			particles[i].vy += 0.2f;
		}
	}

	void render()
	{
		for (int i = 0; i < particles.size(); i++)
		{
			SDL_SetRenderDrawColor(renderer_, particles[i].color.r, particles[i].color.g, particles[i].color.b, particles[i].color.a);
			SDL_RenderFillRect(renderer_, &particles[i].partrect);
		}
	}

private:
	SDL_Renderer* renderer_;

	struct TParticle
	{
		SDL_Rect partrect;
		float x, y;
		float vx, vy;
		int life = 0;
		int mlife = 0;
		SDL_Color color;
		TParticle(SDL_Rect pr, float vx_, float vy_, int l, int ml, SDL_Color c)
		{
			x = pr.x;
			y = pr.y;
			partrect = pr;
			vx = vx_;
			vy = vy_;
			life = l;
			mlife = ml;
			color = c;
		}
	};

	std::vector<TParticle> particles;

};