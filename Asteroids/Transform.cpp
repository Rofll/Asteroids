#include "Transform.h"
#include <algorithm>

Transform::Transform(Transform* parent)
{
	SetParent(parent);

	childs = std::vector<Transform*>();

	this->localPosition = Vector2(0, 0);
}

Transform::~Transform()
{
	if (parent != nullptr)
	{
		parent->DetachChild(this);
	}

	parent = nullptr;

	for (int i = 0; i < childs.size(); i++)
	{
		delete childs[i];

		childs[i] = nullptr;
	}
}

void Transform::SetParent(Transform* parent)
{
	if (parent != nullptr)
	{
		parent->AddChild(this);
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

	child->parent = this;
	childs.push_back(child);
}

void Transform::DetachChild(Transform* child)
{
	child->SetParent(nullptr);
	childs.erase(std::remove(childs.begin(), childs.end(), child), childs.end());
}

std::vector<Transform*> Transform::GetChilds()
{
	return childs;
}

Vector2 Transform::GetWorldPosition()
{
	Transform* tmp = parent;
	Vector2 vector = localPosition;

	while (tmp != nullptr)
	{
		vector += tmp->localPosition;
		tmp = tmp->parent;
	}

	return vector;
}