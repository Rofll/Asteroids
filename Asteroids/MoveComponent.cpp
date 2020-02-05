#include "MoveComponent.h"
#include <cmath>
#include <stdio.h>

MoveComponent::MoveComponent()
{
	directionX = 0;
	directionY = 0;

	currentSpeedX = 0;
	currentSpeedY = 0;
}

MoveComponent::MoveComponent(int* xPosition, int* yPosition, float* minSpeed,
	float* maxSpeed, float* acceleration, float* deacceleration)
{
	this->xPosition = xPosition;
	this->yPosition = yPosition;
	
	this->minSpeed = minSpeed;
	this->maxSpeed = maxSpeed;

	this->acceleration = acceleration;
	this->deacceleration = deacceleration;

	directionX = 0;
	directionY = 0;

	previousDirectionX = 0;
	previousDirectionY = 0;

	currentSpeedX = *minSpeed;
	currentSpeedY = *minSpeed;
}

MoveComponent::~MoveComponent()
{
	
}

void MoveComponent::Tick()
{

	if (isMovingUp || isMovingDown || isMovingRight || isMovingLeft)
	{
		if (isMovingUp)
		{
			currentSpeedY -= *acceleration * Time::instance().deltaTime;
		}

		if (isMovingDown)
		{
			currentSpeedY += *acceleration * Time::instance().deltaTime;
		}

		if (isMovingRight)
		{
			currentSpeedX += *acceleration * Time::instance().deltaTime;
		}

		if (isMovingLeft)
		{
			currentSpeedX -= *acceleration * Time::instance().deltaTime;
		}
	}

	else
	{
		if (currentSpeedX > 0)
		{
			currentSpeedX -= *deacceleration * Time::instance().deltaTime;
		}

		else if (currentSpeedX < 0)
		{
			currentSpeedX += *deacceleration * Time::instance().deltaTime;
		}

		if (currentSpeedY > 0)
		{
			currentSpeedY -= *deacceleration * Time::instance().deltaTime;
		}

		else if (currentSpeedY < 0)
		{
			currentSpeedY += *deacceleration * Time::instance().deltaTime;
		}
	}


	//if ((isMovingUp || isMovingDown || isMovingRight || isMovingLeft) && (previousDirectionX == directionX))
	//{
	//	currentSpeedX += *acceleration;//* Time::instance().deltaTime;
	//}

	//else if (currentSpeed > 0)
	//{
	//	currentSpeed -= *deacceleration; //* Time::instance().deltaTime;
	//}

	//if (currentSpeed < 0)
	//{
	//	currentSpeed = 0;

	//	previousDirectionX = 0;
	//	previousDirectionY = 0;
	//}

	//printf("%f\n", currentSpeedX);
	//printf("%f\n", currentSpeedY);

	*xPosition += std::round(currentSpeedX);
	*yPosition += std::round(currentSpeedY);
}

void MoveComponent::MoveUp()
{
	isMovingUp = true;
	directionY -= 1;
}

void MoveComponent::MoveDown()
{
	isMovingDown = true;
	directionY += 1;
}

void MoveComponent::MoveRight()
{
	isMovingRight = true;
	directionX += 1;
}

void MoveComponent::MoveLeft()
{
	isMovingLeft = true;
	directionX -= 1;
}

void MoveComponent::StopMoveUp()
{
	directionY += 1;
	previousDirectionY = -1;
	isMovingUp = false;
}

void MoveComponent::StopMoveDown()
{
	directionY -= 1;
	previousDirectionY = 1;
	isMovingDown = false;
}

void MoveComponent::StopMoveRight()
{
	directionX -= 1;
	previousDirectionX = 1;
	isMovingRight = false;
}

void MoveComponent::StopMoveLeft()
{
	directionX += 1;
	previousDirectionX = -1;
	isMovingLeft = false;
}