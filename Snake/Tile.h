#pragma once

#include "SFML/Graphics.hpp"

class Tile
{
public:
	Tile(float x, float y, float width, float heigth, sf::Color color);

	sf::Vector2f getPosition();
	void setPosition(int x, int y);

	const sf::RectangleShape& getShape();
	const sf::FloatRect getGlobalBounds() const;
	const bool intersects(const sf::FloatRect bounds) const;

	void render(sf::RenderTarget* target);

private:
	sf::RectangleShape shape;

	float width;
	float heigth;
};

