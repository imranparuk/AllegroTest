#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>


#include <math.h>
#include <iostream>
#include <string>

#include "Brick.h"
#include "ArrayOfBricks.h"
#include "Ball.h"
#include "Player.h"
#include "powerUp.h"


#define PI 3.14159265359

using namespace std;

const float FPS = 45;
const int SCREEN_W = 640;
const int SCREEN_H = 480;

const int BALL_SIZE_RADIUS = 7;
const int BALL_VEL = 4;

const int PLAYER_SIZEX = 120;
const int PLAYER_SIZEY = 10;

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
bool demo = false;

int pCount = 0;


enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};


int main(int argc, char **argv)

{

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_SAMPLE *sample = NULL;
	ALLEGRO_SAMPLE *SAMMY = NULL;
	ALLEGRO_SAMPLE *thunder = NULL;


	bool key[4] = { false, false, false, false };
	bool redraw = true;
	bool doexit = false;

	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	if (!al_install_audio()){
		fprintf(stderr, "failed to initialize audio!\n");
		return -1;
	}

	if (!al_init_acodec_addon()) {
		fprintf(stderr, "failed to initialize audio codecs!\n");
		return -1;

	}

	if (!al_reserve_samples(3)){
		fprintf(stderr, "failed to reserve samples!\n");
		return -1;
	}

	sample = al_load_sample("oursound.wav");
	SAMMY = al_load_sample("bloop.wav");
	thunder = al_load_sample("thunder.wav");

	if (!sample) {
		printf("Audio clip sample not loaded!\n");
		return -1;
	}

	if (!SAMMY) {
		printf("Audio clip sample not loaded!\n");
		return -1;
	}

	if (!thunder) {
		printf("Audio clip sample not loaded!\n");
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

	al_play_sample(sample, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);//plays

	if (!al_install_mouse()) {
		fprintf(stderr, "failed to initialize the mouse!\n");
		return -1;
	}

	Player player(PLAYER_SIZEX, PLAYER_SIZEY, PLAYER_SIZEX + 100);
	//Player superPlayer(PLAYER_SIZEX + 100, PLAYER_SIZEY);
restart:
	ArrayOfBricks b1(4, 150, 100), b2(6, 100, 125), b3(8, 50, 150, 0, true), b4(6, 100, 175), b5(4, 150, 200), powerBrick1(1, 320, 70, 1), powerBrick2(1, 320, 230, 1);
	ArrayOfBricks level[7] = { powerBrick1, b1, b2, b3, b4, b5, powerBrick2 };

	al_init_font_addon();
	al_init_ttf_addon();

	ALLEGRO_FONT *font = al_load_ttf_font("CFNuclearWar-Regular.ttf", 32, 0);
	ALLEGRO_FONT *font1 = al_load_ttf_font("CFNuclearWar-Regular.ttf", 72, 0);
	ALLEGRO_FONT *font2 = al_load_ttf_font("CFNuclearWar-Regular.ttf", 30, 0);

	if (!font){
		fprintf(stderr, "Could not load font.\n");
		return -1;
	}


	Ball ball(BALL_SIZE_RADIUS, player.getLocX() + player.getSizeX() / 2, player.getLocY(), BALL_VEL, -BALL_VEL, false);

	if (!al_init_image_addon()) {
		fprintf(stderr, "Failed to initialize image addon!\n");
	}

	const int amountPUps = 2;
	Player *toPlayer = &player;
	Ball *Balla = &ball;


	powerUp powerUp1(toPlayer, Balla, 20, 20, 4, 0.2, level[6].arr[0]->getLocX(), level[6].arr[0]->getLocY());
	powerUp powerUp2(toPlayer, Balla, 20, 20, 4, 0.2, level[0].arr[0]->getLocX(), level[0].arr[0]->getLocY());

	powerUp powerUps[amountPUps] = { powerUp1, powerUp2 };

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
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();
	al_start_timer(timer);


	bool menu = true;

	while (menu)
	{
		int startx = 230;
		int starty = 150;


		al_draw_text(font2, al_map_rgb(255, 0, 40), startx, starty, ALLEGRO_ALIGN_LEFT, "START GAME");
		al_draw_text(font2, al_map_rgb(255, 0, 40), startx, starty + 40, ALLEGRO_ALIGN_LEFT, "DEMO");
		al_draw_text(font2, al_map_rgb(255, 0, 40), startx, starty + 80, ALLEGRO_ALIGN_LEFT, "EXIT");
		al_flip_display();
		ALLEGRO_EVENT ec;
		al_wait_for_event(event_queue, &ec);
		if (ec.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		{
			if (ec.mouse.y >= 150 && ec.mouse.y <= 180 && ec.mouse.x >= startx && ec.mouse.x <= startx + 200)//start game
			{
				menu = false;
			}
			else if (ec.mouse.y > 180 && ec.mouse.y <= 230 && ec.mouse.x >= startx && ec.mouse.x <= startx + 88)//demo
			{
				demo = true;
				menu = false;

			}
			else if (ec.mouse.y > 230 && ec.mouse.y <= 260 && ec.mouse.x >= startx && ec.mouse.x <= startx + 65)//exit
			{
				exit(1);
			}

		}
		if (ec.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			exit(1);
		}

	}
	while (!doexit)
	{

		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER) {


			if (score > 3)
			{

				//ball.setSuperBall(true);
				//player.setSuperPlayer(true);
				//powerUp1.enableBitmap();
			}

			if (key[KEY_LEFT] && !demo)
				player.moveLeft();

			if (key[KEY_RIGHT] && !demo)
				player.moveRight();

			if (demo)
			{
				player.setLocationX(ball.getCenter_X() - player.getSizeX() / 2);
			}

			if (player.getLocX() + 0.5*player.getSizeX() > SCREEN_W  && key[KEY_RIGHT])
			{
				player.setLocationX(0);
			}

			if (player.getLocX() < -0.5*player.getSizeX() && key[KEY_LEFT])
			{
				player.setLocationX(SCREEN_W);
			}

			if (ball.getCenter_Y() > SCREEN_H - ball.getRadius())
			{
				//std::cout << "Lives Left: " << --lives << std::endl;
				lives--;
				al_play_sample(thunder, 2, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

				player.setSuperPlayer(false);
				ball.restart(player.getLocX() + player.getSizeX() / 2, player.getLocY(), BALL_VEL, -BALL_VEL, false);

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


			for (int i = 0; i < amountPUps; i++)
			{
				if (powerUps[i].detectCollision(toPlayer))
				{
					powerUps[i].selectRandomPowerUp();
					//powerUp1.ballPowerUp(&ball);
					//powerUp1.playerPowerUp(&player);
				}
			}


			/*
			Ay dont delete this (original player code)
			ballVel = ball.getBallVelocity();
			ballAngle = ball.getBallAngle();

			std::cout << "Angle: " << ballAngle*(180 / PI) << std::endl;

			float tempdX = ballVel*cos(ballAngle + radAngle);
			float tempdY = ballVel*sin(-(ballAngle + radAngle));
			s
			std::cout << "Temps: " << tempdX << " , " << tempdY << std::endl;
			ball.setVelocity(tempdX, tempdY);

			float ballAngle2 = ball.getBallAngle();

			std::cout << "New Angle: " << ballAngle2*(180 / PI) << std::endl;
			*/

			//cleaning code here
			for (int j = 0; j < 8; j++)
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

								//if (!al_init_image_addon()) {
								//fprintf(stderr, "Failed to initialize image addon!\n");
								//}

								level[j].arr[i]->brick = al_load_bitmap("second.bmp");
								al_draw_bitmap(level[j].arr[i]->getBitMap(), level[j].arr[i]->getLocX(), level[j].arr[i]->getLocY(), 0);
								//al_set_target_bitmap(level[j].arr[i]->getBitMap());
								//al_clear_to_color(al_map_rgb(0, 100, 255));
								//std::cout << "Vertical: " << checkVer << " , Horizontal: " << checkHor << std::endl;
								if (checkVer) ball.reflectY();
								if (checkHor) ball.reflectX();

							}

							if (level[j].arr[i]->getSuperLevel() == 1)
							{
								level[j].arr[i]->brick = al_load_bitmap("final.bmp");
								al_draw_bitmap(level[j].arr[i]->getBitMap(), level[j].arr[i]->getLocX(), level[j].arr[i]->getLocY(), 0);
								//al_set_target_bitmap(level[j].arr[i]->getBitMap());
								//al_clear_to_color(al_map_rgb(125, 246, 231));
								//std::cout << "Vertical: " << checkVer << " , Horizontal: " << checkHor << std::endl;

								if (checkVer) ball.reflectY();
								if (checkHor) ball.reflectX();
							}

							if (level[j].arr[i]->getSuperLevel() == 0)
							{

								for (int k = 1; k < 10; k++)
								{
									string num = to_string(k);
									string naam = "ani" + num + ".bmp";
									level[j].arr[i]->brick = al_load_bitmap(naam.c_str());
									al_draw_bitmap(level[j].arr[i]->getBitMap(), level[j].arr[i]->getLocX(), level[j].arr[i]->getLocY(), 0);
									//al_rest(0.0001);
								}

								//al_set_target_bitmap(level[j].arr[i]->getBitMap());
								//al_clear_to_color(al_map_rgb(0, 0, 0));
								std::cout << "Vertical: " << checkVer << " , Horizontal: " << checkHor << std::endl;

								if (checkVer) ball.reflectY();
								if (checkHor) ball.reflectX();
								score++;
								al_play_sample(SAMMY, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);//plays

								level[j].arr[i]->destroy(true);
							}
							al_set_target_bitmap(al_get_backbuffer(display));
							al_flip_display();
						}
					}
					else
					{
						if ((checkVer || checkHor) && !level[j].arr[i]->isDestroyed() && !level[j].arr[i]->isPowerUp())
						{
							if (checkVer && !ball.isSuperBall()) ball.reflectY();
							if (checkHor && !ball.isSuperBall()) ball.reflectX();
							level[j].arr[i]->destroy(true);

							for (int k = 1; k < 10; k++)
							{
								string num = to_string(k);
								string naam = "ani" + num + ".bmp";
								level[j].arr[i]->brick = al_load_bitmap(naam.c_str());
								al_draw_bitmap(level[j].arr[i]->getBitMap(), level[j].arr[i]->getLocX(), level[j].arr[i]->getLocY(), 0);
								//al_rest(0.0001);
							}
							al_play_sample(SAMMY, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);//plays

							//al_set_target_bitmap(level[j].arr[i]->getBitMap());
							//al_clear_to_color(al_map_rgb(0, 0, 0));
							al_set_target_bitmap(al_get_backbuffer(display));
							al_flip_display();
							score++;
						}
					}

					if ((checkVer || checkHor) && !level[j].arr[i]->isDestroyed() && level[j].arr[i]->isPowerUp())
					{
						if (checkVer && !ball.isSuperBall()) ball.reflectY();
						if (checkHor && !ball.isSuperBall()) ball.reflectX();
						level[j].arr[i]->destroy(true);

						int xPos = ball.getCenter_X();
						int yPos = ball.getCenter_Y();
						Brick *temp = level[j].arr[i];

						al_play_sample(SAMMY, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);//plays

						al_set_target_bitmap(level[j].arr[i]->getBitMap());
						al_clear_to_color(al_map_rgb(0, 0, 0));
						//powerUp1.enableBitmap();

						powerUps[pCount].enableBitmap();

						pCount++;
						al_set_target_bitmap(al_get_backbuffer(display));
						al_flip_display();
						score++;

						//std::cout << "Score is : " << ++score << std::endl;
					}

				}
			}



			//powerUp1.makeMove();

			for (int i = 0; i < amountPUps; i++)
			{
				powerUps[i].makeMove();
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

			/*if (player.isSuperPlayer())
			{
			player.setBitMap(superPlayer.getBitMap());
			player.setSize(superPlayer.getSizeX(), superPlayer.getSizeY());
			}*/
			al_clear_to_color(al_map_rgb(0, 0, 0));
			//al_draw_bitmap(player, player_x, player_y, 0);
			al_draw_bitmap(player.getBitMap(), player.getLocX(), player.getLocY(), 0);

			for (int i = 0; i < amountPUps; i++)
			{
				if (powerUps[i].getBitmap() != NULL)
					al_draw_bitmap(powerUps[i].getBitmap(), powerUps[i].getLocationX(), powerUps[i].getLocationY(), 0);
			}

			string scoretxt = to_string(score);
			string livestxt = to_string(lives);
			ALLEGRO_COLOR grey = al_map_rgb(100, 100, 100);

			al_draw_text(font, grey, 100, 5, ALLEGRO_ALIGN_CENTRE, "SCORE: ");
			al_draw_text(font, grey, 170, 5, ALLEGRO_ALIGN_CENTRE, scoretxt.c_str());
			al_draw_text(font, al_map_rgb(255, 0, 40), 300, 5, ALLEGRO_ALIGN_CENTRE, "LIVES: ");
			al_draw_text(font, al_map_rgb(255, 0, 40), 400, 5, ALLEGRO_ALIGN_CENTRE, livestxt.c_str());
			if (score == 30)
			{
				al_draw_text(font1, al_map_rgb(255, 0, 40), 320, 240, ALLEGRO_ALIGN_CENTRE, "LEVEL CLEAR");
				al_flip_display();
				score = 0;
				lives = 10;
				al_rest(2.0);

				goto restart;
			}
			if (lives == 0)
			{
				al_draw_text(font1, al_map_rgb(255, 0, 40), 320, 240, ALLEGRO_ALIGN_CENTRE, "GAMEOVER");
				al_flip_display();
				al_rest(2.0);
				exit(1);
			}
			for (int j = 0; j < 7; j++)
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
	al_destroy_font(font);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_sample(sample);

	return 0;
}