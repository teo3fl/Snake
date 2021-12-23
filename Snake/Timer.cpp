#include "stdafx.h"
#include "Timer.h"

Timer::Timer(float duration)
{
	elapsedTime = 0;
	maxTime = duration;
}

void Timer::update(const float& dt)
{
	elapsedTime += dt;
}

bool Timer::reachedEnd()
{
	return elapsedTime>=maxTime;
}

void Timer::reset()
{
	elapsedTime = 0;
}

uint8_t Timer::getRemainingSeconds()
{
	if (elapsedTime >= maxTime)
		return 0;

	return maxTime - elapsedTime;
}
