#include "stdafx.h"
#include "SpecialFood.h"

SpecialFood::SpecialFood(float x, float y, float width, float heigth, sf::Color color, float lifeSpan) 
	: Tile(x,y,width,heigth,color)
{
	timer = new Timer(lifeSpan);
}

void SpecialFood::update(const float& dt)
{
	timer->update(dt);
}

bool SpecialFood::reachedLifespanEnd()
{
	return timer->reachedEnd();
}

uint8_t SpecialFood::getRemainingSeconds()
{
	return timer->getRemainingSeconds();
}
