#include "stdafx.h"
#include "InfoScene.h"

InfoScene::InfoScene(sf::RenderWindow* window) : Scene(window)
{
	initializeFont();
	initializeText();
}

void InfoScene::update(const float& dt)
{
	updateInput(dt);
}

void InfoScene::render()
{
	renderText();
}

void InfoScene::updateInput(const float& dt)
{
	updateKeyTime(dt);
	checkForQuit();
}

void InfoScene::initializeText()
{
	sf::Text* titleText = new sf::Text();
	titleText->setString("SNAKE");
	setText(*titleText, font, sf::Color::White, 30, sf::Vector2f(30.f, 30.f), 0.5f);

	text.push_back(titleText);

	std::stringstream ss;
	ss << "Maps are found in the Resources/Maps folder.\n";
	ss << "In order to add a map, create a mapX.ini file, where X is the level number.\n";
	ss << "The file format is as follows (everything in grid values, not pixels):\n\n";
	ss << "mapWidth mapHeigth\n";
	ss << "playerX playerY\n";
	ss << "upperLeftCornerX upperLeftCornerY wallWidth wallHeigth\n";
	ss << "upperLeftCornerX upperLeftCornerY wallWidth wallHeigth\n";
	ss << "and so on, add as many walls as you want\n\n";
	ss << "There can be up to 48 maps.\n\n\n";
	ss << "Press ESC to go back";

	sf::Text* keybindsText = new sf::Text();
	keybindsText->setString(ss.str());
	setText(*keybindsText, font, sf::Color::White, 20, sf::Vector2f(20.f, 100.f));

	text.push_back(keybindsText);

}
