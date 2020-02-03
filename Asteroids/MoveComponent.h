#pragma once

#include "BaseComponent.h"

class MoveComponent : BaseComponent
{
public:
	MoveComponent();
	~MoveComponent();

	void MoveUp();
	void MoveDown();
	void MoveRight();
	void MoveLeft();

	void Tick() override;

private:
	int* xPosition;
	int* yPosition;

	int* acceleration;
	int* deacceleration;
};

