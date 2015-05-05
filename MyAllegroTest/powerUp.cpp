#include "powerUp.h"


powerUp::powerUp(float sx = 0, float sy = 0, float dy = 0, float ay = 0, float lx = 0, float ly = 0)
{
	sizeX = sx;
	sizeY = sy;
	deltaY = dy;
	accelY = ay;
	locationX = lx;
	locationY = ly;

	pUp = al_create_bitmap(sx, sy);
	//al_set_target_bitmap(ball);
	//al_clear_to_color(al_map_rgb(255, 0, 0));

	if (!pUp)
	{
		fprintf(stderr, "Failed to create power up bitmap!\n");
	}
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

void powerUp::ballPowerUp(Ball *ball)
{
	ball->setSuperBall(true);
}



bool powerUp::detectCollision(Player *Player)
{

	int temp_dy = abs(deltaY);

	if ((deltaY > 0) && (locationY + sizeY >= Player->getLocY()) && (locationY + sizeY <= Player->getLocY() + temp_dy) && (locationX + sizeX > Player->getLocX()) && (locationX < Player->getLocX() +Player->getSizeX()))
	{
		return true;
	}
	else
		return false;

}

ALLEGRO_BITMAP *powerUp::getBitmap()
{
	return pUp;
}

void powerUp::setBitmap(ALLEGRO_BITMAP *bmp)
{
	pUp = bmp;
}

powerUp::~powerUp()
{
	al_destroy_bitmap(pUp);
}
