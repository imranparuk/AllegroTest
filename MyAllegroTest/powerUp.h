#pragma once
#include <stdio.h>
#include"allegro5/allegro.h"
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <math.h>
#include "Player.h"
#include "Ball.h"
#include <ctime>

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

	Player *player;
	Ball *ball;

	int numPowerUps = 2;

	bool start = false;


public:
	powerUp(Player*, Ball*, float, float, float, float, float, float);
	~powerUp();

	float getLocationX();
	float getLocationY();
	void setLocation(int, int);

	float getDeltaY();
	float getAccel();
	void setVelocity(float, float);

	void playerPowerUp(Player *);
	void ballPowerUp(Ball *);

	void selectRandomPowerUp();

	bool detectCollision(Player *);

	void makeMove();

	//void setBitmap(ALLEGRO_BITMAP *, bool);
	void enableBitmap();
	ALLEGRO_BITMAP *getBitmap();
};

