#include "Game.h"
#include "MenuScene.h"

Game::Game()
{
	initialize();
}

void Game::initialize()
{
	window = new sf::RenderWindow(sf::VideoMode(1000, 600), "Snake");
	deltaTime = 0.f;

	scenes.push(new MenuScene(window,&scenes));
}

Game* Game::getInstance()
{
	static Game* instance;

	if (!instance)
	{
		instance = new Game();
	}

	return instance;
}

void Game::render()
{
	window->clear();

	if (!scenes.empty())
	{
		scenes.top()->update(deltaTime);
		scenes.top()->render();
	}

	window->display();
}

void Game::update()
{
	updateSFMLEvents();

	if (!scenes.empty())
	{
		if (window->hasFocus())
		{
			scenes.top()->update(deltaTime);

			if (scenes.top()->getQuit())
			{
				delete scenes.top();
				scenes.pop();
			}
		}
	}
	else
	{
		// end application
		window->close();
	}
}

void Game::updateDt()
{
	deltaTime = clock.restart().asSeconds();
}

void Game::updateSFMLEvents()
{
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
	}
}

void Game::run()
{
	while (window->isOpen())
	{
		updateDt();
		update();
		render();
	}
}

void Game::start()
{
	Game::getInstance()->run();
}
