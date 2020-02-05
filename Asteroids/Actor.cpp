#include "Actor.h"

Actor::Actor(Transform* parent)
{
	printf("AAAAAAAAA\n");

	Transform* transform = new Transform(parent);

	AddComponent<Transform>(transform);
}

Actor::~Actor()
{

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