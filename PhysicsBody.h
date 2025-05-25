#pragma once

#include "Vec2.h"

class PhysicsBody
{
public:
	PhysicsBody(const Vec2& position, const float radius);

	void updatePosition(const float dt);
	void accelerate(const Vec2& acceleration);

	Vec2 getPosition() const;
	void setPosition(const Vec2& position);

	float getRadius() const;

	void setVelocity(const Vec2& velocity, const float dt);

private:
	Vec2 _positionOld;
	Vec2 _positionCurrent;
	Vec2 _acceleration;

	float _radius;
};
