#include "Actor.h"

Actor::Actor(Transform* parent, World* world)
{
	this->world = world;

	Transform* transform = new Transform(parent);
	
	AddComponent<Transform>(transform);

}

Actor::~Actor()
{
	if (components.empty())
	{
		return;
	}

	for (auto it = components.begin(); it != components.end(); ++it)
	{
		auto worldComponents = world->GetComponents(it->first);

		delete (worldComponents->at(it->second));

		(*worldComponents)[it->second] = nullptr;


		//printf("\nDeleted: %i %i\n", it->second, it->first);

		//worldComponents->erase(worldComponents->begin() + it->second);
	}
}

//template<class T>
//T* Actor::GetComponent()
//{
//	printf("WTF!!!");
//	//printf("%s", typeid(components[typeid(T)]).name());
//	return (components[typeid(T)]);
//	//return nullptr;
//}
//
//template<class T>
//void Actor::AddComponent(T* component)
//{
//	components[typeid(T)] = component;
//
//	printf("%s", typeid(component).name());
//}