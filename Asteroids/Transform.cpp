#include "Transform.h"
#include <algorithm>

Transform::Transform(Transform* parent)
{
	SetParent(parent);

	this->localPosition = Vector2(0, 0);

	childs = std::vector<Transform*>();
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

	childs.clear();
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
	Vector2 vector = Vector2(0, 0);

	while (tmp != nullptr)
	{
		vector += tmp->localPosition;
		tmp = tmp->parent;
	}

	return vector;
}