#pragma once
class Ball
{
private:
	int sizeX;
	int sizeY;

	int locationX;
	int locationY;

	int deltaX;
	int deltaY;

	bool destroyed = false;

public:
	Ball();
	~Ball();
};



