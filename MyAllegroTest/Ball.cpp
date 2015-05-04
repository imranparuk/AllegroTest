#include "Ball.h"

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


Ball::~Ball()
{
}

float Ball::getCenter_X()
{
	return CenterX;
}

float Ball::getCenter_Y()
{
	return CenterY;
}

void Ball::setCenter(int ax, int ay)
{
	CenterX = ax;
	CenterX = ay;
}

float Ball::getDelta_X()
{
	return deltaX;
}

float Ball::getDelta_Y()
{
	return deltaY;
}

ALLEGRO_BITMAP *Ball::getBitMap()
{
	return ball;
}

float Ball::getRadius()
{
	return radius;
};

void Ball::setVelocity(float dx, float dy)
{
	deltaX = dx;
	deltaY = dy;
}

void Ball::makeMove()
{
	CenterX += deltaX;
	CenterY += deltaY;
}

void Ball::reflectX()
{
	deltaX *= -1;
}

void Ball::reflectY()
{
	deltaY *= -1;
}

void Ball::restart(int cx, int cy, float dx, float dy)
{
	CenterX = cx;
	CenterY = cy;
	deltaX = dx;
	deltaY = dy;
}

void Ball::drawBall(int r, int g, int b)
{
	al_draw_filled_circle(getCenter_X(), getCenter_Y(), getRadius(), al_map_rgb(r, g, b));
}

bool Ball::isSuperBall()
{
	return superBall;
}

void Ball::setSuperBall(bool state)
{
	superBall = state;
}

float Ball::getBallVelocity()
{
	return sqrt(pow(deltaX, 2) + pow(deltaY, 2));
}

float Ball::getBallAngle()
{
	float tempRet = atan(deltaY / deltaX);
	if (tempRet > 0) return tempRet;
	else return tempRet + PI;
	return tempRet;
}

void Ball::reboundOffPlayer(float offset)
{
	float tempBallVel = getBallVelocity();
	float tempBallAngle = getBallAngle();

	if (tempBallAngle > 140 * (PI / 180)) offset -= 30 * (PI / 180);
	if (tempBallAngle < 40 * (PI / 180)) offset += 30 * (PI / 180);

	deltaX = tempBallVel*cos(tempBallAngle + offset);
	deltaY = tempBallVel*sin(-(tempBallAngle + offset));
}