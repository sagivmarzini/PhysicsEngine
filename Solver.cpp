#include "Solver.h"
#include <iostream>

Solver::Solver(const Constraint& constraint, const int subSteps)
	: _constraint(constraint), _subSteps(subSteps)
{
}

void Solver::update(std::vector<PhysicsBody>& bodies, const float dt, const Vec2& gravity) const
{
	const float subDt = dt / static_cast<float>(_subSteps);

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

void Solver::updatePosition(PhysicsBody& body, const float dt) const
{
	body.updatePosition(dt);
}

void Solver::applyGravity(PhysicsBody& body, const Vec2& gravity) const
{
	body.accelerate(gravity);
}

void Solver::applyConstraint(PhysicsBody& body) const
{
	const Vec2 fromCenter = body.getPosition() - _constraint.position;
	const float distanceFromCenter = fromCenter.getDistance();

	if (distanceFromCenter + body.getRadius() > _constraint.radius)
	{
		const Vec2 directionNormal = fromCenter / distanceFromCenter;
		body.setPosition(_constraint.position + directionNormal * (_constraint.radius - body.getRadius()));
	}
}

void Solver::solveCollisions(std::vector<PhysicsBody>& bodies) const
{
	for (auto& body : bodies)
	{
		for (auto& otherBody : bodies)
		{
			if (&body == &otherBody) continue; // Skip self-collision

			const Vec2 collisionAxis = body.getPosition() - otherBody.getPosition();
			const float distance = collisionAxis.getDistance();

			const float radiusSum = body.getRadius() + otherBody.getRadius();
			// If colliding
			if (distance < radiusSum)
			{
				const Vec2 collisionAxisNormal = collisionAxis / distance;
				const float overlap = radiusSum - distance;

				// Move both the colliding objects half the overlap
				body.setPosition(body.getPosition() + collisionAxisNormal * (overlap / 2));
				otherBody.setPosition(otherBody.getPosition() - collisionAxisNormal * (overlap / 2));
			}
		}
	}
}