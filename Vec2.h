#pragma once

struct Vector2
{
	float x;
	float y;

	Vector2 operator+(const Vector2& other) const;
	Vector2& operator+=(const Vector2& other);
	Vector2 operator-(const Vector2& other) const;
	Vector2 operator*(const float s) const;
	Vector2 operator/(const float s) const;

	float distance() const;
	float distanceSquared() const;
	Vector2 normal() const;
	float dot(const Vector2& other) const;
};
