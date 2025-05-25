#include "PhysicsBody.h"

PhysicsBody::PhysicsBody(const Vec2& position, const float radius)
	: _positionOld(position), _positionCurrent(position), _acceleration{ 0, 0 }, _radius(radius)
{
}

void PhysicsBody::updatePosition(const float dt)
{
	const Vec2 velocity = _positionCurrent - _positionOld;

	_positionOld = _positionCurrent;

	// Verlet integration
	_positionCurrent = _positionCurrent + velocity + _acceleration * dt * dt;

	_acceleration = {};
}

void PhysicsBody::accelerate(const Vec2& acceleration)
{
	_acceleration += acceleration;
}

Vec2 PhysicsBody::getPosition() const
{
	return _positionCurrent;
}

void PhysicsBody::setPosition(const Vec2& position)
{
	_positionCurrent = position;
}

float PhysicsBody::getRadius() const
{
	return _radius;
}

void PhysicsBody::setVelocity(const Vec2& velocity, const float dt)
{
	// velocity = (current - previous) / dt
	   // So: previous = current - velocity * dt
	_positionOld = _positionCurrent - velocity * dt;
}