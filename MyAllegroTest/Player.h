#pragma once
class Player
{

private:
	int locationX;
	int locationY;

	int sizeX;
	int sizeY;


public:
	Player();
	~Player();

	int getLocX();
	int getLocY();
	int getSizeX();
	int getSizeY();


};

