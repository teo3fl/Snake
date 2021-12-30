#include "stdafx.h"
#include "Player.h"

Player::Player(sf::Vector2f startingPosition, float segmentSize, uint8_t initialLength)
	: segmentSize(segmentSize)
{
	headColor = sf::Color(123, 0, 255);
	bodyColors.push_back(sf::Color(53, 0, 176));
	bodyColors.push_back(sf::Color(41, 0, 138));
	bodyColors.push_back(sf::Color(31, 0, 105));

	movementDirection = Direction::N;
	pendingMovementDirection = Direction::N;

	surplusSegments = 0;

	initializeBody(startingPosition, initialLength);
}

Player::~Player()
{
	for (size_t i = 0; i < body.size(); i++)
	{
		delete body[i];
	}
}

void Player::setMovingDirection(Direction newDirection)
{
	/*
	* The player shouldn't be allowed to go back on themselves (i.e. switch from
	* North to South, or East to West). The corresponding values of the Direction
	* enum are:
	*
	* N = 1
	* S = 2
	* E = 3
	* W = 4
	*
	* From that, N + S = 3 and E + W = 7. No other combinations can result in hese
	* values, therefore they can be used in order to validate the switch.
	*
	* The player can change the direction multiple times during the movement span,
	* therefore might be able to go back on themselves. In order to prevent this
	* from happening, pendingMovementDirection will store the movement direction
	* that was chosed by the player, then movementDirection will take the same
	* value only when actually moving.
	*/

	bool canChangeDirection = !((int)newDirection + (int)movementDirection == 3 || (int)newDirection + (int)movementDirection == 7);

	if (canChangeDirection && pendingMovementDirection != newDirection)
	{
		pendingMovementDirection = newDirection;
	}
}

void Player::grow(int incr)
{
	sf::Vector2f tailPosition = body.back()->getPosition();
	for (size_t i = 0; i < incr; i++)
	{
		body.push_back(new Tile(tailPosition.x, tailPosition.y, segmentSize, segmentSize, getNextSegmentColor()));
	}

	surplusSegments += incr;
}

const sf::FloatRect& Player::getNextHeadPosition()
{
	auto currentHeadPosition = body[0]->getPosition();
	switch (pendingMovementDirection)
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

	return sf::FloatRect(nextHeadPosition, body[0]->getShape().getSize());
}

const sf::FloatRect Player::getHead()
{
	return body[0]->getGlobalBounds();
}

bool Player::checkSelfCollision()
{
	Tile* head = body[0];

	for (int i = 1; i < body.size(); ++i)
	{
		if (head->intersects(body[i]->getGlobalBounds()))
			return true;
	}

	return false;
}

const bool Player::intersects(const sf::FloatRect bounds) const
{
	for (auto& segment : body)
	{
		if (segment->intersects(bounds))
			return true;
	}

	return false;
}

void Player::move()
{
	movementDirection = pendingMovementDirection;
	moveBody();

	// update the head position
	Tile* head = body[0];
	head->setPosition(nextHeadPosition.x, nextHeadPosition.y);
}

void Player::move(Direction colliderOrientation, float jumpingPoint)
{
	movementDirection = pendingMovementDirection;
	moveBody();

	// update the head position
	Tile* head = body[0];
	switch (colliderOrientation)
	{
	case Direction::N:
		head->setPosition(nextHeadPosition.x, jumpingPoint - segmentSize);
		break;
	case Direction::S:
		head->setPosition(nextHeadPosition.x, jumpingPoint);
		break;
	case Direction::E:
		head->setPosition(jumpingPoint, nextHeadPosition.y);
		break;
	case Direction::W:
		head->setPosition(jumpingPoint - segmentSize, nextHeadPosition.y);
		break;
	}
}

void Player::render(sf::RenderTarget* target)
{
	for (auto it = body.rbegin(); it != body.rend(); ++it)
	{
		(*it)->render(target);
	}
}

void Player::initializeBody(const sf::Vector2f& startingPosition, uint8_t initialLength)
{
	body.push_back(new Tile(startingPosition.x, startingPosition.y, segmentSize, segmentSize, headColor));
	for (int i = 1; i < initialLength; i++)
	{
		body.push_back(new Tile(startingPosition.x, startingPosition.y + segmentSize, segmentSize, segmentSize, getNextSegmentColor()));
	}
}

void Player::moveBody()
{
	for (size_t i = body.size() - 1 - surplusSegments; i > 0; i--)
	{
		auto nextTilePosition = body[i - 1]->getPosition();
		body[i]->setPosition(nextTilePosition.x, nextTilePosition.y);
	}

	if (surplusSegments > 0)
		--surplusSegments;
}

const sf::Color& Player::getNextSegmentColor()
{
	return bodyColors[(body.size() - 1) / 2 % bodyColors.size()];
}
