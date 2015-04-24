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
