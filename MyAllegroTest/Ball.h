#pragma once
class Ball
{
private:
	int radius;

	int CenterX;
	int CenterY;

	int deltaX;
	int deltaY;

	bool destroyed = false;

public:
	Ball();
	~Ball();
};



