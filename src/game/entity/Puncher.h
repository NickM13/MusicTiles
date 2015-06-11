#pragma once

#include <SDL_pixels.h>

#include "utils\system\Event.h"

enum PAnimation
{
	ANIM_HIT,
	ANIM_MISS,
	ANIM_PERFECT,
	ANIM_COMBO
};

struct Puncher
{
	PAnimation animation_ = ANIM_HIT;
	int ac_ = 0;

	char boundkey = 'a';

	bool check = false;

	void bind(char key)
	{
		boundkey = key;
	}

	void update()
	{
		if (ac_ > 0) ac_ -= 4;
	}

	int* getColor()
	{
		int* color_ = new int[3];

		color_[0] = (ac_ * (animation_ == ANIM_MISS ? 1 : -1)) + (ac_ * (animation_ == ANIM_COMBO ? 1 : 0));
		color_[1] = (ac_ * (animation_ == ANIM_HIT ? 1 : -1)) + (ac_ * (animation_ == ANIM_COMBO ? 1 : 0));
		color_[2] = (ac_ * (animation_ == ANIM_PERFECT ? 1 : -1)) + (ac_ * (animation_ == ANIM_COMBO ? 1 : 0));

		return color_;
	}

	bool isKey()
	{
		check = (bool)(Event::getInstance().getKey(boundkey) & 2);
		return check;
	}

	void pressed(PAnimation animation)
	{
		ac_ = 128;
		animation_ = animation;
		std::cout << boundkey << std::endl;
	}
};
