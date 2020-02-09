#pragma once
#include <unordered_map>
#include <typeindex>
#include "AbstractComponent.h"
#include <map>
class World
{
public:

	template<typename T = AbstractComponent>
	std::vector<AbstractComponent*>* GetComponents()
	{
		return components[typeid(T)];
	}

	std::vector<AbstractComponent*>* GetComponents(std::type_index index)
	{
		return components[index];
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

	void RemoveAllComponents()
	{
		components.erase(components.begin(), components.end());
	}

	std::unordered_map<std::type_index, std::map<int, int>>  ResolveFragmentation()
	{

		std::unordered_map<std::type_index, std::map<int, int>> indexBindings;

		for (auto vector = components.begin(); vector != components.end(); vector++)
		{
			indexBindings[vector->first] = {};

			int counter = 0;
			int reverseIndexer = vector->second->size() - 1;

			for (int i = 0; i < vector->second->size(); i++)
			{
				if (vector->second->at(i) != nullptr)
				{
					continue;
				}

				if (i >= reverseIndexer)
				{
					break;
				}

				while (vector->second->at(reverseIndexer) == nullptr)
				{
					reverseIndexer--;
				
				}

				printf("WorldReplace from: %i to %i in %i\n", reverseIndexer, i, vector->first);

				indexBindings[vector->first][reverseIndexer] = i;

				(*(vector->second))[i] = vector->second->at(reverseIndexer);

				(*(vector->second))[reverseIndexer] = nullptr;

				counter++;

			}

			if (counter > 0)
			{
				vector->second->erase(vector->second->begin() + (vector->second->size() - counter), vector->second->end());

			}
		}

		/*for (auto i = components.begin(); i != components.end(); i++)
		{
			for (auto j = i->second->begin();  j != i->second->end();  j++)
			{
				printf("j == NUll: %i\n", components.at(i)->second.at(j) == nullptr);
			}
		}*/

		return indexBindings;
	}

private:
	std::unordered_map<std::type_index, std::vector<AbstractComponent*>*> components;
};

