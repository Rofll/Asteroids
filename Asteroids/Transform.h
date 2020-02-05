#pragma once

#include <vector>
#include "Vector2.h"
#include "AbstractComponent.h"

class Transform : public AbstractComponent
{
public:
	explicit Transform(Transform* parent);
	~Transform();

	Vector2 localPosition;

	Transform* GetParent();

	void SetParent(Transform* parent);

	std::vector<Transform*> GetChilds();

	void AddChild(Transform* child);

	void DetachChild(Transform* child);

	Vector2 GetWorldPosition();

protected:
	Transform* parent;

private:
	std::vector<Transform*> childs;
	
};

