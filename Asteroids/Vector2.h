#pragma once

struct Vector2
{
	Vector2();
	Vector2(float x, float y);
	Vector2 operator+ (Vector2 const& vector);
	void operator+= (Vector2 const& vector);
	Vector2 operator- (Vector2 const& vector);
	Vector2 operator* (float const& value);

	static const Vector2 zero;
	static const Vector2 one;

	float x;
	float y;
};
