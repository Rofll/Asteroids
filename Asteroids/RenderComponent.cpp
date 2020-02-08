#include "RenderComponent.h"
RenderComponent::RenderComponent(Sprite* sprite, int order)
{
	this->sprite = sprite;
	this->order = order;
}

RenderComponent::~RenderComponent()
{

}


Sprite* RenderComponent::GetSprite()
{
	return sprite;
}