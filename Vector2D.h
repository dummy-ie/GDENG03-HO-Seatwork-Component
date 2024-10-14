#pragma once

namespace math
{
	class Vector2D
	{
	public:
		float x = 0, y = 0;

	public:
		Vector2D() : x(0), y(0) {}
		Vector2D(float x, float y) : x(x), y(y) {}
		Vector2D(const Vector2D& vector) : x(vector.x), y(vector.y) {}
		~Vector2D() {}

	public:
		static Vector2D zero()
		{
			return Vector2D(0, 0);
		}

		static Vector2D one()
		{
			return Vector2D(1, 1);
		}

		bool operator!=(const Vector2D& vec) const
		{
			return x != vec.x || y != vec.y;
		}
	};
}