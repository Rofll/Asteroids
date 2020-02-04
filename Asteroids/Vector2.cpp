#include "Vector2.h"

	Vector2::Vector2()
	{
		this->x = 0;
		this->y = 0;
	}

	Vector2::Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2 Vector2::operator+ (Vector2 const& vector)
	{
		return Vector2(this->x + vector.x, this->y + vector.y);
	}

	void Vector2::operator+= (Vector2 const& vector)
	{
		this->x += vector.x;
		this->y += vector.y;
	}

	Vector2 Vector2::operator- (Vector2 const& vector)
	{
		return Vector2(this->x - vector.x, this->y - vector.y);
	}

	Vector2 Vector2::operator* (float const& value)
	{
		return Vector2(this->x * value, this->y * value);
	}

	const Vector2 Vector2::zero = Vector2(0, 0);
	const Vector2 Vector2::one = Vector2(1, 1);
