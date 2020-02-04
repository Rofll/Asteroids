#include "SpaceSheep.h"
#include "Time.h"

SpaceSheep::SpaceSheep()
{
	xPosition = 0;
	yPosition = 0;
}

SpaceSheep::SpaceSheep(const char* spritePass, int xPosition, int yPosition)
{
	this->xPosition = xPosition;
	this->yPosition = yPosition;

	renderer = new RenderComponent(spritePass,
								&this->xPosition, &this->yPosition);

	moveComponent = new MoveComponent(&this->xPosition, &this->yPosition,
									&this->minSpeed, &this->maxSpeed,
									&this->acceleration, &this->deaceleration);

	//inputComponent = new InputComponent();
}

SpaceSheep::~SpaceSheep()
{
	delete renderer;

	renderer = nullptr;
}

void SpaceSheep::Tick()
{
	if (renderer)
	{
		renderer->Tick();
	}

	if (moveComponent)
	{
		moveComponent->Tick();
	}
}

MoveComponent* SpaceSheep::GetMoveComponent()
{
	return moveComponent;
}