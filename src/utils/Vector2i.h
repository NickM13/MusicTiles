#pragma once

struct Vector2i
{
	public:
		int x, y;

		Vector2i()
		{
			x = 0;
			y = 0;
		}

		Vector2i(int x_, int y_)
		{
			x = x_;
			y = y_;
		}

		void operator*=(Vector2i vec)
		{
			x *= vec.x;
			y *= vec.y;
		}

		void operator+=(Vector2i vec)
		{
			x += vec.x;
			y += vec.y;
		}

		Vector2i operator*(Vector2i vec)
		{
			return { x * vec.x, y * vec.y };
		}

		Vector2i operator+(Vector2i vec)
		{
			return { x + vec.x, y + vec.y };
		}
};