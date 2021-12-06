#include "Tile.h"

Tile::Tile(float x, float y, float width, float heigth, sf::Color color)
{
	this->width = width;
	this->heigth = heigth;

	shape.setSize(sf::Vector2f(width, heigth));
	shape.setFillColor(color);
	setPosition(x, y);
}

void Tile::setPosition(int x, int y)
{
	shape.setPosition(x, y);
}

void Tile::createHitbox()
{
	hitbox = new Hitbox(shape.getPosition().x, shape.getPosition().y, width, heigth);
}

const sf::FloatRect Tile::GetGlobalBounds() const
{
	return shape.getGlobalBounds();
}

const bool Tile::Intersects(const sf::FloatRect bounds) const
{
	return shape.getGlobalBounds().intersects(bounds);
}

void Tile::Render(sf::RenderTarget* target)
{
	target->draw(shape);
	if (hitbox)
		hitbox->render(target);
}