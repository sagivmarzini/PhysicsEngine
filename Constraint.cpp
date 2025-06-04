#include "Constraint.h"
#include "Renderer.h"

void Constraint::draw(Renderer& renderer) const
{
	renderer.drawRectangle(position, width, height, 2, sf::Color::Transparent);
}