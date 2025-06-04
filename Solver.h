#pragma once

#include "Vec2.h"
#include "PhysicsBody.h"
#include "Constraint.h"
#include <vector>
#include <SFML/Graphics.hpp>

class Solver
{
public:
	Solver(const Constraint& constraint, const float deltaTime, const int subSteps);

	void update(std::vector<PhysicsBody>& bodies, const Vector2& gravity) const;

	Constraint getConstraint() const;

private:
	void updatePosition(PhysicsBody& body, const float deltaTime) const;
	void applyGravity(PhysicsBody& body, const Vector2& gravity) const;
	void applyConstraint(PhysicsBody& body) const;
	void solveCollisions(std::vector<PhysicsBody>& bodies) const;

	Vector2 closestPointOnLine(const Vector2& p1, const Vector2& p2, const Vector2& circleCenter) const;
	bool circleIntersectsLine(const Vector2& p1, const Vector2& p2, const Vector2& center, float radius) const;
	bool circleIntersectsRectEdges(const Vector2& center, float radius, const Vector2& topLeft, float width, float height) const;

	Constraint _constraint;
	float _deltaTime;
	int _subSteps;
};
