#pragma once
class Timer
{
public:
	Timer(float duration);

	void update(const float& dt);
	bool reachedEnd();
	void reset();

private:
	float elapsedTime;
	float maxTime;
};

