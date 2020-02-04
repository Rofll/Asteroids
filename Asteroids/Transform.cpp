#include "Transform.h"

Transform::Transform(Transform* parent)
{
	SetParent(parent);

	this->localPosition = Vector2(0, 0);

	childs = std::vector<Transform*>();
}

Transform::~Transform()
{
	
}

void Transform::SetParent(Transform* parent)
{
	if (parent != nullptr)
	{
		this->parent->AddChild(this);
	}

	else
	{
		this->parent = nullptr;
	}
}

Transform* Transform::GetParent()
{
	return parent;
}

void Transform::AddChild(Transform* child)
{
	if (child->parent == this)
	{ 
		return;
	}

	child->SetParent(this);
	childs.push_back(child);
}

void Transform::DetachChild(Transform* child)
{
	for (int i = 0; i < childs.size(); i++)
	{
		if (childs[i] == child)
		{
			child->SetParent(nullptr);
			childs.erase(childs.begin() + i);
			break;
		}
	}
}

std::vector<Transform*> Transform::GetChilds()
{
	return childs;
}

Vector2 Transform::GetWorldPosition()
{
	Transform* tmp = parent;
	Vector2 vector = Vector2(0, 0);

	while (tmp != nullptr)
	{
		vector += tmp->localPosition;
		tmp = tmp->parent;
	}

	return vector;
}