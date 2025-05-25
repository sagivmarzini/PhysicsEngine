#pragma once

#include "PhysicsBody.h"
#include "Constraint.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Renderer
{
public:
	Renderer(const sf::VideoMode& videoMode, const std::string& windowName, const int maxFrameRate = 60);

	void render(const std::vector<PhysicsBody>& bodies, const Constraint& constraint);
	void processEvents();

	bool isOpen() const;
	int getWindowWidth() const;
	int getWindowHeight() const;

private:
	sf::RenderWindow _window;
};
