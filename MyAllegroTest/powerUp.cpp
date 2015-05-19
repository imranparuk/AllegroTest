/************************************************************
Created By Imran Paruk
The powerUp class controls the powerUps, a powerup gives
the user a slight advantage when playing the game. There are 
two Power Ups, one extends the paddel, the other makes the
ball a super ball
************************************************************/


#include <stdio.h>
#include"allegro5/allegro.h"
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <math.h>
#include <cstdlib>
#include "powerUp.h"

// the constructor
powerUp::powerUp(Player* playa, Ball* bala, float sx = 0, float sy = 0, float dy = 0, float ay = 0, float lx = 0, float ly = 0)
{
	srand(time(NULL));

	player = playa;
	ball = bala;

	sizeX = sx;
	sizeY = sy;
	deltaY = dy;
	accelY = ay;
	locationX = lx;
	locationY = ly;
}

//gets x location
float powerUp::getLocationX()
{
	return locationX;
}

//get y location
float powerUp::getLocationY()
{
	return locationY;
}

//getAcceleration y
float powerUp::getAccel()
{
	return accelY;
}

//get velocity y
float powerUp::getDeltaY()
{
	return deltaY;
}

// this allows the powerup to move, the powerup actually accelerates, generating difficulty in the game
void powerUp::makeMove()
{
	if (pUp != NULL)
	{
		deltaY += accelY;
		locationY += deltaY;
	}
}

// sets the player to extend mode
void powerUp::playerPowerUp(Player *Player)
{
	Player->setSuperPlayer(true);
}

// sets the ball into superball
void powerUp::ballPowerUp(Ball *ball)
{
	ball->setSuperBall(true);
}

//This function impliments bounded box collision detection
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
}

//selects the random power ups
void powerUp::selectRandomPowerUp()
{
	// rand (max-min) + min
	int random = rand() % (2) + 1;

	std::cout << "Rand: " << random << std::endl;
	switch (random)
	{
	case 1:
		playerPowerUp(player);
		break;
	case 2:
		ballPowerUp(ball);
		break;
	}

}

powerUp::~powerUp()
{
	al_destroy_bitmap(pUp);
}


