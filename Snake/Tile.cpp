#include "Tile.h"

Tile::Tile(float x, float y, float width, float heigth, sf::Color color)
{
	this->width = width;
	this->heigth = heigth;

	shape.setSize(sf::Vector2f(width, heigth));
	shape.setFillColor(color);
	setPosition(x, y);
}

sf::Vector2f  Tile::getPosition()
{
	return shape.getPosition();
}

void Tile::setPosition(int x, int y)
{
	shape.setPosition(x, y);
}

void Tile::createHitbox()
{
	hitbox = new Hitbox(shape.getPosition().x, shape.getPosition().y, width, heigth);
}

sf::FloatRect Tile::getNextPosition(sf::Vector2f move)
{
	return sf::FloatRect(shape.getPosition() + move, shape.getSize());
}

const sf::FloatRect Tile::getGlobalBounds() const
{
	return shape.getGlobalBounds();
}

const bool Tile::intersects(const sf::FloatRect bounds) const
{
	return shape.getGlobalBounds().intersects(bounds);
}

void Tile::render(sf::RenderTarget* target)
{
	target->draw(shape);
	if (hitbox)
		hitbox->render(target);
}