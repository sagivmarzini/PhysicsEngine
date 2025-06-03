#include "Renderer.h"

Renderer::Renderer(const sf::VideoMode& videoMode, const std::string& windowName, const int maxFrameRate)
	: _window(videoMode, windowName)
{
	_window.setFramerateLimit(maxFrameRate);
}

void Renderer::render(const std::vector<PhysicsBody>& bodies, const Constraint& constraint)
{
	_window.clear(sf::Color::Black);

	for (const auto& body : bodies)
	{
		sf::CircleShape circle(body.getRadius());
		circle.setFillColor(sf::Color::Red);
		circle.setOutlineThickness(2);

		circle.setOrigin({ body.getRadius(), body.getRadius() }); // Set origin to center
		const auto& position = body.getPosition();
		circle.setPosition({ position.x, position.y });

		_window.draw(circle);
	}

	// Render the constraint
	sf::CircleShape circle(constraint.radius);
	circle.setOutlineColor(sf::Color::White);
	circle.setOutlineThickness(3);
	circle.setFillColor(sf::Color::Transparent);

	circle.setOrigin({ constraint.radius, constraint.radius }); // Set origin to center
	const auto& position = constraint.position;
	circle.setPosition({ position.x, position.y });

	_window.draw(circle);

	_window.display();
}

void Renderer::processEvents()
{
	const std::optional event = _window.pollEvent();

	if (event.has_value() && event->is<sf::Event::Closed>())
		_window.close();
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