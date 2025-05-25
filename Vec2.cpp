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

float Vec2::getDistance() const
{
	return sqrt(x * x + y * y);
}