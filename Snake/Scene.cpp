#include "Scene.h"

Scene::Scene(sf::RenderWindow* window)
{
	this->window = window;
	quit = false;

	keyTime = 0.f;
	keytimeMax = 20.f;
}

Scene::~Scene()
{

}

void Scene::setText(sf::Text& text, const sf::Font& font, const sf::Color& fillColor, uint16_t size, const sf::Vector2f& position, float thickness)
{
	text.setFillColor(fillColor);
	text.setFont(font);
	text.setCharacterSize(size);
	text.setPosition(position);
	text.setOutlineThickness(thickness);
	text.setOutlineColor(fillColor);
}

void Scene::setText(sf::Text& text, const sf::Font& font, const sf::Color& fillColor, uint16_t size, float thickness)
{
	text.setFillColor(fillColor);
	text.setFont(font);
	text.setCharacterSize(size);
	text.setOutlineThickness(thickness);
	text.setOutlineColor(fillColor);
}

void Scene::checkForQuit()
{
	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Escape)) && getKeyTime())
	{
		quit = true;
	}
}

void Scene::updateKeyTime(const float& dt)
{
	if (keyTime < keytimeMax)
		keyTime += 100.f * dt;
}

void Scene::renderText(sf::RenderTarget* target)
{
	for (auto it = text.begin(); it != text.end(); it++)
	{
		target->draw(*it);
	}
}

const bool& Scene::getQuit() const
{
	return quit;
}

const bool Scene::getKeyTime()
{
	if (keyTime >= keytimeMax)
	{
		keyTime = 0.f;
		return true;
	}

	return false;
}
