#include "Framework.h"
#include "SpaceSheep.h"
#include "Time.h"

#include "InputComponent.h"
#include "MoveComponent.h"

#include <stdio.h>
#include <cmath>
#include "Actor.h"

#include <vector>


/* Test Framework realization */
class MyFramework : public Framework {

public:

	MyFramework()
	{
		printf("Hello!");
	}

	SpaceSheep* spaceSheep;
	InputComponent* playerInput;
	MoveComponent* playerMoveComponent;

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = 800;
		height = 600;
		fullscreen = false;
	}

	virtual bool Init() 
	{
		spaceSheep = new SpaceSheep("data/spaceship.png", 0, 0);

		playerMoveComponent = spaceSheep->GetMoveComponent();

		//playerInput = spaceSheep->GetInputComponent();
		return true;
	}

	virtual void Close() 
	{

	}

	virtual bool Tick() 
	{
        drawTestBackground();

		Time::instance().CalculateDeltaTime();

		spaceSheep->Tick();

		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) 
	{

	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) 
	{

	}

	virtual void onKeyPressed(FRKey k) 
	{
		if (k == FRKey::UP)
		{
			playerMoveComponent->MoveUp();
		}

		if (k == FRKey::DOWN)
		{
			playerMoveComponent->MoveDown();
		}

		if (k == FRKey::RIGHT)
		{
			playerMoveComponent->MoveRight();
		}

		if (k == FRKey::LEFT)
		{
			playerMoveComponent->MoveLeft();
		}
	}

	virtual void onKeyReleased(FRKey k) 
	{
		if (k == FRKey::UP)
		{
			playerMoveComponent->StopMoveUp();
		}

		if (k == FRKey::DOWN)
		{
			playerMoveComponent->StopMoveDown();
		}

		if (k == FRKey::RIGHT)
		{
			playerMoveComponent->StopMoveRight();
		}

		if (k == FRKey::LEFT)
		{
			playerMoveComponent->StopMoveLeft();
		}
	}
	
	virtual const char* GetTitle() override
	{
		return "asteroids";
	}
};

int main(int argc, char *argv[])
{
	return run(new MyFramework());
}
