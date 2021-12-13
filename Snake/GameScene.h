#pragma once

#include "FoodSpawner.h"
#include "Map.h"
#include "Player.h"
#include "Scene.h"

class GameScene : public Scene
{
public:
	GameScene(sf::RenderWindow* window, int level, const std::string& mapPath);
	virtual ~GameScene();

	void update(const float& dt) override;
	void render() override;

private:
	void initializeVariables(int level);
	void initializePlayer();
	void initializeMap(const std::string& path);
	void initializeText();

	void checkForGameOver();
	bool canMove();

	void updateInput(const float& dt) override;
	void updatePlayerMovement(const float& dt);
	void updateScoreText(int score);

	void renderBackground();
	virtual void renderEntities();

private:
	Player* player;
	//FoodSpawner* spawner;
	Map* map;
	//Tile* food;

	float movementSpan; // each MovementSpan seconds, the player's position will be updated
	const float baseMovementSpeed = 1; // the number of seconds between moves
	const float speedIncrease = 0.3f; // will increase the movementSpan depending on the difficulty level
	float elapsedTime; // counts the time that has passed since the last move

	int score;
	sf::Text scoreText;

	// game over
	float gameOver;
	const float gameOverScreenDuration = 2.f;
	float elapsedGameOverTime;
};

