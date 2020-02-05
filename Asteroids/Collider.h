#pragma once

#include "Vector2.h"
#include "Actor.h"

class Collider
{
public:
	Collider();
	~Collider();

	bool Overlap(Collider* other);


private:
	Vector2 size;
	Actor* actor;
};

