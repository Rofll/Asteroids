#include "RenderComponent.h"
RenderComponent::RenderComponent(const char* spritePath)
{
	CreateSprite(spritePath);
}

RenderComponent::~RenderComponent()
{
	destroySprite(sprite);

	sprite = nullptr;
}

void RenderComponent::CreateSprite(const char* pass)
{
	sprite = createSprite(pass);
}

Sprite* RenderComponent::GetSprite()
{
	return sprite;
}