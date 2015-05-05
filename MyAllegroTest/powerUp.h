#pragma once
#include <stdio.h>
#include"allegro5/allegro.h"
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <math.h>
#include "Player.h"

class powerUp
{
private:

	float sizeX;
	float sizeY;

	float locationX;
	float locationY;

	float accelY;
	float deltaY;

	ALLEGRO_BITMAP *pUp = NULL;


public:
	powerUp(float, float, float, float, float, float);
	~powerUp();

	float getLocationX();
	float getLocationY();
	void setLocation(int, int);

	float getDeltaY();
	float getAccel();
	void setVelocity(float, float);
	
	void playerPowerUp(Player *);


	void makeMove();
};

