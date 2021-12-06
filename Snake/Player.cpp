#include "Player.h"

Player::Player(sf::Vector2f startingPosition, float segmentSize, uint8_t initialLength)
	: segmentSize(segmentSize)
{
	headColor = sf::Color::Magenta;
	bodyColor = sf::Color::Red;

	movementDirection = Direction::N;

	initializeBody(startingPosition, initialLength);
}

void Player::setMovingDirection(Direction newDirection)
{
	movementDirection = newDirection;
}

void Player::grow()
{
	sf::Vector2f tailPosition = body.back()->getPosition();
	body.push_back(new Tile(tailPosition.x, tailPosition.y + segmentSize, segmentSize, segmentSize, bodyColor));
}

sf::FloatRect Player::getNextHeadPosition()
{
	auto currentHeadPosition = body[0]->getPosition();
	switch (movementDirection)
	{
	case Direction::N:
		nextHeadPosition = sf::Vector2f(currentHeadPosition.x, currentHeadPosition.y - segmentSize);
		break;
	case Direction::S:
		nextHeadPosition = sf::Vector2f(currentHeadPosition.x, currentHeadPosition.y + segmentSize);
		break;
	case Direction::E:
		nextHeadPosition = sf::Vector2f(currentHeadPosition.x + segmentSize, currentHeadPosition.y);
		break;
	case Direction::W:
		nextHeadPosition = sf::Vector2f(currentHeadPosition.x - segmentSize, currentHeadPosition.y);
		break;
	}

	return body[0]->getNextPosition(nextHeadPosition);
}

void Player::move()
{
	moveBody();

	// update the head position
	Tile* head = body[0];
	head->setPosition(nextHeadPosition.x, nextHeadPosition.y);
}

void Player::render(sf::RenderTarget* target)
{
	for (auto it = body.rbegin(); it != body.rend(); ++it)
	{
		(*it)->render(target);
	}
}

void Player::initializeBody(sf::Vector2f startingPosition, uint8_t initialLength)
{
	body.push_back(new Tile(startingPosition.x, startingPosition.y, segmentSize, segmentSize, headColor));
	for (int i = 1; i < initialLength; i++)
	{
		body.push_back(new Tile(startingPosition.x, startingPosition.y + segmentSize, segmentSize, segmentSize, bodyColor));
	}
}

void Player::moveBody()
{
	sf::Vector2f headPosition = body[0]->getPosition();
	// take the last segment and move it in front of the others (current head position), instead of moving all of them by one unit
	Tile* tail = *body.rbegin();
	tail->setPosition(headPosition.x, headPosition.y); // move the shape
	body.erase(body.end()-1);
	body.insert(body.begin() + 1, tail); // insert the object on the second position inside the vector

}
