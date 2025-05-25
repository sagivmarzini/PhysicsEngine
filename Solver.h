#pragma once

#include "Vec2.h"
#include "PhysicsBody.h"
#include "Constraint.h"
#include <vector>
#include <SFML/Graphics.hpp>

class Solver
{
public:
	Solver(const Constraint& constraint, const int subSteps);

	void update(std::vector<PhysicsBody>& bodies, const float dt, const Vec2& gravity) const;

	Constraint getConstraint() const;

private:
	void updatePosition(PhysicsBody& body, const float dt) const;
	void applyGravity(PhysicsBody& body, const Vec2& gravity) const;
	void applyConstraint(PhysicsBody& body) const;
	void solveCollisions(std::vector<PhysicsBody>& bodies) const;

	Constraint _constraint;
	int _subSteps;
};
