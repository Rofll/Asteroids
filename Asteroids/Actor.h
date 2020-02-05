#pragma once

#include "Transform.h"
#include "AbstractComponent.h"
#include <map>
#include <memory>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>

class Actor
{
public:

	Actor(Transform* parent);
	~Actor();

	template<class T = AbstractComponent>
	T* GetComponent()
	{
		//printf("%s", typeid(components[typeid(T)]).name());

		T* tmp = static_cast<T*>(components[typeid(T)]);

		return tmp;
		//return nullptr;
	}

	template<typename T = AbstractComponent>
	void AddComponent(T* component)
	{
		components[typeid(T)] = component;

		//printf("%s", typeid(component).name());
	}

private:
	std::unordered_map<std::type_index, AbstractComponent*> components;
};