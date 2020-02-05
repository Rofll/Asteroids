#include "SpaceSheep.h"
#include "Time.h"

SpaceSheep::SpaceSheep()
{

}

SpaceSheep::SpaceSheep(const char* spritePass)
{

}

SpaceSheep::~SpaceSheep()
{
	delete renderer;

	renderer = nullptr;
}

//void SpaceSheep::Tick()
//{
//	if (renderer)
//	{
//		renderer->Tick();
//	}
//
//	if (moveComponent)
//	{
//		moveComponent->Tick();
//	}
//}

MoveComponent* SpaceSheep::GetMoveComponent()
{
	return moveComponent;
}