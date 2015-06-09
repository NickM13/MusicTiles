#pragma once

struct Color3i /* Opaque color values */
{
	int r, g, b;
	Color3i()
	{
		r = 0;
		g = 0;
		b = 0;
	}

	Color3i(int r_, int g_, int b_)
	{
		r = r_;
		g = g_;
		b = b_;
	}
};

struct Color4i /* Transparent color values */
{
	int a, r, g, b;
	Color4i()
	{
		r = 0;
		g = 0;
		b = 0;
	}

	Color4i(int a_, int r_, int g_, int b_)
	{
		a = a_;
		r = r_;
		g = g_;
		b = b_;
	}
};
