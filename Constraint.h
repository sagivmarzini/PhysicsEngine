#pragma once

#include "Vec2.h"

class Renderer;

struct Constraint
{
	Vector2 position;
	const float width;
	const float height;

	void draw(Renderer& renderer) const;
};