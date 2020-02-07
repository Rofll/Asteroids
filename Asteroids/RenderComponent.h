#pragma once

#include "Framework.h"
#include "AbstractComponent.h"

class RenderComponent : public AbstractComponent
{
public:
	RenderComponent(Sprite* sprite);
	~RenderComponent();

	Sprite* GetSprite();

private:
	Sprite* sprite;
};

