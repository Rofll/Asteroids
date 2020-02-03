#include "RenderComponent.h"

RenderComponent::RenderComponent()
{

}

RenderComponent::RenderComponent(const char* spritePath, int* xPosition, int* yPosition)
{
	this->xPosition = xPosition;
	this->yPosition = yPosition;

	CreateSprite(spritePath);
}

RenderComponent::~RenderComponent()
{
	delete sprite;

	sprite = nullptr;
}

void RenderComponent::Tick()
{
	Draw(*xPosition, *yPosition);
}

void RenderComponent::Draw(int x, int y)
{
	drawSprite(sprite, x, y);
}

void RenderComponent::CreateSprite(const char* pass)
{
	sprite = createSprite(pass);
}