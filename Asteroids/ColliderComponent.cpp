#include "ColliderComponent.h"

ColliderComponent::ColliderComponent(Vector2 size, bool shouldColide)
{
	this->size = size;
	this->shouldCollide = shouldColide;
}

ColliderComponent::~ColliderComponent()
{

}

Vector2  ColliderComponent::GetSize()
{
	return size;
}