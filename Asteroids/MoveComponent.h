#pragma once

#include "AbstractComponent.h"
#include "Transform.h"
#include "Vector2.h"

class MoveComponent : public AbstractComponent
{
public:
	MoveComponent(Vector2 velocity);
	~MoveComponent();

	Vector2 velocity;
};

