#pragma once

#include "SFML/Graphics.hpp"

#include "Hitbox.h"

class Tile
{
public:
	Tile(float x, float y, float width, float heigth, sf::Color color);

	void SetTexture(const sf::Texture& texture);
	void setPosition(int x, int y);
	void createHitbox();

	const sf::FloatRect GetGlobalBounds() const;
	const bool Intersects(const sf::FloatRect bounds) const;

	void Render(sf::RenderTarget* target);

private:
	sf::RectangleShape shape;
	Hitbox* hitbox;

	float width;
	float heigth;
};

