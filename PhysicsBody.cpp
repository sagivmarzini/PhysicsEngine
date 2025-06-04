#include "PhysicsBody.h"
#include "Renderer.h"

PhysicsBody::PhysicsBody(const Vector2& position, const float radius)
	: _positionLast(position), _position(position), _acceleration{ 0, 0 }, _radius(radius)
{
}

void PhysicsBody::updatePosition(const float dt)
{
	// Compute how much we moved
	const Vector2 displacement = _position - _positionLast;

	_positionLast = _position;

	_position = _position + displacement + _acceleration * (dt * dt);
	// Reset acceleration
	_acceleration = {};
}

void PhysicsBody::accelerate(const Vector2& acceleration)
{
	_acceleration += acceleration;
}

Vector2 PhysicsBody::getPosition() const
{
	return _position;
}

void PhysicsBody::setPosition(const Vector2& position)
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

Vector2 PhysicsBody::getVelocity(const float dt) const
{
	return (_position - _positionLast) / dt;
}

void PhysicsBody::setVelocity(const Vector2& velocity, const float dt)
{
	// velocity = (current - previous) / dt
	// So: previous = current - velocity * dt
	_positionLast = _position - velocity * dt;
}

void PhysicsBody::draw(Renderer& renderer) const
{
	renderer.drawCircle(_position, _radius, 2, sf::Color::Red);
}