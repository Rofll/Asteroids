#pragma once

#include "BaseComponent.h"

#include "Framework.h"

class RenderComponent : BaseComponent
{
public:
	RenderComponent();
	RenderComponent(const char* spritePath, int* xPosition, int* yPosition);
	~RenderComponent();

	void Tick() override;
	void Draw(int x, int y);
	void CreateSprite(const char* pass);

private:
	Sprite* sprite;

	int* xPosition;
	int* yPosition;
};

