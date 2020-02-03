#pragma once

class Actor
{
public:
	virtual void Tick() = 0;

protected:
	int xPosition;
	int yPosition;
};

