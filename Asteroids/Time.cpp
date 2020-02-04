#include "Time.h"

void Time::CalculateDeltaTime()
{
	previousTime = currentTime;
	currentTime = getTickCount();

	deltaTime = currentTime - previousTime;

	deltaTime /= 1000.0f;
}