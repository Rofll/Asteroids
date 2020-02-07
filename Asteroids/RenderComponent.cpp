#include "RenderComponent.h"
RenderComponent::RenderComponent(Sprite* sprite)
{
	this->sprite = sprite;
}

RenderComponent::~RenderComponent()
{
	destroySprite(sprite);

	sprite = nullptr;
}


Sprite* RenderComponent::GetSprite()
{
	return sprite;
}