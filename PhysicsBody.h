#pragma once

#include "Vec2.h"

class Renderer;

class PhysicsBody
{
public:
	PhysicsBody(const Vector2& position, const float radius);

	void updatePosition(const float dt);
	void accelerate(const Vector2& acceleration);

	Vector2 getPosition() const;
	void setPosition(const Vector2& position);

	float getRadius() const;
	float getMass() const; // Returns the radius for now

	Vector2 getVelocity(const float dt) const;
	void setVelocity(const Vector2& velocity, const float dt);

	void draw(Renderer& renderer) const;

private:
	Vector2 _positionLast;
	Vector2 _position;
	Vector2 _acceleration;

	float _radius;
};
