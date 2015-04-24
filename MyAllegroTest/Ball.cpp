#include "Ball.h"

Ball::Ball(float rad = 0, int sx = 0, int sy = 0, float dx = 0, float dy = 0)
{
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

int Ball::getCenter_X()
{
	return CenterX;
}

int Ball::getCenter_Y()
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