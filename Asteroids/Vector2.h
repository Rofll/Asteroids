#pragma once

struct Vector2
{
	Vector2();
	Vector2(float x, float y);

	Vector2 operator+ (Vector2 const& vector);
	void operator+= (Vector2 const& vector);
	Vector2 operator- (Vector2 const& vector);
	void operator-= (Vector2 const& vector);
	Vector2 operator* (float const& value);
	void operator*= (Vector2 const& value);
	Vector2 operator% (Vector2 const& value);
	void operator%= (Vector2 const& value);
	bool operator== (Vector2 const& value);
	
	void Clamp(Vector2 max);
	float Distance(Vector2 const& vector);
	Vector2 WrapAround(Vector2 const& value);

	Vector2 Normalized();

	static const Vector2 zero;
	static const Vector2 one;

	float x;
	float y;
};

struct Vector2Int
{
	Vector2Int();
	Vector2Int(int x, int y);
	Vector2Int operator+ (Vector2Int const& vector);
	void operator+= (Vector2Int const& vector);
	Vector2Int operator- (Vector2Int const& vector);
	Vector2Int operator* (float const& value);


	static const Vector2Int zero;
	static const Vector2Int one;

	int x;
	int y;
};
