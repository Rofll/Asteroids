#pragma once

#include <vector>
#include "Vector2.h"

class Transform
{
public:
	Transform(Transform* parent);
	~Transform();

	Vector2 localPosition;

	Transform* GetParent();

	void SetParent(Transform* parent);

	std::vector<Transform*> GetChilds();

	void AddChild(Transform* child);

	void DetachChild(Transform* child);

	Vector2 GetWorldPosition();

private:
	Transform* parent;

	std::vector<Transform*> childs;
	
};

