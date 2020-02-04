#pragma once

#include "Actor.h"

#include "RenderComponent.h"

class Map : public Actor
{
public:
	Map();
	Map(const char* spritePass);
	~Map();

	void Tick();

private:
	const char* spritePass;

	RenderComponent* renderer;
};
