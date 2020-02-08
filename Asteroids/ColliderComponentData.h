#pragma once

#include "Transform.h"
#include "MoveComponent.h"
#include "ColliderComponent.h"

struct ColliderComponentData
{
	Transform* transform;
	MoveComponent* moveComponent;
	ColliderComponent* collider;
	Actor* actor;
};

