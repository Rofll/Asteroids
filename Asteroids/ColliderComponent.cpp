#include "ColliderComponent.h"

ColliderComponent::ColliderComponent(Vector2 size, bool shouldColide, ActorType actorType)
{
	this->size = size;
	this->shouldCollide = shouldColide;
	this->actorType = actorType;
}

ColliderComponent::~ColliderComponent()
{

}

Vector2  ColliderComponent::GetSize()
{
	return size;
}