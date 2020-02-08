#pragma once

#include "Framework.h"
#include "AbstractComponent.h"

class RenderComponent : public AbstractComponent
{
public:
	RenderComponent(Sprite* sprite, int order);
	~RenderComponent();

	Sprite* GetSprite();
	int order;

private:
	Sprite* sprite;
};

