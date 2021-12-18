#include "stdafx.h"
#include "Button.h"

Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string buttonText, uint8_t characterSize,
	sf::Color textColor, sf::Color buttonColor)
{
	pressed = false;

	shape.setPosition(sf::Vector2f(x, y));
	shape.setSize(sf::Vector2f(width, height));
	shape.setFillColor(buttonColor);

	font = font;
	text.setFont(*font);
	text.setString(buttonText);
	text.setFillColor(textColor);
	text.setCharacterSize(characterSize);
	text.setPosition(
		shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) - text.getGlobalBounds().width / 2.f,
		shape.getPosition().y
	);
}

Button::~Button()
{

}

bool Button::isPressed() const
{
	return pressed;
}

void Button::reset()
{
	pressed = false;
}

void Button::update(const sf::Vector2i& mousePos)
{
	if (shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			pressed = true;
		}
	}
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(shape);
	target->draw(text);
}