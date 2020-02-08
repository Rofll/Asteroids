#pragma once

#include "Vector2.h"
#include "Actor.h"

class ColliderComponent : public AbstractComponent
{
public:
	ColliderComponent(Vector2 size, bool shouldColide);
	~ColliderComponent();

	Vector2 GetSize();
	bool shouldCollide;


private:
	Vector2 size;
};

