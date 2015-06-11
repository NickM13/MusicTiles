#pragma once

struct Vector3f
{
	public:
		float x, y, z;
		Vector3f()
		{
			x = 0;
			y = 0;
			z = 0;
		}

		Vector3f(int x_, int y_, int z_)
		{
			x = x_;
			y = y_;
			z = z_;
		}
};
