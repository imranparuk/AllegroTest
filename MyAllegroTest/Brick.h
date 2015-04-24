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
	ALLEGRO_BITMAP *brick = NULL;
	
	
public:
	Brick(int lx=0, int ly=0) :locationX(lx), locationY(ly)
	{ 
		destroyed = false;
		brick = al_create_bitmap(sizeX,sizeY); 
		al_set_target_bitmap(brick);
		al_clear_to_color(al_map_rgb(125, 246, 231));
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
	void destroy(bool result);

	ALLEGRO_BITMAP *getBitMap();

	bool detectCollisionVertical(const int ball_x, const int ball_y, const int ball_dx, const int ball_dy, const int BALL_SIZE_RADIUS);
	bool detectCollisionHorizontal(const int ball_x, const int ball_y, const int ball_dx, const int ball_dy, const int BALL_SIZE_RADIUS);

};