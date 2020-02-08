#pragma once

#include "Vector2.h"
#include "Actor.h"
#include "ActorType.h"

class ColliderComponent : public AbstractComponent
{
public:
	ColliderComponent(Vector2 size, bool shouldColide, ActorType actorType);
	~ColliderComponent();

	Vector2 GetSize();
	bool shouldCollide;
	ActorType actorType;


private:
	Vector2 size;

};

