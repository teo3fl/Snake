#include "Hitbox.h"

Hitbox::Hitbox(float x, float y, float width, float height)
{
	hitbox.setPosition(x, y);
	hitbox.setSize(sf::Vector2f(width, height));
	hitbox.setFillColor(sf::Color::Transparent);
	/*m_hitbox.setOutlineThickness(1.f);
	m_hitbox.setOutlineColor(sf::Color::Green);*/
}

Hitbox::~Hitbox()
{
}

bool Hitbox::intersects(const sf::FloatRect& frect)
{
	return hitbox.getGlobalBounds().intersects(frect);
}

const sf::Vector2f& Hitbox::getPosition() const
{
	return hitbox.getPosition();
}

const sf::FloatRect Hitbox::getGlobalBounds() const
{
	return hitbox.getGlobalBounds();
}

const sf::FloatRect& Hitbox::getNextPosition(const sf::Vector2f& velocity)
{
	nextPosition.left = hitbox.getPosition().x + velocity.x;
	nextPosition.top = hitbox.getPosition().y + velocity.y;
	nextPosition.height = hitbox.getGlobalBounds().height;
	nextPosition.width = hitbox.getGlobalBounds().width;
	return nextPosition;
}

void Hitbox::setPosition(float x, float y)
{
	hitbox.setPosition(x, y);
}

void Hitbox::render(sf::RenderTarget* target)
{
	target->draw(hitbox);
}
