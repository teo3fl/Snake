#pragma once
#include "Scene.h"

class Game
{
public:
	static void start();
	static void close();

private:
	Game();

	void initialize();

	static Game* getInstance();

	void render();
	void update();

	void updateDt();
	void updateSFMLEvents();

	void run();

private:
	sf::RenderWindow* window;
	sf::Event event;

	sf::Clock clock;
	float deltaTime;

	std::stack<Scene*> scenes;

	std::map<std::string, int> supportedKeys;
};

