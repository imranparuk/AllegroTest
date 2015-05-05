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

	int superSizeX;
	int normSizeX;

	int sizeX;
	int sizeY;

	int centre = sizeX / 2;

	ALLEGRO_BITMAP *p = NULL;
	ALLEGRO_BITMAP *s = NULL;

	bool superPlayer = false;
	
public:
	Player(int sX, int sY, int supX)
	{ 
		normSizeX = sX;
		superSizeX = supX;

		sizeX = sX; 
		sizeY = sY; 

		p = al_create_bitmap(sizeX, sizeY);//actual player made
		al_set_target_bitmap(p);//viewing the player
		al_clear_to_color(al_map_rgb(255, 0, 255));

		s = al_create_bitmap(superSizeX, sizeY); // da superPlayer (PowerUp)
		al_set_target_bitmap(s);//viewing the player
		al_clear_to_color(al_map_rgb(45, 45, 45));

		if (!p || !s)
		{
			fprintf(stderr, "Failed to create player bitmap!\n");
		}
	};

	~Player()
	{
		al_destroy_bitmap(p);
		al_destroy_bitmap(s);
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

	void setSuperPlayer(bool);
	bool isSuperPlayer();
	
	ALLEGRO_BITMAP *Player::getBitMap();
	void setBitMap(ALLEGRO_BITMAP*);

};

