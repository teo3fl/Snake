#pragma once

#include <SFML/Graphics.hpp>

class Hitbox
{
public:
	Hitbox(float x, float y, float width, float height);

	~Hitbox();

	bool intersects(const sf::FloatRect& frect);

	//Accessors
	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
	const sf::FloatRect& getNextPosition(const sf::Vector2f& velocity);

	void setPosition(float x, float y);
	void render(sf::RenderTarget* target = nullptr);

private:
	sf::RectangleShape hitbox;
	sf::FloatRect nextPosition;
};

