#pragma once
#include <stdio.h>
#include"allegro5/allegro.h"
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <math.h>

#define PI 3.14159265359

class Ball
{
private:
	float radius;

	float CenterX;
	float CenterY;

	float deltaX;
	float deltaY;

	float deltaA;
	ALLEGRO_BITMAP *ball = NULL;

	bool superBall;
	bool stop;

public:
	
	Ball(float, float, float, float, float, bool);
	~Ball()
	{
		//al_destroy_bitmap(ball); not working??
	};

	float getCenter_X();
	float getCenter_Y();
	void setCenter(int, int);

	float getDelta_X();
	float getDelta_Y();
	void setVelocity(float , float );

	void setSuperBall(bool);
	bool isSuperBall();

	void setAccel(float);
	void boostVelocity(float);


	void makeMove();
	void reflectY();
	void reflectX();
	void restart(int, int, float, float, bool);
	void drawBall(int, int, int);

	float getBallVelocity();
	float getBallAngle();
	void  reboundOffPlayer(float);

	float getRadius();
	ALLEGRO_BITMAP *getBitMap();

};



