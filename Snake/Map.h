#pragma once

#include <string>
#include <random>

#include "Tile.h"

enum class Direction { None, N, S, E, W };
enum class MapTile { None, Wall, Snake };

class Map
{
public:
	Map(const std::string& path);
	~Map();

	void update(const float& dt);
	void render(sf::RenderTarget* target);

	sf::Vector2f getStartingPosition();
	float getOppositeBoundCoordinate(Direction collidingBound); // when colliding with a certain bound, returns the X or Y (based on the direction) coordinate of the opposite bound
	Direction checkBoundCollision(sf::FloatRect playerHead);
	bool checkWallCollision(sf::FloatRect playerHead);
	sf::Vector2f getEmptySpace(/*Player* player*/);

	float getTileSize();

private:
	void loadFromFile(const std::string& path);
	void initializeLogicalMap(uint8_t width, uint8_t heigth);
	void insertWallInLogicalMap(uint8_t x, uint8_t y, uint8_t width, uint8_t heigth);

private:
	std::vector<Tile*> walls;
	std::map<Direction, Tile*> bounds;

	sf::Color boundColor;
	sf::Color wallColor;

	const float tileSize = 30;
	sf::Vector2f upperLeftCorner;
	sf::Vector2f lowerRightCorner;

	std::vector<std::vector<MapTile>> logicalMap;
	int gridWidth;
	int gridHeigth;

	// random
	std::random_device rd;
	std::mt19937* gen;
	std::uniform_int_distribution<int>* randomNumberWidth;
	std::uniform_int_distribution<int>* randomNumberHeigth;
};

