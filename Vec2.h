#pragma once

struct Vec2
{
	float x;
	float y;

	Vec2 operator+(const Vec2& other) const;
	Vec2& operator+=(const Vec2& other);
	Vec2 operator-(const Vec2& other) const;
	Vec2 operator*(const float s) const;
	Vec2 operator/(const float s) const;

	float getDistance() const;
};
