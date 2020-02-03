#include "Framework.h"
#include "SpaceSheep.h"
#include "Time.h"

#include <stdio.h>
#include <cmath>
#include "Actor.h"

#include <vector>


/* Test Framework realization */
class MyFramework : public Framework {

public:

	SpaceSheep* spaceSheep;

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = 800;
		height = 600;
		fullscreen = false;
	}

	virtual bool Init() {

		spaceSheep = new SpaceSheep("data/spaceship.png", 0, 0);

		return true;
	}

	virtual void Close() {

	}

	virtual bool Tick() {
        drawTestBackground();

		Time::CalculateDeltaTime();

		spaceSheep->Tick();

		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {

	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {

	}

	virtual void onKeyPressed(FRKey k) 
	{
	/*	if (k == FRKey::UP)
		{
			spaceSheep->MoveForward();
		}

		if (k == FRKey::DOWN)
		{
			spaceSheep->MoveBackward();
		}*/

		/*if (k == FRKey::RIGHT)
		{
			spaceSheep->MoveRight();
		}*/

		/*if (k == FRKey::LEFT)
		{
			spaceSheep->MoveLeft();
		}*/
	}

	virtual void onKeyReleased(FRKey k) {
	}
	
	virtual const char* GetTitle() override
	{
		return "asteroids";
	}
};

int main(int argc, char *argv[])
{
	return run(new MyFramework);
}
