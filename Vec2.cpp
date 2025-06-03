#include "Vec2.h"
#include <math.h>

Vec2 Vec2::operator+(const Vec2& other) const
{
	return Vec2{ x + other.x, y + other.y };
}

Vec2& Vec2::operator+=(const Vec2& other)
{
	x += other.x;
	y += other.y;

	return *this;
}

Vec2 Vec2::operator-(const Vec2& other) const
{
	return Vec2{ x - other.x, y - other.y };
}

Vec2 Vec2::operator*(const float s) const
{
	return Vec2{ x * s, y * s };
}

Vec2 Vec2::operator/(const float s) const
{
	return Vec2{ x / s, y / s };
}

float Vec2::distance() const
{
	return sqrt(x * x + y * y);
}

void Vec2::normalize()
{
	float length = distance();

	if (length > 0.0f)
	{
		x /= length;
		y /= length;
	}
}

float Vec2::dot(const Vec2& other) const
{
	return x * other.x + y * other.y;
}