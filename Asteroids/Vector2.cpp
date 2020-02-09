#include "Vector2.h"
#include <cmath>

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

	Vector2 Vector2::Normalized()
	{
		if (x != 0 || y != 0)
		{
			return *this * (1 / sqrt(x * x + y * y));
		}

		else
		{
			return Vector2::one;
		}
	}

	void Vector2::Clamp(Vector2 max)
	{
		if (abs(this->x) > abs(max.x))
		{
			this->x = max.x * (this->x > 0 ? 1: -1);
		}

		if (abs(this->y) > abs(max.y))
		{
			this->y = max.y * (this->y > 0 ? 1 : -1);
		}
	}

	float Vector2::Distance(Vector2 const& vector)
	{
		Vector2 diference = *this - vector;

		return sqrt(diference.x * diference.x + diference.y * diference.y);
	}

	Vector2 Vector2::WrapAround(Vector2 const& value)
	{
		Vector2 vector2 = (*this) % value;
		if (vector2.x < 0)
		{
			vector2.x = value.x + vector2.x;
		}

		if (vector2.y < 0)
		{
			vector2.y = value.y + vector2.y;
		}

		return vector2;
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

	void Vector2::operator-= (Vector2 const& vector)
	{
		this->x -= vector.x;
		this->y -= vector.y;
	}

	Vector2 Vector2::operator- (Vector2 const& vector)
	{
		return Vector2(this->x - vector.x, this->y - vector.y);
	}

	Vector2 Vector2::operator* (float const& value)
	{
		return Vector2(this->x * value, this->y * value);
	}

	void Vector2::operator*= (Vector2 const& value)
	{
		this->x *= value.x;
		this->y *= value.y;
	}

	Vector2 Vector2::operator% (Vector2 const& value)
	{
		return Vector2(fmod(this->x, value.x), fmod(this->y,value.y));
		
	}
	void Vector2::operator%= (Vector2 const& value)
	{
		this->x = fmod(this->x, value.x);
		this->y = fmod(this->y, value.y);
	}

	bool Vector2::operator== (Vector2 const& value)
	{
		if (this->x = value.x && this->y == value.y)
		{
			return true;
		}

		return false;
	}


	const Vector2 Vector2::zero = Vector2(0, 0);
	const Vector2 Vector2::one = Vector2(1, 1);








	Vector2Int::Vector2Int()
	{
		this->x = 0;
		this->y = 0;
	}

	Vector2Int::Vector2Int(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2Int Vector2Int::operator+ (Vector2Int const& vector)
	{
		return Vector2Int(this->x + vector.x, this->y + vector.y);
	}

	void Vector2Int::operator+= (Vector2Int const& vector)
	{
		this->x += vector.x;
		this->y += vector.y;
	}

	Vector2Int Vector2Int::operator- (Vector2Int const& vector)
	{
		return Vector2Int(this->x - vector.x, this->y - vector.y);
	}

	Vector2Int Vector2Int::operator* (float const& value)
	{
		return Vector2Int(this->x * value, this->y * value);
	}

	const Vector2Int Vector2Int::zero = Vector2Int(0, 0);
	const Vector2Int Vector2Int::one = Vector2Int(1, 1);
