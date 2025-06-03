#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "PhysicsBody.h"
#include "Renderer.h"
#include "Solver.h"
#include "Vec2.h"
#include "Constraint.h"
#include <iostream>
#include <random>
#include <math.h>

constexpr sf::Vector2u windowSize = { 1500, 800 };

int main()
{
	// Random stuff
	std::random_device rd; // Seed source
	std::mt19937 gen(rd()); // Mersenne Twister RNG

	const uint32_t frameRate = 60;
	const float dt = 1.0f / frameRate;
	const int subSteps = 16;
	const Vec2 windowCenter{ static_cast<float>(windowSize.x) / 2.0f, static_cast<float>(windowSize.y) / 2.0f };

	Vec2 gravity{ 0.0f, 1000.f };
	float bodyRadius = 20.0f;
	std::uniform_int_distribution<> radiusDistribution(10, 20); // Range

	Renderer renderer(sf::VideoMode(windowSize), "Sagiv's Physics Engine", frameRate);
	Solver solver({ windowCenter, std::min(windowSize.x, windowSize.y) * 0.4f }, dt, subSteps);

	// Ball spawning
	Vec2 spawningLocation = windowCenter + Vec2{ 90, -(solver.getConstraint().radius * 0.9f + bodyRadius) };
	sf::Clock spawnClock;
	const float spawnInterval = 0.05f; // seconds
	int ballsSpawned = 0;
	const int maxBalls = 300;
	std::vector<PhysicsBody> bodies = {};
	const float spawnSpeed = 1.0f;  // Initial velocity magnitude
	const float maxAngle = 1.0f;      // Angle variation range (radians)
	const Vec2 fixedSpawnPosition = windowCenter + Vec2{ 0, -200 };
	sf::Clock timeClock;

	while (renderer.isOpen()) {
		renderer.processEvents();

		// Spawn balls
		if (ballsSpawned < maxBalls && spawnClock.getElapsedTime().asSeconds() >= spawnInterval)
		{
			bodyRadius = radiusDistribution(gen);
			spawningLocation = windowCenter + Vec2{ static_cast<float>(ballsSpawned * 50 % static_cast<int>(1.9f * solver.getConstraint().radius)) - (solver.getConstraint().radius * 0.9f) - bodyRadius, 0 };

			// Create the ball
			bodies.emplace_back(spawningLocation, bodyRadius);

			ballsSpawned++;
			spawnClock.restart();
		}

		solver.update(bodies, gravity);
		renderer.render(bodies, solver.getConstraint());
	}

	return 0;
}