#pragma once

#include <string>

#include "Tile.h"

enum class Direction { None, N, S, E, W };

class Map
{
public:
	Map(const std::string& path);

	void update(const float& dt);
	void render(sf::RenderTarget* target);

	sf::Vector2f getStartingPosition();
	float getOppositeBoundCoordinate(Direction collidingBound); // when colliding with a certain bound, returns the X or Y (based on the direction) coordinate of the opposite bound
	Direction checkBoundCollision(sf::FloatRect playerHead);
	bool checkWallCollision(sf::FloatRect playerHead);

	float getTileSize();

private:
	void loadFromFile(const std::string& path);

private:
	std::vector<Tile*> walls;
	std::map<Direction,Tile*> bounds;

	sf::Color boundColor;
	sf::Color wallColor;

	const float tileSize = 30;
	sf::Vector2f upperLeftCorner;
	sf::Vector2f lowerRightCorner;
};

