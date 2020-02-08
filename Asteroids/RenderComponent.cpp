#include "RenderComponent.h"
RenderComponent::RenderComponent(Sprite* sprite)
{
	this->sprite = sprite;
}

RenderComponent::~RenderComponent()
{

}


Sprite* RenderComponent::GetSprite()
{
	return sprite;
}