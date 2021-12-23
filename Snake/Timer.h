#pragma once
class Timer
{
public:
	Timer(float duration);

	void update(const float& dt);
	bool reachedEnd();
	void reset();
	uint8_t getRemainingSeconds();

private:
	float elapsedTime;
	float maxTime;
};

