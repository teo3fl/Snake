#include "stdafx.h"
#include "Map.h"

Map::Map(const std::string& path)
{
	upperLeftCorner.x = 80;
	upperLeftCorner.y = 180;
	boundColor = sf::Color(77, 77, 77);
	wallColor = sf::Color(0, 89, 232);
	loadFromFile(path);
}

Map::~Map()
{
	delete gen;

	for (size_t i = 0; i < walls.size(); i++)
	{
		delete walls[i];
	}

	for (auto& [_, tile] : bounds)
	{
		delete tile;
	}
}

void Map::update(const float& dt)
{
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

sf::Vector2f* Map::getStartingPosition()
{
	return playerStartingPosition;
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
	for (auto& [direction, bound] : bounds)
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

sf::Vector2f Map::getEmptySpace(Player* player)
{
	/*
	* will pick a random tile on the map (X)
	*
	* for radius in range (0, maximum size of the map)
	*	check the upper (U) and lower (D) edges of the square
	*	check the left (L) and right (R) edges of the square
	*	pick a random tile from the valid ones
	*
	*  _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	* |     |     |     |     |     |
	* |  U  |  U  |  U  |  U  |  U  |
	* |_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|
	* |     |     |     |     |     |
	* |  L  |     |     |     |  R  |
	* |_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|
	* |     |     |     |     |     |
	* |  L  |     |  X  |     |  R  |
	* |_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|
	* |     |     |     |     |     |
	* |  L  |     |     |     |  R  |
	* |_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|
	* |     |     |     |     |     |
	* |  D  |  D  |  D  |  D  |  D  |
	* |_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|
	*
	*
	*/

	uint8_t x = (*randomNumberWidth)(*gen);
	uint8_t y = (*randomNumberHeigth)(*gen);

	uint8_t maxSize = gridHeigth > gridWidth ? gridHeigth : gridWidth;


	std::vector<std::pair<int, int>> emptyTiles;

	// lambda

	auto getRect = [&](int x, int y)
	{
		int coordX = upperLeftCorner.x + x * tileSize;
		int coordY = upperLeftCorner.y + y * tileSize;
		return sf::FloatRect(coordX, coordY, tileSize, tileSize);
	};

	auto checkSide = [&](int start, int end, int constant, bool vertical)
	{
		for (int i = start; i < end + 1; ++i)
		{
			if (vertical)
			{
				if (logicalMap[constant][i] == MapTile::None && !player->intersects(getRect(constant, i)))
				{
					emptyTiles.emplace_back(constant, i);
				}
			}
			else
			{
				if (logicalMap[i][constant] == MapTile::None && !player->intersects(getRect(i, constant)))
				{
					emptyTiles.emplace_back(i, constant);
				}
			}
		}
	};


	// check first generated tile
	if (logicalMap[x][y] == MapTile::None && !player->intersects(getRect(x, y)))
		return sf::Vector2f(upperLeftCorner.x + x * tileSize, upperLeftCorner.y + y * tileSize);


	// else iterate through

	for (int R = 0; R < maxSize; ++R)
	{
		// upper edge (map[y - R][i] -> i = x - R, x + R)
		if (0 <= y - R)
		{
			int startPoint = x - R >= 0 ? x - R : 0;
			int endPoint = x + R < gridWidth ? x + R : gridWidth - 1;
			checkSide(startPoint, endPoint, y - R, false);
		}

		// lower edge (map[y + R][i] -> i = x - R, x + R)
		if (y + R < gridHeigth)
		{
			int startPoint = x - R >= 0 ? x - R : 0;
			int endPoint = x + R < gridWidth ? x + R : gridWidth - 1;
			checkSide(startPoint, endPoint, y + R, false);
		}

		// left edge (map[i][x - R] -> i = y - R + 1, x + R - 1)
		if (0 <= x - R)
		{
			int startPoint = y - R + 1 >= 0 ? y - R + 1 : 0;
			int endPoint = y + R - 1 < gridHeigth ? y + R - 1 : gridHeigth - 1;
			checkSide(startPoint, endPoint, x - R, true);
		}

		// right edge (map[i][x + R] -> i = y - R + 1, x + R - 1)
		if (x + R < gridWidth)
		{
			int startPoint = y - R + 1 >= 0 ? y - R + 1 : 0;
			int endPoint = y + R - 1 < gridHeigth ? y + R - 1 : gridHeigth - 1;
			checkSide(startPoint, endPoint, x + R, true);
		}

		if (emptyTiles.size() > 0)
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dist(0, emptyTiles.size() - 1);

			auto& [gridX, gridY] = emptyTiles[dist(gen)];
			return sf::Vector2f(upperLeftCorner.x + gridX * tileSize, upperLeftCorner.y + gridY * tileSize);
		}
	}

	return sf::Vector2f(-1, -1);
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
	* playerX playerY
	* x y width height
	* ...
	*/

	const uint16_t borderX = upperLeftCorner.x;
	const uint16_t borderY = upperLeftCorner.y;

	std::ifstream in(path);
	if (in.is_open())
	{
		// initialize dimensions
		in >> gridWidth >> gridHeigth;
		if (0 > gridWidth || gridWidth > maxWidth ||
			0 > gridHeigth || gridHeigth > maxHeigth)
		{
			throw std::runtime_error("ERROR: map width cannot be higher than " + std::to_string(maxWidth) + " and map heigth cannot be higher than " + std::to_string(maxHeigth) + ", or lower than 1");
		}

		// player starting point
		int playerX, playerY;
		in >> playerX >> playerY;
		bool spawnedInsideMap = 0 <= playerX && playerX <= gridWidth && 0 <= playerY && playerY <= gridHeigth;
		if (!spawnedInsideMap)
		{
			throw std::runtime_error("ERROR: player starting point cannot be outside the map bounds");
		}
		playerStartingPosition = new sf::Vector2f(
			upperLeftCorner.x + playerX * tileSize, 
			upperLeftCorner.y + playerY * tileSize
		);

		// random & logical map

		gen = new std::mt19937(rd());
		randomNumberWidth = new std::uniform_int_distribution(0, gridWidth - 1);
		randomNumberHeigth = new std::uniform_int_distribution(0, gridHeigth - 1);

		initializeLogicalMap(gridWidth, gridHeigth);

		// create bounds

		lowerRightCorner.x = upperLeftCorner.x + tileSize * gridWidth;
		lowerRightCorner.y = upperLeftCorner.y + tileSize * gridHeigth;

		bounds[Direction::N] = new Tile(borderX - tileSize, borderY - tileSize, (gridWidth + 2) * tileSize, tileSize, boundColor);
		bounds[Direction::S] = new Tile(borderX - tileSize, borderY + tileSize * gridHeigth, (gridWidth + 2) * tileSize, tileSize, boundColor);
		bounds[Direction::E] = new Tile(borderX + gridWidth * tileSize, borderY, tileSize, tileSize * gridHeigth, boundColor);
		bounds[Direction::W] = new Tile(borderX - tileSize, borderY, tileSize, tileSize * gridHeigth, boundColor);

		while (!in.eof())
		{
			// create wall
			int gridX;
			int gridY;
			int widthUnits;
			int heigthUnits;

			in >> gridX >> gridY >> widthUnits >> heigthUnits;

			walls.push_back(new Tile(borderX + gridX * tileSize, borderY + gridY * tileSize, widthUnits * tileSize, heigthUnits * tileSize, wallColor));

			// mark the changes inside the logical map
			insertWallInLogicalMap(gridX, gridY, widthUnits, heigthUnits);
		}
		in.close();
	}
	else
	{
		throw std::runtime_error("ERROR: map could not be loaded from path: " + path);
	}

}

void Map::initializeLogicalMap(uint8_t width, uint8_t heigth)
{
	for (int i = 0; i < width; ++i)
	{
		logicalMap.emplace_back();
		logicalMap[i].insert(logicalMap[i].begin(), heigth, MapTile::None);
	}
}

void Map::insertWallInLogicalMap(uint8_t x, uint8_t y, uint8_t width, uint8_t heigth)
{
	for (uint16_t i = x; i < x + width; ++i)
		for (uint16_t j = y; j < y + heigth; ++j)
			logicalMap[i][j] = MapTile::Wall;
}
