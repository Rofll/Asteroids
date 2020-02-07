#include "ColliderComponent.h"

ColliderComponent::ColliderComponent(Vector2 size)
{
	this->size = size;
}

ColliderComponent::~ColliderComponent()
{

}

Vector2  ColliderComponent::GetSize()
{
	return size;
}