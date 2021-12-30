#include "stdafx.h"
#include "MenuScene.h"

#include "GameScene.h"
#include "InfoScene.h"

MenuScene::MenuScene(sf::RenderWindow* window, std::stack<Scene*>* scenes)
	: Scene(window), scenes(scenes)
{
	initializeVariables();
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

void MenuScene::initializeVariables()
{
	auto fileCount = getDirectoryFileCount(resourcesPath + "Maps");
	mapCount = fileCount < maxMapCount ? fileCount : maxMapCount;
}

void MenuScene::initializeButtons()
{
	float offsetX = 350;
	float offsetY = 100;
	float padding = 30;

	int lineCapacity = 8;
	float buttonSize = 50;

	for (int i = 0; i < mapCount; ++i)
	{
		float x = offsetX + (buttonSize + padding) * (i % lineCapacity);
		float y = offsetY + (buttonSize + padding) * (i / lineCapacity);

		buttons["LVL" + std::to_string(i + 1)] = new Button(x, y, buttonSize, buttonSize,
			&font, std::to_string(i + 1), 30,
			sf::Color::White, sf::Color::Black);
	}

	buttons["CREATE_MAP"] = new Button(30, 350, 200, 80,
		&font, "HOW TO ADD\nA MAP", 30,
		sf::Color::White, sf::Color::Black);

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

	for (int i = 1; i < mapCount + 1; ++i)
	{
		Button* button = buttons["LVL" + std::to_string(i)];
		if (button->isPressed())
		{
			button->reset();
			auto path = resourcesPath + "Maps/map" + std::to_string(i) + ".ini";
			scenes->push(new GameScene(window, i, path));

			break;
		}
	}

	if (buttons["CREATE_MAP"]->isPressed())
	{
		buttons["CREATE_MAP"]->reset();
		scenes->push(new InfoScene(window));
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

std::size_t MenuScene::getDirectoryFileCount(std::filesystem::path path)
{
	return (std::size_t)std::distance(std::filesystem::directory_iterator{ path }, std::filesystem::directory_iterator{});
}

void MenuScene::render()
{
	renderText();
	renderButtons();
}