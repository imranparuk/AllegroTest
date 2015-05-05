#include <stdio.h>
#include"allegro5/allegro.h"
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <math.h>
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
	if (pUp != NULL)
	{
		deltaY += accelY;
		locationY += deltaY;
	}
}

void powerUp::playerPowerUp(Player *Player)
{
	Player->setSuperPlayer(true);
}

void powerUp::ballPowerUp(Ball *ball)
{
	ball->setSuperBall(true);
}


bool powerUp::detectCollision(Player *player)
{

	float temp_dy = abs(deltaY);

	if ((deltaY > 0) && (locationY + sizeY >= player->getLocY()) && (locationY + sizeY <= player->getLocY() + temp_dy) && (locationX + sizeX > player->getLocX()) && (locationX < player->getLocX() + player->getSizeX()))
		return true;
	else
		return false;
		
}

ALLEGRO_BITMAP *powerUp::getBitmap()
{
	return pUp;
}

void powerUp::enableBitmap()
{
		pUp = al_create_bitmap(sizeX, sizeY);
		if (!pUp)
		{
			fprintf(stderr, "Failed to create power up bitmap!\n");
		}

		al_set_target_bitmap(pUp);
		al_clear_to_color(al_map_rgb(255, 0, 0));
		std::cout << "Hello";
}

powerUp::~powerUp()
{
	al_destroy_bitmap(pUp);
}
