#include "Framework.h"
#include "SpaceSheep.h"
#include "Time.h"


#include "MoveComponent.h"

#include <stdio.h>
#include <cmath>
#include "Actor.h"
#include "Transform.h"
#include <vector>
#include "World.h"
#include <vector>


/* Test Framework realization */
class MyFramework : public Framework {

public:

	Actor* rootTransform;
	World* world;

	std::vector<Actor*> actors;

	MyFramework()
	{

	}

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = 800;
		height = 600;
		fullscreen = false;
	}

	virtual bool Init() 
	{
		world = new World();

		rootTransform = new Actor(nullptr, world);

		actors.push_back(CreateActor(rootTransform->GetComponent<Transform>()));

		return true;
	}

	virtual void Close() 
	{

	}

	Actor* CreateActor(Transform* parent)
	{
		auto actor = new Actor(parent, world);
		actor->AddComponent(new MoveComponent(Vector2(1.0, 1.0)));
		actor->AddComponent(new RenderComponent("data/spaceship.png"));
		return actor;
	}

	virtual bool Tick() 
	{
        drawTestBackground();

		Time::instance().CalculateDeltaTime();

		std::vector<int> moveComponentIndexes, transformIndexes;

		for (int i = 0; i < actors.size(); i++)
		{
			if (actors[i]->HasComponent<Transform>() && actors[i]->HasComponent<MoveComponent>())
			{
				moveComponentIndexes.push_back(actors[i]->GetComponentIndex<MoveComponent>());
				transformIndexes.push_back(actors[i]->GetComponentIndex<Transform>());
			}
		}


		Move(moveComponentIndexes, transformIndexes);

		std::vector<int> renders, transforms;

		for (int i = 0; i < actors.size(); i++)
		{
			if (actors[i]->HasComponent<Transform>() && actors[i]->HasComponent<RenderComponent>())
			{
				renders.push_back(actors[i]->GetComponentIndex<RenderComponent>());
				transforms.push_back(actors[i]->GetComponentIndex<Transform>());
			}
		}


		Render(renders, transforms);
		//spaceSheep->Tick();

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
			//playerMoveComponent->MoveUp();
		}

		if (k == FRKey::DOWN)
		{
			//playerMoveComponent->MoveDown();
		}

		if (k == FRKey::RIGHT)
		{
			//playerMoveComponent->MoveRight();
		}

		if (k == FRKey::LEFT)
		{
			//playerMoveComponent->MoveLeft();
		}
	}

	virtual void onKeyReleased(FRKey k) 
	{
		if (k == FRKey::UP)
		{
			//playerMoveComponent->StopMoveUp();
		}

		if (k == FRKey::DOWN)
		{
			//playerMoveComponent->StopMoveDown();
		}

		if (k == FRKey::RIGHT)
		{
			//playerMoveComponent->StopMoveRight();
		}

		if (k == FRKey::LEFT)
		{
			//playerMoveComponent->StopMoveLeft();
		}
	}
	
	virtual const char* GetTitle() override
	{
		return "asteroids";
	}

	void Move(std::vector<int> moveComponentIndexes, std::vector<int> transformIndexes)
	{
		std::vector<AbstractComponent*>* transforms = world->GetComponents<Transform>();
		std::vector<AbstractComponent*>* moveComponents = world->GetComponents<MoveComponent>();

		for (int i = 0; i < moveComponentIndexes.size() && i < transformIndexes.size(); i++)
		{
			(static_cast<Transform*>(transforms->at(transformIndexes[i])))->localPosition += (static_cast<MoveComponent*>(moveComponents->at(moveComponentIndexes[i])))->velocity;
		}
	}

	void Render(std::vector<int> renderComponentIndexes, std::vector<int> transformIndexes)
	{
		std::vector<AbstractComponent*>* transforms = world->GetComponents<Transform>();
		std::vector<AbstractComponent*>* renderers = world->GetComponents<RenderComponent>();

		for (int i = 0; i < renderComponentIndexes.size() && i < transformIndexes.size(); i++)
		{
			Vector2 worldPosition = (static_cast<Transform*>(transforms->at(transformIndexes[i])))->GetWorldPosition();
			drawSprite((static_cast<RenderComponent*>(renderers->at(renderComponentIndexes[i])))->GetSprite(), worldPosition.x, worldPosition.y);
		}
	}
};

int main(int argc, char *argv[])
{
	return run(new MyFramework());
}
