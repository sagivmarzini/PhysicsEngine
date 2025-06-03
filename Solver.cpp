#include "Solver.h"
#include <iostream>

Solver::Solver(const Constraint& constraint, const float deltaTime, const int subSteps)
	: _constraint(constraint), _deltaTime(deltaTime), _subSteps(subSteps)
{
}

void Solver::update(std::vector<PhysicsBody>& bodies, const Vec2& gravity) const
{
	const float subDt = _deltaTime / static_cast<float>(_subSteps);

	// Perform multiple substeps
	for (int step = 0; step < _subSteps; ++step)
	{
		for (auto& body : bodies)
		{
			applyGravity(body, gravity);
			applyConstraint(body);
		}

		// Solve collisions for all bodies in this substep
		solveCollisions(bodies); // Note: pass all bodies, not individual

		// Update positions for all bodies using subDt
		for (auto& body : bodies)
		{
			updatePosition(body, subDt);
		}
	}
}

Constraint Solver::getConstraint() const
{
	return _constraint;
}

void Solver::updatePosition(PhysicsBody& body, const float deltaTime) const
{
	body.updatePosition(deltaTime);
}

void Solver::applyGravity(PhysicsBody& body, const Vec2& gravity) const
{
	body.accelerate(gravity);
}

void Solver::applyConstraint(PhysicsBody& body) const
{
	const Vec2 toConstraint = body.getPosition() - _constraint.position;
	const float distanceToConstraint = toConstraint.distance();

	// Only apply constraint if body is outside the boundary
	if (distanceToConstraint + body.getRadius() > _constraint.radius)
	{
		// Calculate direction from constraint center to body
		Vec2 directionNormal = toConstraint;
		directionNormal.normalize();

		// Position the body at the constraint boundary
		body.setPosition(_constraint.position + directionNormal * (_constraint.radius - body.getRadius()));

		// Reflect velocity component that's pointing into the constraint
		const Vec2 velocity = body.getVelocity(_deltaTime);
		float velocityAlongNormal = velocity.dot(directionNormal);

		// Only reflect if moving into the constraint
		if (velocityAlongNormal > 0)
		{
			Vec2 reflectedVelocity = velocity - directionNormal * 2.0f * velocityAlongNormal;
			body.setVelocity(reflectedVelocity * 0.9f, _deltaTime); // Add damping
		}
	}
}

void Solver::solveCollisions(std::vector<PhysicsBody>& bodies) const
{
	for (auto& body : bodies)
	{
		for (auto& otherBody : bodies)
		{
			if (&body == &otherBody) continue; // Skip self-collision

			Vec2 relativeVelocity = body.getVelocity(_deltaTime) - otherBody.getVelocity(_deltaTime);

			Vec2 collisionAxisNormal = body.getPosition() - otherBody.getPosition();
			float distance = collisionAxisNormal.distance();
			float radiusSum = body.getRadius() + otherBody.getRadius();

			if (distance == 0.0f) continue; // Prevent division by zero

			collisionAxisNormal.normalize();

			float penetration = radiusSum - distance;
			if (penetration > 0)
			{
				Vec2 correction = collisionAxisNormal * (penetration / 2.0f);
				body.setPosition(body.getPosition() + correction);
				otherBody.setPosition(otherBody.getPosition() - correction);
			}

			float velocityAlongNormal = relativeVelocity.dot(collisionAxisNormal);

			// Skip if separating
			if (velocityAlongNormal > 0) continue;

			float restitution = 1.0f; // perfect elastic collision for now
			float impulseMag = -(1 + restitution) * velocityAlongNormal / (1 / body.getMass() + 1 / otherBody.getMass());

			Vec2 impulse = collisionAxisNormal * impulseMag;
			body.setVelocity(body.getVelocity(_deltaTime) + impulse, _deltaTime);
			otherBody.setVelocity(otherBody.getVelocity(_deltaTime) - impulse, _deltaTime);
		}
	}
}