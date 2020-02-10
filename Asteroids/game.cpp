#include "Framework.h"
#include "Time.h"

#include <ctime>

#include "MoveComponent.h"
#include "ColliderComponent.h"
#include "BulletComponent.h"
#include "RenderComponent.h"

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

#include "RenderModel.h"

#define M_PI 3.14159265

/* Test Framework realization */
class MyFramework : public Framework {

public:

	Actor* rootActor;
	Actor* spaceShip;
	Actor* aim;

	World* world;

	Vector2 cellSize;

	Vector2 mapSize = Vector2(1000, 1000);
	Vector2 screenSize = Vector2(800, 600);
	Vector2 cameraPosition;

	Input* input;
		
	const float minVelocity = 30;
	const float maxVelocity = 50;

	const float spaceShipSpeed = 200;
	const float spaceShipDeaceleration = 2;

	const float bulletSpeed = 500;

	Sprite* spaceShipSprite;
	Sprite* asteroidSprite;
	Sprite* smallAsteroidSprite;
	Sprite* bulletSprite;
	Sprite* aimSprite;
	Sprite* bgSprite;

	bool isFire = false;

	int maxAsteroidsCount = 10;
	int currentAstreriodsCount = 0;

	std::vector<Actor*> actors;

	Vector2 mousePosition;
	Vector2 aimOffset;

	int maxBullets = 3;
	std::vector<Actor*> totalBullets;

	std::set<Actor*> actorsToDestroy;


	int score = 0;

	int maxActorsToDelete = 20;
	int currentActorsToDelete = 0;

	float abilityPorbability = 0.3;

	bool isGame = false;

	MyFramework(Vector2Int windowSize, Vector2Int mapSize, int asteroidsNum, int ammoNum, float abilityPorbability)
	{
		if (windowSize.x > Vector2Int::zero.x && windowSize.y > Vector2Int::zero.y)
		{
			this->screenSize = Vector2(windowSize.x, windowSize.y);
		}

		if (mapSize.x > Vector2Int::zero.x && mapSize.y > Vector2Int::zero.y)
		{
			this->mapSize = Vector2(mapSize.x, mapSize.y);
		}
		
		if (asteroidsNum > 0)
		{
			this->maxAsteroidsCount = asteroidsNum;
		}
		
		if (ammoNum > 0)
		{
			this->maxBullets = ammoNum;
		}
		
		if (abilityPorbability > 0)
		{
			this->abilityPorbability = abilityPorbability;
		}
	}

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = screenSize.x;
		height = screenSize.y;
		fullscreen = false;
	}

	virtual bool Init() 
	{
		world = new World();

		input = new Input();

		cellSize = Vector2(200, 200);

		spaceShipSprite = createSprite("data\\spaceship.png");
		asteroidSprite = createSprite("data\\big_asteroid.png");
		smallAsteroidSprite = createSprite("data\\small_asteroid.png");
		bulletSprite = createSprite("data\\bullet.png");
		aimSprite = createSprite("data\\circle.tga");
		bgSprite = createSprite("data\\background.png");

		StartGame();

		showCursor(false);

		return true;
	}

	virtual void Close() 
	{

	}

	void Restart()
	{
		printf("RESTART!\n", score);

		DestroyAllActors();
		StartGame();
	}

	void GameOver()
	{
		isGame = false;

		printf("Your Score: %i\n", score);
	}

	void DestroyAllActors()
	{
		totalBullets.clear();

		for (int i = 0; i < actors.size(); i++)
		{
			delete actors[i];
		}

		actors.clear();
		
		rootActor = nullptr;
		spaceShip = nullptr;
	}

	void StartGame()
	{
		rootActor = CreateActor(nullptr);

		CreateSpaceShip(spaceShipSprite);
		aim = CreateActor(rootActor->GetComponent<Transform>());

		aim->AddComponent<RenderComponent>(new RenderComponent(aimSprite, 3));

		Vector2 aimSize = GetSpriteSize(aimSprite);

		aimOffset = Vector2(aimSize.x / 2, aimSize.y / 2);;

		aim->GetComponent<Transform>()->localPosition -= aimOffset;

		for (int i = 0; i < maxAsteroidsCount; i++)
		{
			CreateRandomAsteroid();
		}

		currentActorsToDelete = 0;
		currentAstreriodsCount = 0;
		score = 0;

		isGame = true;
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

		spaceShip->AddComponent<RenderComponent>(new RenderComponent(sprite, 2));
		spaceShip->AddComponent<MoveComponent>(new MoveComponent(Vector2::one));
		spaceShip->AddComponent<ColliderComponent>(new ColliderComponent(GetSpriteSize(sprite), false, ActorType::Player));

		float x = mapSize.x / 2;
		float y = mapSize.y / 2;

		spaceShip->GetComponent<Transform>()->localPosition = Vector2(x, y);
	}

	void CreateRandomAsteroid()
	{
		int rand = std::rand() % 2;

		if (rand == 0)
		{
			CreateAsteroid(asteroidSprite);
		}

		else
		{
			CreateSmallAsteroid(smallAsteroidSprite, Vector2(-1, -1));
		}
	}

	void CreateAsteroid(Sprite* sprite)
	{
		if (spaceShip == nullptr)
		{
			return;
		}

		Actor* asteroid = CreateActor(rootActor->GetComponent<Transform>());
	    
		asteroid->AddComponent<RenderComponent>(new RenderComponent(sprite, 0));

		float velocity = (maxVelocity - minVelocity) * static_cast <float> (rand()) / static_cast <float> (RAND_MAX) + minVelocity;
		float angle = 2 * M_PI * static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

		Vector2 velocityDirection = Vector2(cos(angle), sin(angle)) * velocity;

		printf("%f %f\n", velocityDirection.x / M_PI, velocityDirection.y / M_PI);

		Vector2 spaceShipPosition = spaceShip->GetComponent<Transform>()->localPosition;

		float x = mapSize.x * static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float y = mapSize.y * static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

		Vector2 position(x, y);

		float distance = position.Distance(spaceShipPosition);

		if (distance < 200)
		{
			position += (position - spaceShipPosition).Normalized() * 200;
		}

		asteroid->GetComponent<Transform>()->localPosition = position;

		asteroid->AddComponent<MoveComponent>(new MoveComponent(velocityDirection));
		asteroid->AddComponent<ColliderComponent>(new ColliderComponent(GetSpriteSize(sprite), true, ActorType::AsteroidBig));

		currentAstreriodsCount++;
	}
	
	void CreateSmallAsteroid(Sprite* sprite, Vector2 bigAsteroidPosition)
	{
		if (spaceShip == nullptr)
		{
			return;
		}

		Actor* asteroid = CreateActor(rootActor->GetComponent<Transform>());

		asteroid->AddComponent<RenderComponent>(new RenderComponent(sprite, 0));

		float velocity = (maxVelocity - minVelocity) * static_cast <float> (rand()) / static_cast <float> (RAND_MAX) + minVelocity;
		float angle = M_PI * static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

		Vector2 velocityDirection = Vector2(cos(angle), sin(angle)) * velocity;

		Vector2 spaceShipPosition = spaceShip->GetComponent<Transform>()->localPosition;


		Vector2 position(bigAsteroidPosition.x, bigAsteroidPosition.y);

		if (bigAsteroidPosition == Vector2(-1, -1))
		{
			float x = mapSize.x * static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			float y = mapSize.y * static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

			position = Vector2(x, y);

			float distance = position.Distance(spaceShipPosition);

			if (distance < 200)
			{
				position += (position - spaceShipPosition).Normalized() * 200;
			}
		}

		asteroid->GetComponent<Transform>()->localPosition = position;

		asteroid->AddComponent<MoveComponent>(new MoveComponent(velocityDirection));
		asteroid->AddComponent<ColliderComponent>(new ColliderComponent(GetSpriteSize(sprite), true, ActorType::AsteroidSmall));

		currentAstreriodsCount++;
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

		spawnPosition = Vector2(spawnPosition.x + parentSize.x / 2, spawnPosition.y + parentSize.y / 2);

		transformBullet->localPosition = spawnPosition;

		Vector2 direction = (mousePosition - screenSize * 0.5).Normalized();
		

		bullet->AddComponent<RenderComponent>(new RenderComponent(bulletSprite, 1));
		bullet->AddComponent<MoveComponent>(new MoveComponent(Vector2(direction.x * bulletSpeed, direction.y * bulletSpeed)));
		bullet->AddComponent<ColliderComponent>(new ColliderComponent(GetSpriteSize(bulletSprite), false, ActorType::Bullet));
		bullet->AddComponent<BulletComponent>(new BulletComponent());


		totalBullets.push_back(bullet);

		if (totalBullets.size() > maxBullets)
		{
			actorsToDestroy.insert(totalBullets[0]);
			totalBullets.erase(totalBullets.begin());
		}
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

		if (!isGame)
		{
			Restart();
		}

		OnShot();

		MovePlayer();

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

		Collision(collisionActors, &actorsToDestroy, collision_colliders, collision_moves, collision_transforms);

		cameraPosition = spaceShip->GetComponent<Transform>()->GetWorldPosition() - screenSize * 0.5 + GetSpriteSize(spaceShipSprite) * 0.5;

		aim->GetComponent<Transform>()->localPosition = mousePosition - aimOffset + cameraPosition;

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

		if (currentAstreriodsCount < maxAsteroidsCount)
		{
			for (int i = currentAstreriodsCount; i < maxAsteroidsCount; i++)
			{
				CreateRandomAsteroid();
			}
		}

		DestroyActors(&actorsToDestroy);

		actorsToDestroy.erase(actorsToDestroy.begin(), actorsToDestroy.end());

		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) 
	{
		mousePosition = Vector2(x, y);
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
			transform->localPosition = transform->localPosition.WrapAround(mapSize);
		}
	}

	void Render(std::vector<int> renderComponentIndexes, std::vector<int> transformIndexes)
	{
		std::vector<AbstractComponent*>* transforms = world->GetComponents<Transform>();
		std::vector<AbstractComponent*>* renderers = world->GetComponents<RenderComponent>();

		std::map<int, std::vector<RenderModel>> renderOrderMap;

		for (int i = 0; i < renderers->size() && i < transformIndexes.size(); i++)
		{
			RenderComponent* renderComponent = static_cast<RenderComponent*>(renderers->at(renderComponentIndexes[i]));

			Vector2 worldPosition = (static_cast<Transform*>(transforms->at(transformIndexes[i])))->GetWorldPosition();

			renderOrderMap[renderComponent->order].push_back(RenderModel(renderComponent->GetSprite(), worldPosition));
		}

		std::vector<Vector2> cameraShiftings = { Vector2::zero };

		if ((cameraPosition).x < 0)
		{
			//left
			cameraShiftings.push_back(Vector2(mapSize.x, 0));
		}
		else if ((cameraPosition + screenSize).x > mapSize.x)
		{
			//right
			cameraShiftings.push_back(Vector2(-mapSize.x, 0));
		}

		if ((cameraPosition).y < 0)
		{
			//up
			if (cameraShiftings.size() > 1)
			{
				cameraShiftings.push_back(Vector2(0, mapSize.y) + cameraShiftings[1]);
			}
			cameraShiftings.push_back(Vector2(0, mapSize.y));
		}
		else if ((cameraPosition + screenSize).y > mapSize.y)
		{
			//down
			if (cameraShiftings.size() > 1)
			{
				cameraShiftings.push_back(Vector2(0, -mapSize.y) + cameraShiftings[1]);
			}
			cameraShiftings.push_back(Vector2(0, -mapSize.y));
		}

		for (Vector2 shift : cameraShiftings)
		{
			Vector2 bgsize = GetSpriteSize(bgSprite);

			for (int i = 0; i < 1 + mapSize.x / bgsize.x; i++)
			{
				for (int j = 0; j < 1 + mapSize.y / bgsize.y; j++)
				{
					drawSprite(bgSprite, i * bgsize.x - cameraPosition.x - shift.x, j * bgsize.y - cameraPosition.y - shift.y);
				}
			}
		}

		for (int i = 0; i < renderOrderMap.size(); i++)
		{
			for (int j = 0; j < renderOrderMap[i].size(); j++)
			{
				for (Vector2 shift : cameraShiftings)
				{
					RenderModel renderModel = renderOrderMap[i][j];
					drawSprite(renderModel.sprite,
						renderModel.positionWorld.x - cameraPosition.x - shift.x,
						renderModel.positionWorld.y - cameraPosition.y - shift.y);
				}
			}

		}
		
	}

	void Collision(std::vector<Actor*> actors, std::set<Actor*>* actorsToDestroy, std::vector<int> colliderComnponentIndexes, std::vector<int> moveComponentIndexes, std::vector<int> transformIndexes)
	{
		int cells_x = mapSize.x / cellSize.x, cells_y = mapSize.y / cellSize.y;

		std::vector<ColliderComponentData>** cells = new std::vector<ColliderComponentData> * [cells_x];
		for (int i = 0; i < cells_x; i++)
		{
			cells[i] = new std::vector<ColliderComponentData>[cells_y];
		}

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
			cells[topLeft.x][topLeft.y].push_back(collisionContainer);
			if (topLeft.x != topRight.x)
			{
				cells[topRight.x][topRight.y].push_back(collisionContainer);
			}
			if (topLeft.y != botLeft.y)
			{
				cells[botLeft.x][botLeft.y].push_back(collisionContainer);
			}
			if (topLeft.x != botRigth.x && topLeft.y != botRigth.y)
			{
				cells[botRigth.x][botRigth.y].push_back(collisionContainer);
			}
		}

		for (int i = 0; i < cells_x; i++)
		{
			for (int j = 0; j < cells_y; j++)
			{
				for (size_t k = 0; k < cells[i][j].size(); k++)
				{
					for (size_t l = k + 1; l < cells[i][j].size(); l++)
					{
						if (cells[i][j][l].collider != cells[i][j][k].collider && !cells[i][j][l].actor->IsMarkedAsDestroyed() && !cells[i][j][k].actor->IsMarkedAsDestroyed())
						{
							if (!CheckPhysicsCollide(cells[i][j][l], cells[i][j][k]))
							{
								if (cells[i][j][l].collider->actorType == ActorType::AsteroidBig || cells[i][j][k].collider->actorType == ActorType::AsteroidBig)
								{
									if (cells[i][j][l].collider->actorType == ActorType::Bullet || cells[i][j][k].collider->actorType == ActorType::Bullet)
									{
										score++;


										if (cells[i][j][l].collider->actorType == ActorType::Bullet)
										{
											totalBullets.erase(std::remove(totalBullets.begin(), totalBullets.end(), cells[i][j][l].actor), totalBullets.end());
										}

										else
										{
											totalBullets.erase(std::remove(totalBullets.begin(), totalBullets.end(), cells[i][j][k].actor), totalBullets.end());
										}

										if (cells[i][j][k].collider->actorType == AsteroidBig)
										{
											CreateSmallAsteroid(smallAsteroidSprite, cells[i][j][k].transform->GetWorldPosition());
											CreateSmallAsteroid(smallAsteroidSprite, cells[i][j][k].transform->GetWorldPosition());
										}

										else
										{
											CreateSmallAsteroid(smallAsteroidSprite, cells[i][j][l].transform->GetWorldPosition());
											CreateSmallAsteroid(smallAsteroidSprite, cells[i][j][l].transform->GetWorldPosition());
										}
									}


									cells[i][j][l].actor->MarkAsDestroyed();
									cells[i][j][k].actor->MarkAsDestroyed();
									actorsToDestroy->insert(cells[i][j][l].actor);
									actorsToDestroy->insert(cells[i][j][k].actor);

									currentAstreriodsCount--;
								}


								else if (cells[i][j][l].collider->actorType == ActorType::AsteroidSmall || cells[i][j][k].collider->actorType == ActorType::AsteroidSmall)
								{
									if (cells[i][j][l].collider->actorType == ActorType::Bullet || cells[i][j][k].collider->actorType == ActorType::Bullet)
									{
										score++;

										if (cells[i][j][l].collider->actorType == ActorType::Bullet)
										{
											totalBullets.erase(std::remove(totalBullets.begin(), totalBullets.end(), cells[i][j][l].actor), totalBullets.end());
										}

										else
										{
											totalBullets.erase(std::remove(totalBullets.begin(), totalBullets.end(), cells[i][j][k].actor), totalBullets.end());
										}
									}

									cells[i][j][l].actor->MarkAsDestroyed();
									cells[i][j][k].actor->MarkAsDestroyed();
									actorsToDestroy->insert(cells[i][j][l].actor);
									actorsToDestroy->insert(cells[i][j][k].actor);

									currentAstreriodsCount--;
								}
							}
						} 
					}
				}
			}
		}

		for (int i = 0; i < cells_x; i++)
		{
			delete[] cells[i];
		}

		delete []cells;

	}

	Vector2Int positionToCellIndex(Vector2 pos, Vector2 cellSize)
	{
		Vector2 wrapped = pos.WrapAround(mapSize);
		auto v = Vector2Int(floor(wrapped.x / cellSize.x), floor(wrapped.y / cellSize.y));
		return v;
	}


	bool CheckPhysicsCollide(ColliderComponentData data1, ColliderComponentData data2)
	{
		
		Vector2 position1 = data1.transform->GetWorldPosition();
		Vector2 position2 = data2.transform->GetWorldPosition();

		Vector2 size1 = data1.collider->GetSize();
		Vector2 size2 = data2.collider->GetSize();

		if (isInsideBox(position1 - position2, size2) || isInsideBox(Vector2(position1.x + size1.x, position1.y).WrapAround(mapSize) - position2, size2)
			|| isInsideBox(Vector2(position1.x, size1.y + position1.y).WrapAround(mapSize) - position2, size2)
			|| isInsideBox((position1 + size1).WrapAround(mapSize) - position2, size2))
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

			if ((position1 + size1).x > mapSize.x)
			{
				center1.x -= mapSize.x;
			}
			if ((position1 + size1).y > mapSize.y)
			{
				center1.y -= mapSize.y;
			}
			if ((position2 + size2).x > mapSize.x)
			{
				center2.x -= mapSize.x;
			}
			if ((position2 + size2).y > mapSize.y)
			{
				center2.y -= mapSize.y;
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
			data1.transform->localPosition = data1.transform->localPosition.WrapAround(mapSize);
			data2.transform->localPosition -= shift;
			data2.transform->localPosition = data2.transform->localPosition.WrapAround(mapSize);
		}

		return true;
	}

	bool isInsideBox(Vector2 point, Vector2 size)
	{
		return point.x > 0 && point.y > 0 && point.x < size.x && point.y < size.y;
	}

	void OnShot()
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

			currentActorsToDelete++;

			delete actor;
		}	

		if (spaceShip == nullptr)
		{
			GameOver();
		}

		if (currentActorsToDelete > maxActorsToDelete)
		{ 

			/*auto bindingsMap = world->ResolveFragmentation();

			for (auto actor : actors)
			{
				actor->ResolveComponentsReplacing(bindingsMap);
			}

			printf("DElete\n\n");

			currentActorsToDelete = 0;*/
		}
	}
};

int main(int argc, char *argv[])
{
	Vector2Int windowSize = Vector2Int(800, 600);
	Vector2Int mapSize = Vector2Int(1000, 1000);
	int asteroidsNum = 10;
	int ammoNum = 3;
	float abilityPorbability = 0.3;

	std::vector<int> numbers;

	const char* delim = "xX";
	char* ptr;

	if (argc > 1)
	{
		for (int i = 1; i < argc; i++)
		{
			if (strcmp(argv[i], "-window") == 0)
			{
				i++;

				ptr = strtok(argv[i], delim);

				while (ptr != nullptr)
				{
					numbers.push_back(atoi(ptr));
					ptr = strtok(NULL, delim);

				}

				if (numbers.size() == 2)
				{
					windowSize = Vector2Int(numbers[0], numbers[1]);
				}

				numbers.clear();
			}

			if (strcmp(argv[i], "-map") == 0)
			{
				printf("Enter!\n");

				i++;

				ptr = strtok(argv[i], delim);

				while (ptr != nullptr)
				{
					numbers.push_back(atoi(ptr));
					ptr = strtok(NULL, delim);
				}

				if (numbers.size() >= 2)
				{
					mapSize = Vector2Int(numbers[0], numbers[1]);
				}
				
				numbers.clear();
			}

			if (strcmp(argv[i], "-num_asteroids") == 0)
			{
				i++;
				asteroidsNum = atoi(argv[i]);
			}

			if (strcmp(argv[i], "-num_ammo") == 0)
			{
				i++;
				ammoNum = atoi(argv[i]);
			}

			if (strcmp(argv[i], "-ability_probability") == 0)
			{
				i++;
				abilityPorbability = atof(argv[i]);
			}
		}
	}

	return run(new MyFramework(windowSize, mapSize, asteroidsNum, ammoNum, abilityPorbability));

	return 0;
}
