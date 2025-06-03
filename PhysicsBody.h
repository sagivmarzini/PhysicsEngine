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
	float getMass() const; // Returns the radius for now

	Vec2 getVelocity(const float dt) const;
	void setVelocity(const Vec2& velocity, const float dt);

private:
	Vec2 _positionLast;
	Vec2 _position;
	Vec2 _acceleration;

	float _radius;
};
