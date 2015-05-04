#include "Player.h"

Player::~Player()
{
}

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
	locationY += 7;
};

void Player::detectBallCollsion(Ball ball)
{
	if ((ball.getCenter_Y() + ball.getRadius() >= locationY) && (ball.getCenter_Y() + ball.getRadius() <= locationY + ball.getDelta_Y()) && (ball.getCenter_X() + ball.getRadius() > locationX) && (ball.getCenter_X() - ball.getRadius() < locationX + sizeX))
	{

		float awayFromCent = locationX + centre - ball.getCenter_X();
		float reflectionConst = (awayFromCent / (centre));

		float offsetAngle = 30 * reflectionConst; //max offset 45 degrees
		float radAngle = (PI / 180)*offsetAngle;

		ball.reboundOffPlayer(radAngle);

	}
};

