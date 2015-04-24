#pragma once
#include <stdio.h>
#include"allegro5/allegro.h"
#include <iostream>


class Brick
{
private:
	const int sizeX = 50;
	const int sizeY = 10;
	const int locationX;
	const int locationY;  
	bool destroyed;
	bool super;
	int superLevel;
	ALLEGRO_BITMAP *brick = NULL;//ahmad
	
	
public:
	Brick(int lx=0, int ly=0,bool s = false) :locationX(lx), locationY(ly)
	{ 
		destroyed = false;
		super = s;
		superLevel = 3;
		if (super)
		{
			brick = al_create_bitmap(sizeX, sizeY);
			al_set_target_bitmap(brick);
			al_clear_to_color(al_map_rgb(0, 0, 255));
		}
		else
		{
			brick = al_create_bitmap(sizeX, sizeY);
		al_set_target_bitmap(brick);
		al_clear_to_color(al_map_rgb(125, 246, 231));
		}
		if (!brick)
		{
			fprintf(stderr, "Failed to create player bitmap!\n");
		}
	};
	~Brick()
	{
	};

	int getLocX();
	int getLocY();
	int getSizeX();
	int getSizeY();
	bool isDestroyed();
	int getSuperLevel();

	void destroy(bool result);

	ALLEGRO_BITMAP *getBitMap();

	bool detectCollisionVertical(const int ball_x, const int ball_y, const int ball_dx, const int ball_dy, const int BALL_SIZE_RADIUS);
	bool detectCollisionHorizontal(const int ball_x, const int ball_y, const int ball_dx, const int ball_dy, const int BALL_SIZE_RADIUS);

};