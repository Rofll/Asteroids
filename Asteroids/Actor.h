#pragma once

#include "Transform.h"
#include "AbstractComponent.h"
#include <map>
#include <memory>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <vector>
#include "World.h"

class Actor
{
public:

	Actor(Transform* parent, World* world);
	~Actor();

	template<class T = AbstractComponent>
	T* GetComponent()
	{
		int index = components[typeid(T)];
		T* tmp = static_cast<T*>(world->GetComponents<T>()->at(index));
		return tmp;
	}

	template<typename T = AbstractComponent>
	void AddComponent(T* component)
	{
		if (!world->HasPull<T>())
		{
			world->CreateComponentsPull<T>();
		}
		auto list = world->GetComponents<T>();
		
		list->push_back(component);
		components[typeid(T)] = list->size() - 1;
	}

	template<typename T = AbstractComponent>
	bool HasComponent()
	{
		return components.find(typeid(T)) != components.end();
	}

	template<typename T = AbstractComponent>
	int GetComponentIndex()
	{
		return components[typeid(T)];
	}

	bool IsMarkedAsDestroyed()
	{
		return destroyed;
	}

	void MarkAsDestroyed() 
	{
		destroyed = true;
	}


private:
	World* world;
	bool destroyed = false;
	std::unordered_map<std::type_index, int> components;
};