#include "stdafx.h"
#include "SpecialFood.h"

SpecialFood::SpecialFood(float x, float y, float width, float heigth, sf::Color color, float lifeSpan) 
	: Tile(x,y,width,heigth,color)
{
	this->lifeSpan = lifeSpan;
	elapsedTime = 0;
}

void SpecialFood::update(const float& dt)
{
	elapsedTime += dt;
}

bool SpecialFood::reachedLifespanEnd()
{
	return elapsedTime >= lifeSpan;
}
