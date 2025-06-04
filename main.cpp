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
	const uint32_t frameRate = 60;
	const float dt = 1.0f / frameRate;
	const int subSteps = 8;
	const Vector2 windowCenter{ windowSize.x / 2.0f, windowSize.y / 2.0f };

	Vector2 gravity{ 0.0f, 1000.0f };
	float bodyRadius = 20.0f;

	Renderer renderer(sf::VideoMode(windowSize), "Sagiv's Physics Engine", frameRate);
	Solver solver(Constraint{ Vector2{0,0}, (float)windowSize.x, (float)windowSize.y }, dt, subSteps);

	// Ball spawning
	Vector2 spawningLocation = windowCenter + Vector2{ 90, 0 };
	sf::Clock spawnClock;
	const float spawnInterval = 1.0f; // seconds
	int ballsSpawned = 0;
	const int maxBalls = 100;
	std::vector<PhysicsBody> bodies = {};
	sf::Clock timeClock;

	while (renderer.isOpen())
	{
		renderer.clear(sf::Color::Black);
		renderer.processEvents();

		// Spawn balls
		if (ballsSpawned < maxBalls && spawnClock.getElapsedTime().asSeconds() >= spawnInterval)
		{
			spawningLocation = Vector2{ static_cast<float>((static_cast<int>(ballsSpawned * 100 + 2 * bodyRadius) % windowSize.x)), windowCenter.y };
			// Create the ball
			bodies.emplace_back(spawningLocation, bodyRadius);
			bodies[ballsSpawned].setVelocity(bodies[ballsSpawned].getPosition() + Vector2{ 1, 1 }, dt);

			ballsSpawned++;
			spawnClock.restart();
		}

		solver.update(bodies, gravity);

		// Render everything
		solver.getConstraint().draw(renderer);
		for (const auto& body : bodies)
		{
			body.draw(renderer);
		}

		renderer.display();
	}

	return 0;
}