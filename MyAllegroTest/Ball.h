#pragma once
#include <stdio.h>
#include"allegro5/allegro.h"
#include <allegro5/allegro_primitives.h>
#include <iostream>

class Ball
{
private:
	float radius;

	int CenterX;
	int CenterY;

	float deltaX;
	float deltaY;
	ALLEGRO_BITMAP *ball = NULL;

public:
	Ball(float, int, int, float, float);
	~Ball();

	int getCenter_X();
	int getCenter_Y();
	void setCenter(int, int);

	float getDelta_X();
	float getDelta_Y();
	void setVelocity(float , float );

	void makeMove();
	void reflectY();
	void reflectX();
	void restart(int, int, float, float);

	float getRadius();
	ALLEGRO_BITMAP *getBitMap();

};



