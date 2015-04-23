#pragma once
#include <stdio.h>
#include"allegro5/allegro.h"
#include <iostream>


class Brick
{
private:
	const int sizeX;
	const int sizeY;
	const int locationX;
	const int locationY;
	ALLEGRO_BITMAP *brick = NULL;
	

public:
	Brick(int sx, int sy, int lx, int ly) :sizeX(sx), sizeY(sy), locationX(lx), locationY(ly)
	{ 
		brick = al_create_bitmap(sx,sy); 
		al_set_target_bitmap(brick);
		al_clear_to_color(al_map_rgb(125, 246,231));
		fprintf(stderr, "Brick Created!\n");
		if (!brick)
		{
			fprintf(stderr, "Failed to create player bitmap!\n");
			//quit game
		}
	};
	~Brick()
	{
		al_destroy_bitmap(this->brick);
	};

	int getLocX();
	int getLocY();
	int getSizeX();
	int getSizeY();

	ALLEGRO_BITMAP *getBitMap();
};