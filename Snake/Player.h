#pragma once

#include "Tile.h"

enum class Direction { None, N, S, E, W };

class Player
{
public:
	Player(sf::Vector2f startingPosition, float segmentSize, uint8_t initialLength = 2);
	~Player();

	void setMovingDirection(Direction newDirection);

	void grow();
	const sf::FloatRect& getNextHeadPosition();
	const sf::FloatRect getHead();
	bool checkSelfCollision();

	const bool intersects(const sf::FloatRect bounds) const;

	void move();
	void move(Direction colliderOrientation, float jumpingPoint);
	void render(sf::RenderTarget* target);

private:
	void initializeBody(const sf::Vector2f& startingPosition, uint8_t initialLength);
	void moveBody();
	const sf::Color& getNextSegmentColor();

private:
	std::vector<Tile*> body;
	sf::Vector2f nextHeadPosition;
	Direction movementDirection;
	Direction pendingMovementDirection;  

	float segmentSize;

	sf::Color headColor;
	std::vector<sf::Color> bodyColors;
};

