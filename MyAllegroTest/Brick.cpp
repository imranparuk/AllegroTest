#include "Brick.h"

int Brick::getLocX()
{
	return locationX;
}

int Brick::getLocY()
{
	return locationY;
}

ALLEGRO_BITMAP *Brick::getBitMap()
{
	return brick;
}

int Brick::getSizeX()
{
	return sizeX;
};
int Brick::getSizeY()
{
	return sizeY;
};

bool Brick::detectCollision(const int ball_x, const int ball_y, const int BALL_SIZE)
{
	if ((ball_y + BALL_SIZE > locationY) && (ball_y - BALL_SIZE < locationY + sizeY) && (ball_x + BALL_SIZE > locationX) && (ball_x - BALL_SIZE< locationX + sizeX))
		return true;
	else
		return false;

};

bool Brick::isDestroyed()
{
	return destroyed;
};

void Brick::destroy(bool result)
{
	this->destroyed = result;
}


