#pragma once

#include "Button.h"
#include "Scene.h"

#include <stack>

class MenuScene : public Scene
{
public:
	MenuScene(sf::RenderWindow* window, std::stack<Scene*>* scenes);
	virtual ~MenuScene();

	void update(const float& dt) override;
	void render(sf::RenderTarget* target = nullptr) override;

private:
	//Functions
	void initializeButtons();
	void initializeKeybinds() override;
	void initializeFont();
	void initializeText();

	void updateInput(const float& dt) override;
	void updateMousePosition();
	void updateButtons();

	void renderButtons(sf::RenderTarget& target);

private:
	sf::Font font;
	std::stack<Scene*>* scenes;
	std::map<std::string, Button*> buttons;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
};

