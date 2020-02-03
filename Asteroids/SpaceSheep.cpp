#include "SpaceSheep.h"
#include "Time.h"
#include <stdio.h>

SpaceSheep::SpaceSheep()
{
	
}

SpaceSheep::SpaceSheep(const char* spritePass, int xPosition, int yPosition)
{
	this->xPosition = xPosition;
	this->yPosition = yPosition;

	renderer = new RenderComponent(spritePass, &this->xPosition, &this->yPosition);
}

SpaceSheep::~SpaceSheep()
{
	delete renderer;

	renderer = nullptr;
}

void SpaceSheep::Tick()
{
	renderer->Tick();
}