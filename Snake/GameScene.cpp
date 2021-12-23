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
	delete specialFoodTimer;
	delete movementTimer;
	delete gameOverTimer;

	delete player;
	delete map;

	delete food;
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
		updateSpecialFood(dt);
		checkFoodCollision();
	}
	else
	{
		if (!savedScore)
		{
			saveHighScore();
			savedScore = true;
		}

		// freeze screen
		gameOverTimer->update(dt);
		if (gameOverTimer->reachedEnd())
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
	this->level = level;
	movementSpan = baseMovementSpeed + level * speedIncrease;
	movementTimer = new Timer(movementSpan);
	score = 0;
	player = NULL;
	food = NULL;
	gameOverTimer = new Timer(gameOverScreenDuration);
	gameOver = false;
	loadHighScores();
	savedScore = false;
}

void GameScene::initializePlayer()
{
	player = new Player(*map->getStartingPosition(), map->getTileSize(), 3);
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

	highScoreText = new sf::Text();
	setText(*highScoreText, font, sf::Color::White, 30, sf::Vector2f(300.f, 30.f), 0.5f);
	highScoreText->setString("Highscore: " + std::to_string(highScores[level]));
	text.push_back(highScoreText);

	setText(specialFoodRemainingSeconds, font, sf::Color::White, 30, sf::Vector2f(30.f, 80.f), 0.5f);
}

void GameScene::initializeFood()
{
	float tileSize = map->getTileSize();
	sf::Vector2f position = map->getEmptySpace(player);
	food = new Tile(position.x, position.y, tileSize, tileSize, sf::Color::Cyan);

	specialFoodTimer = new Timer(specialFoodSpawnRate);
}

void GameScene::loadHighScores()
{
	for (std::ifstream in(highScoresFilePath); in.is_open() && !in.eof();)
	{
		int highScore;
		in >> highScore;
		highScores.push_back(highScore);
	}

	for (int i = highScores.size(); i <= level; ++i)
		highScores.push_back(0);
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
	return movementTimer->reachedEnd();
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

	if (specialFood && player->getHead().intersects(specialFood->getGlobalBounds()))
	{
		player->grow(3);
		score += 3;
		updateScoreText();
		delete specialFood;
		specialFood = nullptr;
	}
}

void GameScene::saveHighScore()
{
	if (highScores[level] >= score)
		return;

	highScores[level] = score;

	std::ofstream ofs(highScoresFilePath, std::ofstream::out);

	for (size_t i = 0; i < highScores.size(); i++)
	{
		ofs << highScores[i] << std::endl;
	}

	ofs.close();
}

void GameScene::updateSpecialFood(const float& dt)
{
	if (specialFood)
	{
		specialFood->update(dt);
		specialFoodRemainingSeconds.setString(std::to_string(specialFood->getRemainingSeconds()));
		if (specialFood->reachedLifespanEnd())
		{
			delete specialFood;
			specialFood = nullptr;
		}
	}

	specialFoodTimer->update(dt);
	if (specialFoodTimer->reachedEnd())
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(1, 100);

		int generatedNumber = dist(gen);

		if (generatedNumber < specialFoodSpawnChance)
		{
			if (specialFood)
			{
				delete specialFood;
				specialFood = nullptr;
			}

			auto spawnLocation = map->getEmptySpace(player);
			float tileSize = map->getTileSize();
			specialFood = new SpecialFood(spawnLocation.x, spawnLocation.y, tileSize, tileSize, sf::Color::Red, specialFoodLifeSpan);
		}

		specialFoodTimer->reset();
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
	movementTimer->update(dt);
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
		movementTimer->reset();
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
	if (specialFood)
	{
		specialFood->render(window);
		window->draw(specialFoodRemainingSeconds);
	}
}
