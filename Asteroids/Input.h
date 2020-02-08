#pragma once

#include "AbstractComponent.h"
#include "Vector2.h"

class Input
{
public:
	Input() {};
	~Input() {};

	Vector2 direction = Vector2::zero;
	bool isMouseDown = false;
};

