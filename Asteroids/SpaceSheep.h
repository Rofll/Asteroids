#pragma once

#include "Actor.h"
#include "RenderComponent.h"

class SpaceSheep : public Actor
{
public:
	SpaceSheep();
	SpaceSheep(const char* spritePass, int xPosition, int yPosition);
	~SpaceSheep();
	
	
	void Tick() override;

private:
	const char* spritePass;

	float minSpeed = 0;
	float maxSpeed = 100;

	float acceleration = 100;
	float deaceleration = 1;

	float currentSpeedX;
	float currentSpeedY;

	RenderComponent* renderer;
};

