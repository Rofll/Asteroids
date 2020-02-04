#pragma once

#include "Framework.h"

class Time
{
public:
    static Time& instance()
    {
        static Time time;
        return time;
    }

	float deltaTime;
	void CalculateDeltaTime();

private:
    Time() {};
    ~Time() {};

    Time(Time const&) = delete;
    Time& operator= (Time const&) = delete;

    float previousTime;
    float currentTime;
};