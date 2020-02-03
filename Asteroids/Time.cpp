#include "Time.h"

float Time::previousTime;
float Time::currentTime;
float Time::deltaTime;

void Time::CalculateDeltaTime()
{
	previousTime = currentTime;
	currentTime = getTickCount();

	deltaTime = currentTime - previousTime;

	deltaTime /= 1000.0f;
}