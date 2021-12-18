#pragma once

#include "SFML/Graphics.hpp"

class Scene
{

public:
	Scene(sf::RenderWindow* window);
	virtual ~Scene();

	const bool& getQuit() const;

	virtual void update(const float& dt) = 0;
	virtual void render() = 0;

protected:
	virtual void initializeFont();
	void setText(sf::Text& text, const sf::Font& font, const sf::Color& fillColor, uint16_t size, const sf::Vector2f& position, float thickness = 0);
	void setText(sf::Text& text, const sf::Font& font, const sf::Color& fillColor, uint16_t size, float thickness = 0);
	
	const bool getKeyTime();

	virtual void checkForQuit();

	virtual void updateKeyTime(const float& dt);
	virtual void updateInput(const float& dt) = 0;

	void renderText();

protected:
	sf::RenderWindow* window;
	sf::Font font;

	std::vector<sf::Text*> text;

	bool quit : 1;

	float keyTime;
	float keytimeMax;
};