#include "GameScene.h"

GameScene::GameScene(sf::RenderWindow* window, int level, const std::string& mapPath) : Scene(window)
{
	initializeVariables(level);
	initializeMap(mapPath);
	initializePlayer();
	initializeFont();
	initializeText();
}

GameScene::~GameScene()
{
}

void GameScene::update(const float& dt)
{
	updateKeyTime(dt);
	updateInput(dt);
	updatePlayerMovement(dt);
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
	/*spawner = NULL;
	food = NULL;*/
}

void GameScene::initializePlayer()
{
	player = new Player(sf::Vector2f(200, 200), map->getTileSize(), 3);
}

void GameScene::initializeMap(const std::string& path)
{
	map = new Map(path);
}

void GameScene::initializeText()
{
	updateScoreText(0);
	setText(scoreText, font, sf::Color::White, 30, sf::Vector2f(30.f, 30.f), 0.5f);

	text.push_back(scoreText);
}

void GameScene::checkForGameOver()
{

}

bool GameScene::canMove()
{
	return elapsedTime >= movementSpan;
}

void GameScene::updateInput(const float& dt)
{
}

void GameScene::updatePlayerMovement(const float& dt)
{
	elapsedTime += dt;
	if (canMove())
	{
		// check bounds collisions
		if (map->checkBoundCollision(player->getNextHeadPosition()))
		{
			// jump to the other side of the map
		}
		else
		{
			player->move();
		}
		elapsedTime = 0;
	}
}

void GameScene::updateScoreText(int score)
{
	scoreText.setString("Score: " + score);
}

void GameScene::renderBackground()
{
	renderText();
	map->render(window);
}

void GameScene::renderEntities()
{
	player->render(window);
	//food->render(window);
}
