#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <math.h>
#include <iostream>
#include "Brick.h"
#include "ArrayOfBricks.h"
#include "Ball.h"
#include "Player.h"


#define PI 3.14159265359

using namespace std;

const float FPS = 50;
const int SCREEN_W = 640;
const int SCREEN_H = 480;

const int BALL_SIZE_RADIUS = 7;

const int PLAYER_SIZEX = 120;
const int PLAYER_SIZEY = 10;
//const int PLAYER_CENT = PLAYER_SIZEX / 2.0;

const int BRICK_SIZE = 20;

float ballAngle = 0;
float offsetAngle = 0;
float ballVel = 0;
float radAngle = 0;
float awayFromCent = 0;
float reflectionConst = 0;

int score = 0;
int lives = 10;

bool destroyed = false;



enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};


int main(int argc, char **argv)
{
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	//ALLEGRO_BITMAP *player = NULL; //player being created
//	Player player(PLAYER_SIZEX, PLAYER_SIZEY);

	//float player_x = SCREEN_W / 2.0 - PLAYER_SIZEX / 2.0;
	//float player_y = SCREEN_H-70;
	//float player_dx = 0; float player_dy = 0;
	
	bool key[4] = { false, false, false, false };
	bool redraw = true;
	bool doexit = false;

	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	if (!al_install_keyboard()) {
		fprintf(stderr, "failed to initialize the keyboard!\n");
		return -1;
	}

	if (!al_init_primitives_addon())
	{
		fprintf(stderr, "failed to initialize primitives addon!\n");
		return -1;
	}

	timer = al_create_timer(1.0 / FPS);
	if (!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}

	display = al_create_display(SCREEN_W, SCREEN_H);

	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		return -1;
	}


	/*player = al_create_bitmap(PLAYER_SIZEX, PLAYER_SIZEY);//actual player made
	if (!player)
	{
		fprintf(stderr, "Failed to create player bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}*/

	Player player(PLAYER_SIZEX, PLAYER_SIZEY);

	ArrayOfBricks b1(4, 150, 100), b2(6, 100, 125), b3(8, 50, 150,true), b4(6, 100, 175), b5(4, 150, 200);
	ArrayOfBricks level[5] = { b1, b2, b3, b4, b5 };

	Ball ball(BALL_SIZE_RADIUS, player.getLocX() + player.getSizeX() / 2, player.getLocY(), 4, -4, false);




	//al_set_target_bitmap(player);//viewing the player
	//al_clear_to_color(al_map_rgb(255, 0, 255));


	al_set_target_bitmap(al_get_backbuffer(display));

	event_queue = al_create_event_queue();
	if (!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		//al_destroy_bitmap(player);
		//al_destroy_bitmap(ball);
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();
	al_start_timer(timer);

	while (!doexit)
	{
		
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER) {
		
			if (score > 5)
				ball.setSuperBall(true);

			if (key[KEY_LEFT] && player.getLocX() >= 4.0) 
				player.moveLeft();

			if (key[KEY_RIGHT] && player.getLocX() <= SCREEN_W - PLAYER_SIZEX - 4.0) 
				player.moveRight();

			/*if (player_x > SCREEN_W )
			{
				//player_x = 0;
			}

			if (player_x <= 0)
			{
				player_x = SCREEN_W;
			}*/
			
			if (ball.getCenter_Y() > SCREEN_H - ball.getRadius())
			{
				std::cout << "Lives Left: " << --lives << std::endl;
				ball.restart(player.getLocX() + player.getSizeX() / 2, player.getLocY(), 4, -4);
			}

			if ((ball.getCenter_Y() - ball.getRadius()) <= 0 && ball.getDelta_Y() <= 0) 
			{
				ball.reflectY();
			}


			if (((ball.getCenter_X() - ball.getRadius() < 0) && ball.getDelta_X() <= 0) || (ball.getCenter_X() + ball.getRadius() > SCREEN_W && ball.getDelta_X() >= 0) /*|| ((ball_y + BALL_SIZE_RADIUS > player_y) && ((ball_x + BALL_SIZE_RADIUS < player_x) || (ball_x - BALL_SIZE_RADIUS > player_x + PLAYER_SIZEX)))*/) {
				ball.reflectX();
				
			}

			if (player.detectBallCollsion(ball))
			{
				float awayFromCent = player.getLocX() + (player.getSizeX() / 2) - ball.getCenter_X();
				float reflectionConst = (awayFromCent / (player.getSizeX() / 2));

				float offsetAngle = 30 * reflectionConst; //max offset 45 degrees
				float radAngle = (PI / 180)*offsetAngle;

				ball.reboundOffPlayer(radAngle);
			}
			/*
			if ((ball.getCenter_Y() + ball.getRadius() >= player_y) && (ball.getCenter_Y() + ball.getRadius() <= player_y + ball.getDelta_Y()) && (ball.getCenter_X() + ball.getRadius() > player_x) && (ball.getCenter_X() - ball.getRadius() < player_x + PLAYER_SIZEX))
			{

				awayFromCent = player_x + PLAYER_CENT - ball.getCenter_X();
				reflectionConst = (awayFromCent / (PLAYER_CENT));

				offsetAngle = 30*reflectionConst; //max offset 45 degrees
				radAngle = (PI / 180)*offsetAngle;

				ball.reboundOffPlayer(radAngle);
				
				/*
				Ay dont delete this 
				ballVel = ball.getBallVelocity();
				ballAngle = ball.getBallAngle();
				
				std::cout << "Angle: " << ballAngle*(180 / PI) << std::endl;

				float tempdX = ballVel*cos(ballAngle + radAngle);
				float tempdY = ballVel*sin(-(ballAngle + radAngle));
				
				std::cout << "Temps: " << tempdX << " , " << tempdY << std::endl;
				ball.setVelocity(tempdX, tempdY);

				float ballAngle2 = ball.getBallAngle();

				std::cout << "New Angle: " << ballAngle2*(180 / PI) << std::endl;
				*/
		
			//}

			for (int j = 0; j < 5; j++)
			{
				for (int i = 0; i < level[j].getNum(); i++)
				{
					bool checkVer = level[j].arr[i]->detectCollisionVertical(ball.getCenter_X(), ball.getCenter_Y(), ball.getDelta_X(), ball.getDelta_Y(), BALL_SIZE_RADIUS);
					bool checkHor = level[j].arr[i]->detectCollisionHorizontal(ball.getCenter_X(), ball.getCenter_Y(), ball.getDelta_X(), ball.getDelta_Y(), BALL_SIZE_RADIUS);

					if (level[j].arr[i]->getSuperLevel() != 3)//this means the collsion was against a super brick
					{
						if ((checkVer || checkHor) && !level[j].arr[i]->isDestroyed())
						{
							if (ball.isSuperBall()) level[j].arr[i]->setSuperLevel(0);
							if (level[j].arr[i]->getSuperLevel() == 2)
							{
								al_set_target_bitmap(level[j].arr[i]->getBitMap());
								al_clear_to_color(al_map_rgb(0, 100, 255));
								std::cout << "Vertical: " << checkVer << " , Horizontal: " << checkHor << std::endl;
								if (checkVer) ball.reflectY();
								if (checkHor) ball.reflectX();

							}

							if (level[j].arr[i]->getSuperLevel() == 1)
							{
								al_set_target_bitmap(level[j].arr[i]->getBitMap());
								al_clear_to_color(al_map_rgb(125, 246, 231));
								std::cout << "Vertical: " << checkVer << " , Horizontal: " << checkHor << std::endl;

								if (checkVer) ball.reflectY();
								if (checkHor) ball.reflectX();
							}

							if (level[j].arr[i]->getSuperLevel() == 0)
							{
								al_set_target_bitmap(level[j].arr[i]->getBitMap());
								al_clear_to_color(al_map_rgb(0, 0, 0));
								std::cout << "Vertical: " << checkVer << " , Horizontal: " << checkHor << std::endl;

								if (checkVer) ball.reflectY();
								if (checkHor) ball.reflectX();

								level[j].arr[i]->destroy(true);
							}
							al_set_target_bitmap(al_get_backbuffer(display));
							al_flip_display();
						}
					}
					else
					{
						if ((checkVer || checkHor) && !level[j].arr[i]->isDestroyed())
						{
							if (checkVer && !ball.isSuperBall()) ball.reflectY();
							if (checkHor && !ball.isSuperBall()) ball.reflectX();
							level[j].arr[i]->destroy(true);
							al_set_target_bitmap(level[j].arr[i]->getBitMap());
							al_clear_to_color(al_map_rgb(0, 0, 0));
							al_set_target_bitmap(al_get_backbuffer(display));
							al_flip_display();
							std::cout << "Score is : " << ++score << std::endl;
						}
					}
					/*
					if ((checkVer||checkHor) && !level[j].arr[i]->isDestroyed())
					{
					if (checkVer) ball.reflectY();
					if (checkHor) ball.reflectX();
					level[j].arr[i]->destroy(true);
					al_set_target_bitmap(level[j].arr[i]->getBitMap());
					al_clear_to_color(al_map_rgb(0, 0, 0));
					al_set_target_bitmap(al_get_backbuffer(display));
					al_flip_display();
					std::cout << "Score is: " << ++score << std::endl;
					}*/
				}
			}

			
			

			ball.makeMove();
			redraw = true;
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = true;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = true;
				break;

			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = true;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = true;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = false;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = false;
				break;

			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = false;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = false;
				break;

			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;
			}
		}

		if (redraw && al_is_event_queue_empty(event_queue)) {
			
			redraw = false;
		
			al_clear_to_color(al_map_rgb(0, 0, 0));
			//al_draw_bitmap(player, player_x, player_y, 0);
			al_draw_bitmap(player.getBitMap(), player.getLocX(), player.getLocY(), 0);

			for (int j = 0; j < 5; j++)
				for (int i = 0; i < level[j].getNum(); i++)
					al_draw_bitmap(level[j].arr[i]->getBitMap(), level[j].arr[i]->getLocX(), level[j].arr[i]->getLocY(), 0);

			if (ball.isSuperBall())	ball.drawBall(255, 255, 0);
			else ball.drawBall(255, 0, 0);
			al_flip_display();
		}
		
	}

	//al_destroy_bitmap(player);
	//al_destroy_bitmap(ball);
	//destroy brick bitmaps
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}