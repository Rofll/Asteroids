#pragma once

#include "Framework.h"

class Time
{
public:
	static float deltaTime;
	static void CalculateDeltaTime();

private:
	static float previousTime;
	static float currentTime;
};

