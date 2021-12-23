#pragma once

#include "Tile.h"
#include "Timer.h"

class SpecialFood : public Tile
{
public:
	SpecialFood(float x, float y, float width, float heigth, sf::Color color, float lifeSpan);
	void update(const float& dt);
	bool reachedLifespanEnd();
	uint8_t getRemainingSeconds();

private:
	Timer* timer;
};

