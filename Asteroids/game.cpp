#include "Framework.h"
#include "SpaceSheep.h"
#include "Time.h"

#include <ctime>

//#include "ColliderComponentData.h"

#include "MoveComponent.h"
#include "AsteroidComponent.h"
#include "ColliderComponent.h"
#include "BulletComponent.h"
#include "Input.h"

#include "ColliderComponentData.h"

#include <stdio.h>
#include <cmath>
#include "Actor.h"
#include "Transform.h"
#include <vector>
#include "World.h"
#include <vector>
#include <algorithm>
#include <set>

#define M_PI 3.14159265

/* Test Framework realization */
class MyFramework : public Framework {

public:

	Actor* rootActor;
	Actor* spaceShip;
	World* world;

	Vector2 cellSize;

	Vector2 screenSize;

	Input* input;
		
	const float minVelocity = 30;
	const float maxVelocity = 50;

	const float spaceShipSpeed = 100;
	const float spaceShipDeaceleration = 2;

	Sprite* spaceShipSprite;
	Sprite* asteroidSprite;
	Sprite* bulletSprite;

	bool isFire = false;

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

		input = new Input();


		std::srand(unsigned(std::time(0)));

		int screenWidth;
		int screenHeight;

		getScreenSize(screenWidth, screenHeight);

		screenSize = Vector2(screenWidth, screenHeight);
		cellSize = Vector2(200, 200);

		rootActor = CreateActor(nullptr);
		spaceShipSprite = createSprite("data\\spaceship.png");
		asteroidSprite = createSprite("data\\big_asteroid.png");
		bulletSprite = createSprite("data\\bullet.png");

		CreateSpaceShip(spaceShipSprite);

		for (int i = 0; i < 10; i++)
		{
			CreateAsteroid(asteroidSprite);
		}

		return true;
	}

	virtual void Close() 
	{

	}

	Actor* CreateActor(Transform* parent)
	{
		auto actor = new Actor(parent, world);
		actors.push_back(actor);

		return actor;
	}

	void CreateSpaceShip(Sprite* sprite)
	{
		spaceShip = CreateActor(rootActor->GetComponent<Transform>());

		spaceShip->AddComponent<RenderComponent>(new RenderComponent(sprite));
		spaceShip->AddComponent<MoveComponent>(new MoveComponent(Vector2::one));
		spaceShip->AddComponent<ColliderComponent>(new ColliderComponent(GetSpriteSize(sprite), false));


		float x = screenSize.x * static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float y = screenSize.y * static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

		spaceShip->GetComponent<Transform>()->localPosition = Vector2(x, y);


	}

	void CreateAsteroid(Sprite* sprite)
	{
		if (spaceShip == nullptr)
		{
			return;
		}

		Actor* asteroid = CreateActor(rootActor->GetComponent<Transform>());
	    
		asteroid->AddComponent<RenderComponent>(new RenderComponent(sprite));

		float velocity = (maxVelocity - minVelocity) * static_cast <float> (rand()) / static_cast <float> (RAND_MAX) + minVelocity;
		float angle = M_PI * static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

		Vector2 velocityDirection = Vector2(cos(angle), sin(angle)) * velocity;

		Vector2 spaceShipPosition = spaceShip->GetComponent<Transform>()->localPosition;

		float x = screenSize.x * static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float y = screenSize.y * static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

		Vector2 position(x, y);

		float distance = position.Distance(spaceShipPosition);

		if (distance < 200)
		{
			position += (position - spaceShipPosition).Normalized() * 200;
		}

		asteroid->GetComponent<Transform>()->localPosition = position;

		asteroid->AddComponent<MoveComponent>(new MoveComponent(velocityDirection));
		asteroid->AddComponent<AsteroidComponent>(new AsteroidComponent());

		asteroid->AddComponent<ColliderComponent>(new ColliderComponent(GetSpriteSize(sprite), true));
	}

	void CreateBullet(Actor* parent)
	{
		if (spaceShip == nullptr)
		{
			return;
		}

		Actor* bullet = CreateActor(rootActor->GetComponent<Transform>());

		RenderComponent* parentRenderComponent = parent->GetComponent<RenderComponent>();

		Vector2 parentSize = GetSpriteSize(parentRenderComponent->GetSprite());

		Transform* transformBullet = bullet->GetComponent<Transform>();

		Vector2 spawnPosition = parent->GetComponent<Transform>()->GetWorldPosition();

		transformBullet->localPosition = Vector2(spawnPosition.x + parentSize.x / 2, spawnPosition.y + parentSize.y / 2);

		bullet->AddComponent<RenderComponent>(new RenderComponent(bulletSprite));
		bullet->AddComponent<MoveComponent>(new MoveComponent(Vector2(10,10)));
		bullet->AddComponent<ColliderComponent>(new ColliderComponent(GetSpriteSize(bulletSprite), false));
		bullet->AddComponent<BulletComponent>(new BulletComponent());

		actors.push_back(bullet);
	}

	Vector2 GetSpriteSize(Sprite* sprite)
	{
		int widht;
		int height;

		getSpriteSize(sprite, widht, height);

		return Vector2(widht, height);
	}

	virtual bool Tick() 
	{
        drawTestBackground();

		Time::instance().CalculateDeltaTime();

		OnFire();

		MovePlayer();

		std::set<Actor*> actorsToDestroy;

		//std::vector<Actor*> actorsToDestroy;

		std::vector<int> moveComponentIndexes, transformIndexes;

		for (int i = 0; i < actors.size(); i++)
		{
			if (actors[i]->HasComponent<Transform>() && actors[i]->HasComponent<MoveComponent>())
			{
				moveComponentIndexes.push_back(actors[i]->GetComponentIndex<MoveComponent>());
				transformIndexes.push_back(actors[i]->GetComponentIndex<Transform>());
			}
		}

		std::vector<int> collision_transforms, collision_colliders, collision_moves;
		std::vector<Actor*> collisionActors;

		Move(moveComponentIndexes, transformIndexes);

		for (int i = 0; i < actors.size(); i++)
		{
			if (actors[i]->HasComponent<Transform>() && actors[i]->HasComponent<ColliderComponent>() && actors[i]->HasComponent<MoveComponent>())
			{
				collision_transforms.push_back(actors[i]->GetComponentIndex<Transform>());
				collision_colliders.push_back(actors[i]->GetComponentIndex<ColliderComponent>());
				collision_moves.push_back(actors[i]->GetComponentIndex<MoveComponent>());
				collisionActors.push_back(actors[i]);
			}
		}

		Collision(collisionActors, &actorsToDestroy ,collision_colliders, collision_moves, collision_transforms);
		
		DestroyActors(&actorsToDestroy);

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

		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) 
	{

	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) 
	{
		InputMouse(button, isReleased);
	}

	virtual void onKeyPressed(FRKey k) 
	{
		InputKeyboard(k, false);
	}

	virtual void onKeyReleased(FRKey k) 
	{
		InputKeyboard(k, true);
	}
	
	virtual const char* GetTitle() override
	{
		return "asteroids";
	}

	void MovePlayer()
	{
		if (spaceShip == nullptr)
		{
			return;
		}

		MoveComponent* moveComponent = spaceShip->GetComponent<MoveComponent>();

		moveComponent->velocity -= moveComponent->velocity.Normalized() * spaceShipSpeed * (Time::instance().deltaTime * spaceShipDeaceleration);

		moveComponent->velocity += input->direction * spaceShipSpeed;

		moveComponent->velocity.Clamp(Vector2(spaceShipSpeed, spaceShipSpeed));
	}

	void Move(std::vector<int> moveComponentIndexes, std::vector<int> transformIndexes)
	{
		std::vector<AbstractComponent*>* transforms = world->GetComponents<Transform>();
		std::vector<AbstractComponent*>* moveComponents = world->GetComponents<MoveComponent>();

		for (int i = 0; i < moveComponentIndexes.size() && i < transformIndexes.size(); i++)
		{
			Transform* transform = (static_cast<Transform*>(transforms->at(transformIndexes[i])));
			transform->localPosition += (static_cast<MoveComponent*>(moveComponents->at(moveComponentIndexes[i])))->velocity * Time::instance().deltaTime;
			transform->localPosition = transform->localPosition.WrapAround(screenSize);
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

	void Collision(std::vector<Actor*> actors, std::set<Actor*>* actorsToDestroy, std::vector<int> colliderComnponentIndexes, std::vector<int> moveComponentIndexes, std::vector<int> transformIndexes)
	{
		int cells_x = screenSize.x / cellSize.x, cells_y = screenSize.y / cellSize.y;

		std::vector<ColliderComponentData>* cells = new std::vector<ColliderComponentData>[cells_x, cells_y];

		std::vector<AbstractComponent*>* transforms = world->GetComponents<Transform>();
		std::vector<AbstractComponent*>* colliders = world->GetComponents<ColliderComponent>();
		std::vector<AbstractComponent*>* moveComponents = world->GetComponents<MoveComponent>();

		for (int i = 0; i < colliderComnponentIndexes.size() && i < moveComponentIndexes.size() && i < transformIndexes.size(); i++)
		{
			ColliderComponent* colliderComponent = (static_cast<ColliderComponent*>(colliders->at(colliderComnponentIndexes[i])));
			MoveComponent* moveComponent = (static_cast<MoveComponent*>(moveComponents->at(moveComponentIndexes[i])));
			Transform* transform = (static_cast<Transform*>(transforms->at(transformIndexes[i])));
			Actor* actor = actors.at(i);

			ColliderComponentData collisionContainer = ColliderComponentData();

			collisionContainer.collider = colliderComponent;
			collisionContainer.moveComponent = moveComponent;
			collisionContainer.transform = transform;
			collisionContainer.actor = actor;
			
			Vector2 pos = transform->GetWorldPosition();
			Vector2 size = colliderComponent->GetSize();

			Vector2Int topLeft = positionToCellIndex(pos, cellSize),
				topRight = positionToCellIndex(Vector2(pos.x + size.x, pos.y), cellSize),
				botLeft = positionToCellIndex(Vector2(pos.x, pos.y + size.y), cellSize),
				botRigth = positionToCellIndex(pos + size, cellSize);

			cells[topLeft.x, topLeft.y].push_back(collisionContainer);
			if (topLeft.x != topRight.x)
			{
				cells[topRight.x, topRight.y].push_back(collisionContainer);
			}
			if (topLeft.y != botLeft.y)
			{
				cells[botLeft.x, botLeft.y].push_back(collisionContainer);
			}
			if (topLeft.x != botRigth.x && topLeft.y != botRigth.y)
			{
				cells[botRigth.x, botRigth.y].push_back(collisionContainer);
			}
		}

		for (int i = 0; i < screenSize.x / cellSize.x; i++)
		{
			for (int j = 0; j < screenSize.y / cellSize.y; j++)
			{
				for (int k = 0; k < cells[i,j].size(); k++)
				{
					for (int l = k; l < cells[i, j].size(); l++)
					{
						if (cells[i, j][l].collider != cells[i, j][k].collider)
						{
							if (!CheckPhysicsCollide(cells[i, j][l], cells[i, j][k]))
							{
								actorsToDestroy->insert(cells[i, j][l].actor);
								actorsToDestroy->insert(cells[i, j][k].actor);
							}
						}
					}
				}
			}
		}
		delete []cells;
	}

	Vector2Int positionToCellIndex(Vector2 pos, Vector2 cellSize)
	{
		Vector2 wrapped = pos.WrapAround(screenSize);
		return Vector2Int(floor(wrapped.x / cellSize.x), floor(wrapped.y / cellSize.y));
	}


	bool CheckPhysicsCollide(ColliderComponentData data1, ColliderComponentData data2)
	{
		
		Vector2 position1 = data1.transform->GetWorldPosition();
		Vector2 position2 = data2.transform->GetWorldPosition();

		Vector2 size1 = data1.collider->GetSize();
		Vector2 size2 = data2.collider->GetSize();

		if (isInsideBox(position1 - position2, size2) || isInsideBox(Vector2(position1.x + size1.x, position1.y).WrapAround(screenSize) - position2, size2)
			|| isInsideBox(Vector2(position1.x, size1.y + position1.y).WrapAround(screenSize) - position2, size2)
			|| isInsideBox((position1 + size1).WrapAround(screenSize) - position2, size2))
		{

			if (!data1.collider->shouldCollide || !data2.collider->shouldCollide)
			{
				return false;
			}

			Vector2 tmpVelocity = data1.moveComponent->velocity;
			data1.moveComponent->velocity = data2.moveComponent->velocity;
			data2.moveComponent->velocity = tmpVelocity;

			Vector2 totalSize = (size1 + size2) * 0.5;


			Vector2 center1 = (position1 + size1 * 0.5);
			Vector2 center2 = (position2 + size2 * 0.5);

			if ((position1 + size1).x > screenSize.x)
			{
				center1.x -= screenSize.x;
			}
			if ((position1 + size1).y > screenSize.y)
			{
				center1.y -= screenSize.y;
			}
			if ((position2 + size2).x > screenSize.x)
			{
				center2.x -= screenSize.x;
			}
			if ((position2 + size2).y > screenSize.y)
			{
				center2.y -= screenSize.y;
			}
			Vector2 distance = center1 - center2;

			Vector2 shift;

			if (abs(distance.x / totalSize.x) > abs(distance.y / totalSize.y))
			{
				shift = (distance * (abs(totalSize.x / distance.x) - 1)) * 0.5;
			}
			else
			{
				shift = (distance * (abs(totalSize.y / distance.y) - 1)) * 0.5;
			}

			data1.transform->localPosition += shift;
			data1.transform->localPosition = data1.transform->localPosition.WrapAround(screenSize);
			data2.transform->localPosition -= shift;
			data2.transform->localPosition = data2.transform->localPosition.WrapAround(screenSize);
			printf("%f %f\n", data2.transform->localPosition.x, data2.transform->localPosition.y);
			printf("%f %f\n", data1.transform->localPosition.x, data1.transform->localPosition.y);
		}

		return true;
	}

	bool isInsideBox(Vector2 point, Vector2 size)
	{
		return point.x > 0 && point.y > 0 && point.x < size.x && point.y < size.y;
	}

	void OnFire()
	{
		if (input->isMouseDown)
		{
			CreateBullet(spaceShip);
			input->isMouseDown = false;
		}
	}

	void InputMouse(FRMouseButton mouseButton, bool isReleased)
	{
		if (!isReleased)
		{
			input->isMouseDown = true;
		}
	}

	void InputKeyboard(FRKey key, bool isReleased)
	{
		if (key == FRKey::UP && !isReleased)
		{
			input->direction += Vector2(0, -1);
		}

		else if(key == FRKey::UP && isReleased)
		{
			input->direction += Vector2(0, 1);
		}

		else if (key == FRKey::DOWN && !isReleased)
		{
			input->direction += Vector2(0, 1);
		}

		else if (key == FRKey::DOWN && isReleased)
		{
			input->direction += Vector2(0, -1);
		}

		else if (key == FRKey::RIGHT && !isReleased)
		{
			input->direction += Vector2(1, 0);
		}

		else if (key == FRKey::RIGHT && isReleased)
		{
			input->direction += Vector2(-1, 0);
		}

		else if (key == FRKey::LEFT && !isReleased)
		{
			input->direction += Vector2(-1, 0);
		}

		else if (key == FRKey::LEFT && isReleased)
		{
			input->direction += Vector2(1, 0);
		}
	}

	void DestroyActors(std::set<Actor*>* actorsToDestroy)
	{
		for (auto actor : *actorsToDestroy)
		{
			actors.erase(std::remove(actors.begin(), actors.end(), actor), actors.end());

			if (actor == spaceShip)
			{
				spaceShip = nullptr;
			}

			delete actor;
		}	

		if (spaceShip == nullptr)
		{
			printf("AAAAAAAAAAAA");
			CreateSpaceShip(spaceShipSprite);
		}
	}
};

int main(int argc, char *argv[])
{
	return run(new MyFramework());
}
