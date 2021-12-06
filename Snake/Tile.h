#pragma once

#include "SFML/Graphics.hpp"

#include "Hitbox.h"

class Tile
{
public:
	Tile(float x, float y, float width, float heigth, sf::Color color);

	sf::Vector2f getPosition();
	void setPosition(int x, int y);
	void createHitbox();

	sf::FloatRect getNextPosition(sf::Vector2f move);
	const sf::FloatRect getGlobalBounds() const;
	const bool intersects(const sf::FloatRect bounds) const;

	void render(sf::RenderTarget* target);

private:
	sf::RectangleShape shape;
	Hitbox* hitbox;

	float width;
	float heigth;
};

