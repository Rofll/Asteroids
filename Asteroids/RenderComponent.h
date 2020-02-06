#pragma once

#include "Framework.h"
#include "AbstractComponent.h"

class RenderComponent : public AbstractComponent
{
public:
	RenderComponent(const char* spritePath);
	~RenderComponent();

	Sprite* GetSprite();

private:
	void CreateSprite(const char* pass);

	Sprite* sprite;
};

