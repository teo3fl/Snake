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
}

void GameScene::render()
{
	renderBackground();
	//renderEntities();
}

void GameScene::initializeVariables(int level)
{
	movementSpan = baseMovementSpeed + level * speedIncrease;
	elapsedTime = 0;
	score = 0;
	/*player = NULL;
	spawner = NULL;
	food = NULL;*/
}

void GameScene::initializePlayer()
{
	//player = new Player(map->getStartingPosition());
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
	return false;
}

void GameScene::updateInput(const float& dt)
{
}

void GameScene::updatePlayerMovement(const float& dt)
{
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
	//player->render(window);
	//food->Render(window);
}
