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

	//void render(const std::vector<PhysicsBody>& bodies, const Constraint& constraint);

	void drawCircle(Vector2 center, float radius, float borderThickness, sf::Color color);
	void drawRectangle(Vector2 topLeft, float width, float height, float borderThickness, sf::Color color);

	void processEvents();

	bool isOpen() const;
	int getWindowWidth() const;
	int getWindowHeight() const;

	void clear(sf::Color color);
	void display();

private:
	sf::RenderWindow _window;
};
