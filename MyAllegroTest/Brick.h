#pragma once
#include <stdio.h>
#include"allegro5/allegro.h"
#include"allegro5/allegro_image.h"
#include <iostream>


class Brick
{
private:
	const int sizeX = 60;
	const int sizeY = 15;
	const int locationX;
	const int locationY;  
	bool destroyed;
	bool super;
	int superLevel;
	int puBrick;
//	ALLEGRO_BITMAP *brick = NULL;
	
	
public:
	ALLEGRO_BITMAP *brick = NULL;

	Brick(int lx=0, int ly=0,int pU = 0, bool s = false) :locationX(lx), locationY(ly)
	{ 
		destroyed = false;
		super = s;
		superLevel = 3;
		puBrick = pU;
		if (super)
		{
			if (!al_init_image_addon()) {
				fprintf(stderr, "Failed to initialize image addon!\n");
			}
			brick = al_load_bitmap("super.bmp");
			al_draw_bitmap(brick, locationX, locationY, 0);
			//brick = al_create_bitmap(sizeX, sizeY);
			//al_set_target_bitmap(brick);
			al_clear_to_color(al_map_rgb(0, 0, 255));
		}
		else
		{
			if (!al_init_image_addon()) {
				fprintf(stderr, "Failed to initialize image addon!\n");
			}
			brick = al_load_bitmap("final.bmp");
			al_draw_bitmap(brick, locationX, locationY,0);
			//brick = al_create_bitmap(sizeX, sizeY);
			//al_set_target_bitmap(brick);
			//al_clear_to_color(al_map_rgb(125, 246, 231));
		}
		if (!brick)
		{
			fprintf(stderr, "Failed to create player bitmap!\n");
		}

	};
	~Brick()
	{
		al_destroy_bitmap(brick);
	};

	int getLocX();
	int getLocY();
	int getSizeX();
	int getSizeY();
	bool isPowerUp();
	bool isDestroyed();
	int getSuperLevel();
	void setSuperLevel(int);
	//void setBitmap(ALLEGRO_BITMAP );

	void destroy(bool result);

	ALLEGRO_BITMAP *getBitMap();

	bool detectCollisionVertical(const int ball_x, const int ball_y, const int ball_dx, const int ball_dy, const int BALL_SIZE_RADIUS);
	bool detectCollisionHorizontal(const int ball_x, const int ball_y, const int ball_dx, const int ball_dy, const int BALL_SIZE_RADIUS);

};