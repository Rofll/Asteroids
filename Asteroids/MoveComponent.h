#pragma once

#include "BaseComponent.h"

class MoveComponent : public BaseComponent
{
public:
	MoveComponent();
	MoveComponent(int* xPosition, int* yPosition, float* minSpeed,
		float* maxSpeed, float* acceleration, float* deacceleration);
	~MoveComponent();

	void MoveUp();
	void MoveDown();
	void MoveRight();
	void MoveLeft();

	void StopMoveUp();
	void StopMoveDown();
	void StopMoveRight();
	void StopMoveLeft();

	bool isMovingUp;
	bool isMovingDown;
	bool isMovingRight;
	bool isMovingLeft;

	void Tick() override;

private:
	int* xPosition;
	int* yPosition;

	float* minSpeed;
	float* maxSpeed;

	float* acceleration;
	float* deacceleration;

	int directionX;
	int directionY;

	int previousDirectionX;
	int previousDirectionY;

	float currentSpeedX;
	float currentSpeedY;
};

