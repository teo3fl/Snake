#include "Map.h"

#include <fstream>

Map::Map(const std::string& path)
{
	upperLeftCorner.x = 80;
	upperLeftCorner.y = 180;
	boundColor = sf::Color::Green;
	wallColor = sf::Color::Blue;
	loadFromFile(path);
}

void Map::render(sf::RenderTarget* target)
{
	for (auto wall : walls)
	{
		wall->render(target);
	}

	for (auto pair : bounds)
	{
		pair.second->render(target);
	}
}

float Map::getOppositeBoundCoordinate(Direction collidingBound)
{
	switch (collidingBound)
	{
	case Direction::N:
		return lowerRightCorner.y;
	case Direction::S:
		return upperLeftCorner.y;
	case Direction::E:
		return upperLeftCorner.x;
	case Direction::W:
		return lowerRightCorner.x;
	}
}

Direction Map::checkBoundCollision(sf::FloatRect playerHead)
{
	for (auto& [direction,bound] : bounds)
	{
		if (bound->intersects(playerHead))
			return direction;
	}

	return Direction::None;
}

bool Map::checkWallCollision(sf::FloatRect playerHead)
{
	for (auto wall : walls)
	{
		if (wall->intersects(playerHead))
			return true;
	}

	return false;
}

float Map::getTileSize()
{
	return tileSize;
}

void Map::loadFromFile(const std::string& path)
{
	/*
	* File structure (in tiles):
	*
	* mapWidth mapHeight
	* x y width height
	* ...
	*/

	const uint16_t borderX = upperLeftCorner.x;
	const uint16_t borderY = upperLeftCorner.y;

	std::ifstream in(path);
	if (in.is_open())
	{
		int width;
		int heigth;
		in >> width >> heigth;

		lowerRightCorner.x = upperLeftCorner.x + tileSize * width;
		lowerRightCorner.y = upperLeftCorner.y + tileSize * heigth;

		bounds[Direction::N] = new Tile(borderX - tileSize, borderY - tileSize, (width + 2) * tileSize , tileSize, boundColor);
		bounds[Direction::S] = new Tile(borderX - tileSize, borderY + tileSize * width, (width + 2) * tileSize, tileSize, boundColor);
		bounds[Direction::E] = new Tile(borderX + width * tileSize, borderY, tileSize, tileSize * width, boundColor);
		bounds[Direction::W] = new Tile(borderX - tileSize, borderY, tileSize, tileSize * width, boundColor);

		while (!in.eof())
		{
			// create wall
			int gridX;
			int gridY;
			int widthUnits;
			int heigthUnits;

			in >> gridX >> gridY >> widthUnits >> heigthUnits;

			walls.push_back(new Tile(borderX + gridX * tileSize, borderY + gridY * tileSize, widthUnits * tileSize, heigthUnits * tileSize, wallColor));
		}
	}
	else
	{
		throw path + "ERROR::MAP::COULD NOT LOAD FROM FILE::FILENAME: ";
	}

	in.close();

}
