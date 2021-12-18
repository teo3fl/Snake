#include "stdafx.h"
#include "GameScene.h"

GameScene::GameScene(sf::RenderWindow* window, int level, const std::string& mapPath) : Scene(window)
{
	initializeVariables(level);
	initializeMap(mapPath);
	initializePlayer();
	initializeFont();
	initializeText();
	initializeFood();
}

GameScene::~GameScene()
{
}

void GameScene::update(const float& dt)
{
	checkForGameOver();
	if (!gameOver)
	{
		// update input and visuals
		updateKeyTime(dt);
		updateInput(dt);
		updatePlayerMovement(dt);
		checkFoodCollision();
	}
	else
	{
		// freeze screen
		elapsedGameOverTime += dt;
		if (elapsedGameOverTime >= gameOverScreenDuration)
		{
			quit = true;
		}
	}
	checkForQuit();
}

void GameScene::render()
{
	renderBackground();
	renderEntities();
}

void GameScene::initializeVariables(int level)
{
	movementSpan = baseMovementSpeed + level * speedIncrease;
	elapsedTime = 0;
	score = 0;
	player = NULL;
	food = NULL;
	elapsedGameOverTime = 0;
}

void GameScene::initializePlayer()
{
	player = new Player(sf::Vector2f(200, 300), map->getTileSize(), 3);
}

void GameScene::initializeMap(const std::string& path)
{
	map = new Map(path);
}

void GameScene::initializeText()
{
	scoreText = new sf::Text();
	setText(*scoreText, font, sf::Color::White, 30, sf::Vector2f(30.f, 30.f), 0.5f);
	updateScoreText();

	text.push_back(scoreText);
}

void GameScene::initializeFood()
{
	float tileSize = map->getTileSize();
	sf::Vector2f position = map->getEmptySpace(player);
	food = new Tile(position.x, position.y, tileSize, tileSize, sf::Color::Cyan);
}

void GameScene::checkForGameOver()
{
	if (player->checkSelfCollision() || map->checkWallCollision(player->getHead()))
	{
		gameOver = true;
	}
}

bool GameScene::canMove()
{
	return elapsedTime >= movementSpan;
}

void GameScene::spawnFood()
{
	auto newPosition = map->getEmptySpace(player);
	if (newPosition.x >= 0)
	{
		food->setPosition(newPosition.x, newPosition.y);
	}
	else
	{
		delete food;
	}
}

void GameScene::checkFoodCollision()
{
	if (player->getHead().intersects(food->getGlobalBounds()))
	{
		player->grow();
		++score;
		updateScoreText();
		spawnFood();
	}
}

void GameScene::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		player->setMovingDirection(Direction::N);
		return;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		player->setMovingDirection(Direction::W);
		return;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		player->setMovingDirection(Direction::S);
		return;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		player->setMovingDirection(Direction::E);
		return;
	}
}

void GameScene::updatePlayerMovement(const float& dt)
{
	elapsedTime += dt;
	if (canMove())
	{
		// check bounds collisions
		auto collizionDirection = map->checkBoundCollision(player->getNextHeadPosition());
		if (collizionDirection == Direction::None)
		{
			player->move();
		}
		else
		{
			// jump to the other side of the map
			player->move(collizionDirection, map->getOppositeBoundCoordinate(collizionDirection));
		}
		elapsedTime = 0;
	}
}

void GameScene::updateScoreText()
{
	auto s = "Score: " + std::to_string(score);
	scoreText->setString(s);
}

void GameScene::renderBackground()
{
	renderText();
	map->render(window);
}

void GameScene::renderEntities()
{
	player->render(window);
	if (food)
		food->render(window);
}
