#pragma once

#include "Map.h"
#include "Scene.h"
#include "SpecialFood.h"
#include "Timer.h"

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
	void initializeFood();

	void checkForGameOver();
	bool canMove();
	void spawnFood();
	void checkFoodCollision();

	void updateSpecialFood(const float& dt);
	void updateInput(const float& dt) override;
	void updatePlayerMovement(const float& dt);
	void updateScoreText();

	void renderBackground();
	virtual void renderEntities();

private:
	Player* player;
	Map* map;

	// food
	Tile* food;
	SpecialFood* specialFood;
	const int specialFoodSpawnChance = 15; // 15% chance to spawn
	const float specialFoodSpawnRate = 30.f; // tries to spawn it every X seconds
	const float specialFoodLifeSpan = 10.f; // will destroy self after Y seconds
	Timer* specialFoodTimer;

	float movementSpan; // each MovementSpan seconds, the player's position will be updated
	const float baseMovementSpeed = 1; // the number of seconds between moves
	const float speedIncrease = 0.3f; // will increase the movementSpan depending on the difficulty level
	Timer* movementTimer;

	int score;
	sf::Text* scoreText;

	// game over
	float gameOver;
	const float gameOverScreenDuration = 2.5f;
	Timer* gameOverTimer;
};

