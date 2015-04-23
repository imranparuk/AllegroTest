#pragma once
class Brick
{
private:
	int sizeX;
	int sizeY;
	int locationX;
	int locationY;


public:
	Brick();
	~Brick();

	void setLocation();
	void getLocation(int &, int &);


};

