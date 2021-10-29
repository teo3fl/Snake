#pragma once

#include "SFML/Graphics.hpp"

#include <string>
#include <cstdint>


class Button
{
public:
	Button(float x, float y, float width, float height,
		sf::Font* font, std::string text, uint8_t characterSize,
		sf::Color textColor, sf::Color buttonColor);
	~Button();

	bool isPressed() const;
	void reset();

	//Functions
	void update(const sf::Vector2i& mousePos);
	void render(sf::RenderTarget* target);

private:
	bool pressed : 1;

	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	sf::Color color;
};