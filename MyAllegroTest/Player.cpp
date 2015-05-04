#include "Player.h"

int Player::getLocX()
{
	return locationX;
};

int Player::getLocY(){
	return locationY;
};

int Player::getSizeX(){
	return sizeX;
};

int Player::getSizeY(){
	return sizeY;
};

void Player::setSize(int a, int b)
{
	sizeX = a;
	sizeY = b;
};

void Player::moveLeft()
{
	locationX -= 7;
};

void Player::moveRight()
{
	locationX += 7;
};

bool Player::detectBallCollsion(Ball ball)
{
	if ((ball.getCenter_Y() + ball.getRadius() >= locationY) && (ball.getCenter_Y() + ball.getRadius() <= locationY + ball.getDelta_Y()) && (ball.getCenter_X() + ball.getRadius() > locationX) && (ball.getCenter_X() - ball.getRadius() < locationX + sizeX))
	{
		return true;

		//float awayFromCent = locationX + centre - ball.getCenter_X();
		//float reflectionConst = (awayFromCent / (centre));

		//float offsetAngle = 30 * reflectionConst; //max offset 45 degrees
		//float radAngle = (PI / 180)*offsetAngle;

		//ball.reboundOffPlayer(radAngle);
	}
	return false;
};
void Player::setLocationX(int x)
{
	locationX = x;

}
void Player::setLocationY(int y)
{
	locationY = y;
}




ALLEGRO_BITMAP *Player::getBitMap()
{
	return p;
}

