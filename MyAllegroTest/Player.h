#pragma once
#include <stdio.h>
#include "Ball.h"
#include"allegro5/allegro.h"
#include <iostream>

class Player
{
	const int SCREEN_W = 640;
	const int SCREEN_H = 480;

private:
	int locationX = SCREEN_W / 2.0 - sizeX / 2.0;
	int locationY = SCREEN_H - 70;

	int sizeX;
	int sizeY;

	int centre = sizeX / 2;

	ALLEGRO_BITMAP *p = NULL;
	
public:
	Player(int sX, int sY)
	{ 
		sizeX = sX; 
		sizeY = sY; 

		p = al_create_bitmap(sizeX, sizeY);//actual player made
		al_set_target_bitmap(p);//viewing the player
		al_clear_to_color(al_map_rgb(255, 0, 255));
		if (!p)
		{
			fprintf(stderr, "Failed to create player bitmap!\n");
		}
	};

	~Player()
	{
		al_destroy_bitmap(p);
	};

	int getLocX();
	int getLocY();
	int getSizeX();
	int getSizeY();

	void setSize(int , int );
	void moveLeft();
	void moveRight();

	void setLocationX(int);
	void setLocationY(int);
	bool detectBallCollsion(Ball );

	ALLEGRO_BITMAP *Player::getBitMap();

};

