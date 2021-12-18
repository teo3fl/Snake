#include "MenuScene.h"

#include <sstream>
#include <string>

#include "GameScene.h"

MenuScene::MenuScene(sf::RenderWindow* window, std::stack<Scene*>* scenes)
	: Scene(window), scenes(scenes)
{
	initializeFont();
	initializeButtons();
	initializeText();
}

MenuScene::~MenuScene()
{
	auto it = buttons.begin();
	for (it = buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}
}

void MenuScene::initializeText()
{
	sf::Text* titleText = new sf::Text();
	titleText->setString("SNAKE");
	setText(*titleText, font, sf::Color::White, 30, sf::Vector2f(30.f, 30.f), 0.5f);

	text.push_back(titleText);

	std::stringstream ss;
	ss << "Keybinds:\n\n";
	ss << "WASD - move\n";
	ss << "ESC - back to menu / close\n";
	ss << "Mouse - press buttons";

	sf::Text* keybindsText = new sf::Text();
	keybindsText->setString(ss.str());
	setText(*keybindsText, font, sf::Color::White, 20, sf::Vector2f(10.f, 100.f));

	text.push_back(keybindsText);

	sf::Text* levelText = new sf::Text();
	levelText->setString("Levels:");
	setText(*levelText, font, sf::Color::White, 20, sf::Vector2f(620.f, 30.f));

	text.push_back(levelText);
}

void MenuScene::initializeButtons()
{
	float offsetX = 350;
	float offsetY = 100;
	float padding = 30;

	int lineCapacity = 8;
	float buttonSize = 50;

	for (int i = 0; i < 48; ++i)
	{
		float x = offsetX + (buttonSize + padding) * (i % lineCapacity);
		float y = offsetY + (buttonSize + padding) * (i / lineCapacity);

		buttons["LVL" + std::to_string(i + 1)] = new Button(x, y, buttonSize, buttonSize,
			&font, std::to_string(i + 1), 30,
			sf::Color::White, sf::Color::Black);
	}

	buttons["EXIT_STATE"] = new Button(20, 500, 100, 50,
		&font, "EXIT", 30,
		sf::Color::White, sf::Color::Black);
}

void MenuScene::updateInput(const float& dt)
{
	checkForQuit();
}

void MenuScene::updateMousePosition()
{
	mousePosScreen = sf::Mouse::getPosition();
	mousePosWindow = sf::Mouse::getPosition(*window);
}

void MenuScene::updateButtons()
{
	for (auto& it : buttons)
	{
		it.second->update(mousePosWindow);
	}

	for (int i = 0; i < 48; ++i)
	{
		Button* button = buttons["LVL" + std::to_string(i + 1)];
		if (button->isPressed())
		{
			button->reset();
			auto path = mapPath + "map" + std::to_string(i) + ".ini";
			scenes->push(new GameScene(window, i, path));

			break;
		}
	}

	if (buttons["EXIT_STATE"]->isPressed())
	{
		quit = true;
	}
}

void MenuScene::update(const float& dt)
{
	updateMousePosition();
	updateInput(dt);
	updateButtons();
}

void MenuScene::renderButtons()
{
	for (auto& it : this->buttons)
	{
		it.second->render(window);
	}
}

void MenuScene::render()
{
	renderText();
	renderButtons();
}