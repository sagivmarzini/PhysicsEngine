#include "Solver.h"
#include <iostream>

Solver::Solver(const Constraint& constraint, const float deltaTime, const int subSteps)
	: _constraint(constraint), _deltaTime(deltaTime), _subSteps(subSteps)
{
}

void Solver::update(std::vector<PhysicsBody>& bodies, const Vector2& gravity) const
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
		//solveCollisions(bodies);

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

void Solver::applyGravity(PhysicsBody& body, const Vector2& gravity) const
{
	body.accelerate(gravity);
}

void Solver::applyConstraint(PhysicsBody& body) const
{
	if (circleIntersectsRectEdges(body.getPosition(), body.getRadius(), _constraint.position, _constraint.width, _constraint.height))
		body.setVelocity(body.getVelocity(_deltaTime) * -1, _deltaTime);
}

void Solver::solveCollisions(std::vector<PhysicsBody>& bodies) const
{
	for (auto& body : bodies)
	{
		for (auto& otherBody : bodies)
		{
			if (&body == &otherBody) continue; // Skip self-collision

			const Vector2 collisionAxis = body.getPosition() - otherBody.getPosition();
			const float distance = collisionAxis.distance();
			const float radiiSum = body.getRadius() + otherBody.getRadius();

			if (distance < radiiSum)
			{
				float penetration = radiiSum - distance;

				const Vector2 collisionAxisNormal = collisionAxis.normal();

				body.setPosition(collisionAxisNormal * -1 * (penetration / 2));
				otherBody.setPosition(collisionAxisNormal * (penetration / 2));
			}
		}
	}
}

Vector2 Solver::closestPointOnLine(const Vector2& p1, const Vector2& p2, const Vector2& circleCenter) const
{
	Vector2 line = p2 - p1;
	Vector2 toCircle = circleCenter - p1;

	float t = toCircle.dot(line) / line.dot(line);
	t = std::clamp(t, 0.0f, 1.0f);

	return p1 + line * t;
}

bool Solver::circleIntersectsLine(const Vector2& p1, const Vector2& p2, const Vector2& center, float radius) const
{
	Vector2 closest = closestPointOnLine(p1, p2, center);
	float distSquared = (center - closest).distanceSquared();

	return distSquared <= radius * radius;
}

bool Solver::circleIntersectsRectEdges(const Vector2& center, float radius, const Vector2& topLeft, float width, float height) const
{
	Vector2 topRight = topLeft + Vector2(width, 0);
	Vector2 bottomLeft = topLeft + Vector2(0, height);
	Vector2 bottomRight = topLeft + Vector2(width, height);

	return
		circleIntersectsLine(topLeft, topRight, center, radius) || // top
		circleIntersectsLine(topRight, bottomRight, center, radius) || // right
		circleIntersectsLine(bottomRight, bottomLeft, center, radius) || // bottom
		circleIntersectsLine(bottomLeft, topLeft, center, radius); // left
}