#pragma once
#include <unordered_map>
#include <typeindex>
#include "AbstractComponent.h"
class World
{
public:

	template<typename T = AbstractComponent>
	std::vector<AbstractComponent*>* GetComponents()
	{
		return components[typeid(T)];
	}

	template<typename T = AbstractComponent>
	void CreateComponentsPull()
	{
		components[typeid(T)] = new std::vector<AbstractComponent*>();
	}

	template<typename T = AbstractComponent>
	bool HasPull()
	{
		return components.find(typeid(T)) != components.end();
	}

private:
	std::unordered_map<std::type_index, std::vector<AbstractComponent*>*> components;
};

