#include "game\Game.h"
#include "utils\system\Event.h"

Event e;
Particle particle;
TTFont font;

void Game::init(SDL_Renderer* renderer, const int* screen_width, const int* screen_height, int* fps_)
{
	e = Event::getInstance();
	particle = Particle::getInstance();
	font = TTFont::getInstance();
	this->renderer = renderer;
	SCREEN_WIDTH = screen_width;
	SCREEN_HEIGHT = screen_height;
	fps = fps_;
	
	SideMenu::getInstance().init(renderer, punchsize * 11 + 11, 0, *SCREEN_WIDTH, *SCREEN_HEIGHT);
	particle.init(renderer);
	printf("%i,          %i\n", *SCREEN_WIDTH, *SCREEN_HEIGHT);
	puncher[0].bind('a');
	puncher[1].bind('s');
	puncher[2].bind('d');
	puncher[3].bind('f');
	puncher[4].bind('g');
	puncher[5].bind('h');
	puncher[6].bind('j');
	puncher[7].bind('k');
	puncher[8].bind('l');
	puncher[9].bind(';');

	tiletex = new LTexture[10];
	tiletex[0].init(renderer);
	tiletex[0].loadIMG("res/img/Red.bmp");

	tiletex[1].init(renderer);
	tiletex[1].loadIMG("res/img/Yellow.bmp");

	tiletex[2].init(renderer);
	tiletex[2].loadIMG("res/img/Green.bmp");

	tiletex[3].init(renderer);
	tiletex[3].loadIMG("res/img/Cyan.bmp");

	tiletex[4].init(renderer);
	tiletex[4].loadIMG("res/img/Blue.bmp");

	for (int i = 0; i < 5; i++)
	{
		tiletex[i + 5] = tiletex[i];
	}
}

void Game::input()
{
	if (e.getKey('z') & 1)
		extrakeys[0] = true;
	else
		extrakeys[0] = false;

	if (e.getKey('r') & 2)
		extrakeys[1] = true;
	else
		extrakeys[1] = false;

	if (e.getKey('x') & 1)
		extrakeys[2] = true;
	else
		extrakeys[2] = false;
}

bool levelLoaded = false;

void Game::update()
{
	if (e.getMouse(1) & 1)
		for (int i = 0; i < 50; i++)
			particle.create(e.getMousePos().x, e.getMousePos().y, 5, (rand() % 200 - 100) / 20.f, (rand() % 200 - 100) / 20.f, 120, { 0x33, 0x33, 0x33, 50 });
	particle.update();
	for (int i = 0; i < 10; i++)
	{
		punchkeys[i] = puncher[i].isKey();
	}
	if (!inlevel || developer && (extrakeys[1])) {
		if ((developer && extrakeys[1])) {
			musictiles.clear();
			tilesremaining = 0;
		}
		levelLoaded = false;
		stage++;
		level.generateRandom((int)levellength);
		inlevel = true;
		levellength += 3.5f;
	}

	if (!levelLoaded)
	{
		int spacing = 0;
		while (level.getByte() < level.getSize())
		{
			int currLength = level.readByte();
			for (int i = 0; i < currLength; i++) {
				musictiles.push_back(MusicTile(renderer, level.readByte(), spacing));
				musictiles[musictiles.size() - 1].setTexture(&tiletex[musictiles[musictiles.size() - 1].getRow()]);
				tilesremaining++;
			}
			spacing += (int)((punchsize * (8.f / stage)) + punchsize / 1.9f);
		}
		levelLoaded = true;
		std::cout << "Level loaded" << std::endl;
		std::cout << "Awaiting tile destruction..." << std::endl;
	}

	if (tilesremaining <= 0)
	{
		inlevel = false;
	}

	for (int i = musictiles.size() - 1; i >= 0; i--)
	{
		if (extrakeys[0])
			musictiles[i].update(std::fmin(speed + (stage / 4.f), 6) * 8);
		else
			musictiles[i].update(std::fmin(speed + (stage / 4.f), 6));

		if (musictiles[i].isTapped())
		{
			if (musictiles[i].getExplode() >= 8)
				musictiles.erase(musictiles.begin() + i);
		}
		else
		{

			if (musictiles[i].getHeight() >= *SCREEN_HEIGHT - punchsize / 2 - offsetY && musictiles[i].getHeight() <= *SCREEN_HEIGHT + punchsize - offsetY) {
				if (punchkeys[musictiles[i].getRow()])
				{
					punchkeys[musictiles[i].getRow()] = false;
					if (musictiles[i].getHeight() >= *SCREEN_HEIGHT - offsetY && musictiles[i].getHeight() <= *SCREEN_HEIGHT - offsetY + punchsize / 2)
					{
						puncher[musictiles[i].getRow()].pressed(ANIM_PERFECT);
						score += 125;
						tilesperfect++;
					}
					else
					{
						puncher[musictiles[i].getRow()].pressed(ANIM_HIT);
						score += 75;
					}
					tilesremaining--;
					tilespunched++;
					musictiles[i].destroyTile(musictiles[i].getRow() * punchsize + (musictiles[i].getRow() >= 5 ? punchsize : 0) + punchsize / 2, musictiles[i].getHeight());
					streak++;
				}
				else
				{
					if (puncher[musictiles[i].getRow()].check)
					{
						score += 100;
						puncher[musictiles[i].getRow()].pressed(ANIM_COMBO);
						doubles++;
						tilesremaining--;
						tilespunched++;
						musictiles[i].destroyTile(musictiles[i].getRow() * punchsize + (musictiles[i].getRow() >= 5 ? punchsize : 0) + punchsize / 2, musictiles[i].getHeight());
					}
				}
			}

			if (musictiles[i].getHeight() > *SCREEN_HEIGHT)
			{
				puncher[musictiles[i].getRow()].pressed(ANIM_MISS);
				musictiles.erase(musictiles.begin() + i);
				score -= 50;
				tilesremaining--;
				tilesmissed++;
				if (streak > highstreak)
					highstreak = streak;
				streak = 0;
			}
		}
	}
	for (int i = 0; i < 10; i++)
	{
		if (punchkeys[i])
		{
			puncher[i].pressed(ANIM_MISS);
			score -= 25;
			tilesmissed++;
			if (streak > highstreak)
				highstreak = streak;
			streak = 0;
		}
	}
	for (int i = 0; i < 10; i++)
	{
		puncher[i].update();
	}
}

void Game::render()
{
	for (int i = 0; i < 10; i++)
	{
		int* tcolor_ = puncher[i].getColor();
		SDL_Rect trect_ = { i * (punchsize + 1) + (punchsize * (int)(i >= 5)), *SCREEN_HEIGHT - offsetY, punchsize, punchsize };
		SDL_Rect tback_ = { i * (punchsize + 1) + (punchsize * (int)(i >= 5)), 0, punchsize, *SCREEN_HEIGHT - offsetY };
		SDL_Color bcolor_ = { MusicTile::getColor(i).r / 2, MusicTile::getColor(i).g / 2, MusicTile::getColor(i).b / 2, MusicTile::getColor(i).a };
		SDL_SetRenderDrawColor(renderer, fmin(fmax(bcolor_.r + tcolor_[0], 0), 255), fmin(fmax(bcolor_.g + tcolor_[1], 0), 255), fmin(fmax(bcolor_.b + tcolor_[2], 0), 255), 127 + puncher[i].ac_);
		SDL_RenderFillRect(renderer, &tback_);
		SDL_SetRenderDrawColor(renderer, fmin(tcolor_[0] + 127, 127), fmin(tcolor_[1] + 127, 127), fmin(tcolor_[2] + 127, 127), 255);
		SDL_RenderFillRect(renderer, &trect_);
	}

	for (unsigned int i = 0; i < musictiles.size(); i++)
	{
		musictiles[i].render(punchsize);
	}

	Particle::getInstance().render();

	int spacing = 10;
	int s = 6;;
	font.setSize(16);
	font.setAlignment(ALIGN_RIGHT);
	{
		spacing += font.write(std::string("Score: " + Math::numToString(score)).c_str(), *SCREEN_WIDTH - 16, spacing).h + s;
		spacing += font.write(std::string("Stage: " + Math::numToString(stage)).c_str(), *SCREEN_WIDTH - 16, spacing).h + s;
		spacing += font.write(std::string("Hit: " + Math::numToString(tilespunched)).c_str(), *SCREEN_WIDTH - 16, spacing).h + s;
		spacing += font.write(std::string("Missed: " + Math::numToString(tilesmissed)).c_str(), *SCREEN_WIDTH - 16, spacing).h + s;
		spacing += font.write(std::string("Remaining: " + Math::numToString(tilesremaining)).c_str(), *SCREEN_WIDTH - 16, spacing).h + s;
		spacing += font.write(std::string("Perfect: " + Math::numToString(tilesperfect)).c_str(), *SCREEN_WIDTH - 16, spacing).h + s;
		spacing += font.write(std::string("Streak: " + Math::numToString(streak)).c_str(), *SCREEN_WIDTH - 16, spacing).h + s;
		spacing += font.write(std::string("High Streak: " + Math::numToString(highstreak)).c_str(), *SCREEN_WIDTH - 16, spacing).h + s;
		spacing += font.write(std::string("Doubles: " + Math::numToString(doubles)).c_str(), *SCREEN_WIDTH - 16, spacing).h + s;
		spacing += font.write(std::string("FPS: " + Math::numToString(*fps)).c_str(), *SCREEN_WIDTH - 16, spacing).h + s;
	}
	font.reset();

	font.setAlignment(ALIGN_CENTER);
	{
		for (int i = 0; i < 10; i++)
		{
			const char* bound = &(puncher[i].boundkey);
			std::cout << (int)bound[1] << std::endl;
			font.write(bound, (punchsize + 1) * i + punchsize / 2 + (punchsize * (int)(i >= 5)), *SCREEN_HEIGHT - offsetY + punchsize / 4);
		}
	}

	font.setAlignment(ALIGN_LEFT);
	{

	}

}
