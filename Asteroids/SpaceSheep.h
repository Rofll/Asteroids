#pragma once

#include "Actor.h"
#include "RenderComponent.h"
#include "MoveComponent.h"
#include "InputComponent.h"

class SpaceSheep
{
public:
	SpaceSheep();
	SpaceSheep(const char* spritePass);
	~SpaceSheep();
	
	
	//void Tick() override;

	MoveComponent* GetMoveComponent();

private:
	const char* spritePass;

	float minSpeed = 0;
	float maxSpeed = 100;

	float acceleration = 3;
	float deaceleration = 3;

	float currentSpeedX;
	float currentSpeedY;

	RenderComponent* renderer;
	MoveComponent* moveComponent;
	//InputComponent* inputComponent;
};

