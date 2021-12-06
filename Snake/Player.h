#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "Map.h"

class Player
{
public:
	Player(sf::Vector2f startingPosition, float segmentSize, uint8_t initialLength = 2);

	void setMovingDirection(Direction newDirection);

	void grow();
	sf::FloatRect getNextHeadPosition();

	void move();
	void move(float jumpingPoint);
	void render(sf::RenderTarget* target);

private:
	void initializeBody(sf::Vector2f startingPosition, uint8_t initialLength);
	void moveBody();

private:
	std::vector<Tile*> body;
	sf::Vector2f nextHeadPosition;
	Direction movementDirection;
	Direction pendingMovementDirection;  

	float segmentSize;

	sf::Color headColor;
	sf::Color bodyColor;
};

