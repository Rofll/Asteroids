#pragma once

#include "Vector2.h"
#include "Actor.h"

class ColliderComponent : public AbstractComponent
{
public:
	ColliderComponent(Vector2 size);
	~ColliderComponent();

	Vector2 GetSize();


private:
	Vector2 size;
};

