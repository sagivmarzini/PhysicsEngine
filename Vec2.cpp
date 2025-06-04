#include "Vec2.h"
#include <math.h>

Vector2 Vector2::operator+(const Vector2& other) const
{
	return Vector2{ x + other.x, y + other.y };
}

Vector2& Vector2::operator+=(const Vector2& other)
{
	x += other.x;
	y += other.y;

	return *this;
}

Vector2 Vector2::operator-(const Vector2& other) const
{
	return Vector2{ x - other.x, y - other.y };
}

Vector2 Vector2::operator*(const float s) const
{
	return Vector2{ x * s, y * s };
}

Vector2 Vector2::operator/(const float s) const
{
	return Vector2{ x / s, y / s };
}

float Vector2::distance() const
{
	return sqrt(x * x + y * y);
}

float Vector2::distanceSquared() const
{
	return x * x + y * y;
}

Vector2 Vector2::normal() const
{
	if (const float length = distance() > 0.0f)
	{
		return Vector2{ x / length, y / length };
	}

	return Vector2{ 0,0 };
}

float Vector2::dot(const Vector2& other) const
{
	return x * other.x + y * other.y;
}