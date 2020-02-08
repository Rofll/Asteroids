#pragma once

#include "Framework.h"
#include "Vector2.h"

struct RenderModel
{
	RenderModel(Sprite* sprite, Vector2 positionWorld);
	~RenderModel() = default;

	Sprite* sprite;
	Vector2 positionWorld;
};

