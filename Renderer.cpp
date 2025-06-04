#include "Renderer.h"

Renderer::Renderer(const sf::VideoMode& videoMode, const std::string& windowName, const int maxFrameRate)
	: _window(videoMode, windowName)
{
	_window.setFramerateLimit(maxFrameRate);
}

void Renderer::drawCircle(Vector2 center, float radius, float borderThickness, sf::Color color)
{
	sf::CircleShape circle(radius);
	circle.setOrigin({ radius, radius });
	circle.setPosition({ center.x, center.y });
	circle.setFillColor(color);
	circle.setOutlineColor(sf::Color::White);
	circle.setOutlineThickness(borderThickness);
	_window.draw(circle);
}

void Renderer::drawRectangle(Vector2 topLeft, float width, float height, float borderThickness, sf::Color color)
{
	sf::RectangleShape shape({ width - 2 * borderThickness, height - 2 * borderThickness });
	shape.setPosition({ topLeft.x + borderThickness, topLeft.y + borderThickness });
	shape.setFillColor(color);
	shape.setOutlineColor(sf::Color::White);
	shape.setOutlineThickness(borderThickness);
	_window.draw(shape);
}

void Renderer::processEvents()
{
	const std::optional event = _window.pollEvent();

	if (!event.has_value()) return;

	if (event->is<sf::Event::Closed>())
	{
		_window.close();
	}
	else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
	{
		if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
			_window.close();
	}
}

bool Renderer::isOpen() const
{
	return _window.isOpen();
}

int Renderer::getWindowWidth() const
{
	return _window.getSize().x;
}

int Renderer::getWindowHeight() const
{
	return _window.getSize().y;
}

void Renderer::clear(sf::Color color)
{
	_window.clear(color);
}

void Renderer::display()
{
	_window.display();
}