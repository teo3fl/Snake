#pragma once

#include "Button.h"
#include "Scene.h"

class MenuScene : public Scene
{
public:
	MenuScene(sf::RenderWindow* window, std::stack<Scene*>* scenes);
	virtual ~MenuScene();

	void update(const float& dt) override;
	void render() override;

private:
	void initializeButtons();
	void initializeText();

	void updateInput(const float& dt) override;
	void updateMousePosition();
	void updateButtons();

	void renderButtons();

private:
	std::stack<Scene*>* scenes;
	std::map<std::string, Button*> buttons;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;

	const std::string mapPath = "../External/Resources/Maps/";
};

