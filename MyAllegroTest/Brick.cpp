#include "Brick.h"

int Brick::getLocX()
{
	return locationX;
}

int Brick::getLocY()
{
	return locationY;
}

ALLEGRO_BITMAP *Brick::getBitMap()
{
	return brick;
}

int Brick::getSizeX()
{
	return sizeX;
};
int Brick::getSizeY()
{
	return sizeY;
};
//#IMAMADIR
bool Brick::detectCollisionVertical(const int ball_x, const int ball_y, const int ball_dx, const int ball_dy, const int BALL_SIZE_RADIUS)
{
   int temp_dy = abs(ball_dy);

   if ((ball_y + BALL_SIZE_RADIUS >= locationY) && (ball_y + BALL_SIZE_RADIUS <= locationY + temp_dy) && (ball_x /*+ BALL_SIZE_RADIUS*/ > locationX) && (ball_x /*- BALL_SIZE_RADIUS*/ < locationX + sizeX))
		return true;
   else if ((ball_y - BALL_SIZE_RADIUS <= locationY + sizeY) && (ball_y - BALL_SIZE_RADIUS >= locationY + sizeY - temp_dy) && (ball_x /*+ BALL_SIZE_RADIUS*/ > locationX) && (ball_x /*- BALL_SIZE_RADIUS*/ < locationX + sizeX))
		return true;
   else
		return false;

};

bool Brick::detectCollisionHorizontal(const int ball_x, const int ball_y, const int ball_dx, const int ball_dy, const int BALL_SIZE_RADIUS)
{
	int temp_dx = abs(ball_dx);
	int temp_dy = abs(ball_dy);

	if ((ball_x + BALL_SIZE_RADIUS >= locationX) && (ball_x + BALL_SIZE_RADIUS <= locationX + temp_dx) && (ball_y + BALL_SIZE_RADIUS > locationY) && (ball_y - BALL_SIZE_RADIUS < locationY + sizeY))
	   return true;
	else if ((ball_x - BALL_SIZE_RADIUS <= locationX + sizeX) && (ball_x + BALL_SIZE_RADIUS >= locationX + sizeX - temp_dx) && (ball_y + BALL_SIZE_RADIUS > locationY) && (ball_y - BALL_SIZE_RADIUS < locationY + sizeY))
	   return true;
	else
	   return false;

};
bool Brick::isDestroyed()
{
	return destroyed;
};

void Brick::destroy(bool result)
{
	this->destroyed = result;
}


