#include "PhysicsBody.h"

PhysicsBody::PhysicsBody(const Vec2& position, const float radius)
	: _positionLast(position), _position(position), _acceleration{ 0, 0 }, _radius(radius)
{
}

void PhysicsBody::updatePosition(const float dt)
{
	// Compute how much we moved
	const Vec2 displacement = _position - _positionLast;
	// Update position
	_positionLast = _position;

	_position = _position + displacement + _acceleration * (dt * dt);
	// Reset acceleration
	_acceleration = {};
}

void PhysicsBody::accelerate(const Vec2& acceleration)
{
	_acceleration += acceleration;
}

Vec2 PhysicsBody::getPosition() const
{
	return _position;
}

void PhysicsBody::setPosition(const Vec2& position)
{
	_position = position;
}

float PhysicsBody::getRadius() const
{
	return _radius;
}

float PhysicsBody::getMass() const
{
	return _radius;
}

Vec2 PhysicsBody::getVelocity(const float dt) const
{
	return (_position - _positionLast) / dt;
}

void PhysicsBody::setVelocity(const Vec2& velocity, const float dt)
{
	// velocity = (current - previous) / dt
	// So: previous = current - velocity * dt
	_positionLast = _position - velocity * dt;
}