/************************************************************
Created By Imran Paruk
The ball class creates the functionality for the ball, the
player hits the ball as it moves around the game destroying 
bricks. 
************************************************************/

#include "Ball.h"

//constructor
Ball::Ball(float rad = 0, float sx = 0, float sy = 0, float dx = 0, float dy = 0, bool super = false)
{
	superBall = super;
	radius = rad;
	CenterX = sx;
	CenterY = sy;
	deltaX = dx;
	deltaY = dy;

	ball = al_create_bitmap(radius, radius);
	al_set_target_bitmap(ball);
	al_clear_to_color(al_map_rgb(255, 0, 0));

	if (!ball)
	{
		fprintf(stderr, "Failed to create player bitmap!\n");
	}
}

float Ball::getDelta_X()
{
	return deltaX;
}
float Ball::getDelta_Y()
{
	return deltaY;
}

float Ball::getCenter_X()
{
	return CenterX;
}

float Ball::getCenter_Y()
{
	return CenterY;
}

ALLEGRO_BITMAP *Ball::getBitMap()
{
	return ball;
}

float Ball::getRadius()
{
	return radius;
};
//set the velocity of the ball
void Ball::setVelocity(float dx, float dy)
{
	deltaX = dx;
	deltaY = dy;
}
//make the ball move
void Ball::makeMove()
{
	deltaY += deltaA;
	CenterX += deltaX;
	CenterY += deltaY;
}

//set its acceleration
void Ball::setAccel(float acc)
{
	deltaA = acc;
}

//reflect it about x axis
void Ball::reflectX()
{
	deltaX *= -1;
}

//reflect it about y axis
void Ball::reflectY()
{
	deltaY *= -1;
}

//restart the ball
void Ball::restart(int cx, int cy, float dx, float dy, bool super)
{
	superBall = super;
	CenterX = cx;
	CenterY = cy;
	deltaX = dx;
	deltaY = dy;
}
//draw the ball
void Ball::drawBall(int r, int g, int b)
{
	al_draw_filled_circle(getCenter_X(), getCenter_Y(), getRadius(), al_map_rgb(r, g, b));
}

//are we a superball
bool Ball::isSuperBall()
{
	return superBall;
}

//set it to become a superball, a superball destroys bricks but does not reflect, it also
//destroys super bricks on 1 impact
void Ball::setSuperBall(bool state)
{
	superBall = state;
}

//get the ball velocity
float Ball::getBallVelocity()
{
	return sqrt(pow(deltaX, 2) + pow(deltaY, 2));
}
void Ball::boostVelocity(float factor)
{
	float vel = getBallVelocity()*factor;
	float tempRet = atan(deltaY / deltaX);

	deltaX = vel*cos(tempRet);
	deltaY = vel*sin(tempRet);
}

//get the current angle of the ball
float Ball::getBallAngle()
{
	float tempRet = atan(deltaY / deltaX);
	if (tempRet > 0) return tempRet;
	else return tempRet + PI;
	return tempRet;
}

// this allows the ball to rebound off the player at different angles
void Ball::reboundOffPlayer(float offset)
{
	float tempBallVel = getBallVelocity();
	float tempBallAngle = getBallAngle();

	//just to make sure you the ball goes horizontal
	if (tempBallAngle > 140 * (PI / 180)) offset -= 30 * (PI / 180);
	if (tempBallAngle < 40 * (PI / 180)) offset += 30 * (PI / 180);

	deltaX = tempBallVel*cos(tempBallAngle + offset);
	deltaY = tempBallVel*sin(-(tempBallAngle + offset));
}

