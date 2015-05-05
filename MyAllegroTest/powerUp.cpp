#include "powerUp.h"


powerUp::powerUp(float sx = 0, float sy = 0, float dy = 0, float ay = 0, float lx = 0, float ly = 0)
{
	sizeX = sx;
	sizeY = sy;
	deltaY = dy;
	accelY = ay;
	locationX = lx;
	locationY = ly;
}

float powerUp::getLocationX()
{
	return locationX;
}

float powerUp::getLocationY()
{
	return locationY;
}

float powerUp::getAccel()
{
	return accelY;
}

float powerUp::getDeltaY()
{
	return deltaY;
}

void powerUp::makeMove()
{
	deltaY += accelY;
	locationY += deltaY;
}

void powerUp::playerPowerUp(Player *Player)
{
	Player->setSuperPlayer(true);
}




powerUp::~powerUp()
{
	al_destroy_bitmap(pUp);
}
