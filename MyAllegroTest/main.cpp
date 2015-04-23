#include <stdio.h>
#include <allegro5/allegro.h>
#include <iostream>
#include"Brick.h"
#include"ArrayOfBricks.h"


using namespace std;

const float FPS = 60;
const int SCREEN_W = 640;
const int SCREEN_H = 480;
const int BALL_SIZE = 20;

const int PLAYER_SIZEX = 100;
const int PLAYER_SIZEY = 10;

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
	ALLEGRO_BITMAP *ball = NULL;
	ALLEGRO_BITMAP *player = NULL;

	float player_x = SCREEN_W / 2.0 - PLAYER_SIZEX / 2.0;
	float player_y = SCREEN_H-100;
	float player_dx = 0; float player_dy = 0;

	float ball_x = 60;
	float ball_y = 60;
	float ball_dx = -4.0, ball_dy = 4.0;

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

	ball = al_create_bitmap(BALL_SIZE, BALL_SIZE);
	if (!ball) {
		fprintf(stderr, "failed to create bouncer bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	player = al_create_bitmap(PLAYER_SIZEX, PLAYER_SIZEY);
	if (!player)
	{
		fprintf(stderr, "Failed to create player bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	Brick brick(500, 300);
	if (!brick.getBitMap())
	{
		fprintf(stderr, "Failed to create brick!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
	} 

	ArrayOfBricks b(10, 100, 100);


	al_set_target_bitmap(player);
	al_clear_to_color(al_map_rgb(255, 0, 255));

	al_set_target_bitmap(ball);
	al_clear_to_color(al_map_rgb(50, 50, 50));

	al_set_target_bitmap(al_get_backbuffer(display));

	event_queue = al_create_event_queue();
	if (!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_bitmap(player);
		al_destroy_bitmap(ball);
		al_destroy_display(display);
		brick.~Brick();
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
			if (key[KEY_LEFT] && player_x >= 4.0) {
				player_x -= 4.0;
			}

			if (key[KEY_RIGHT] && player_x <= SCREEN_W - PLAYER_SIZEX - 4.0) {
				player_x += 4.0;
			}
			if (ball_y > SCREEN_H - BALL_SIZE)
			{
				std::cout << "Lives Left: " << --lives;
				ball_x = 100;
				ball_y = 100;
				ball_dx = 4;
				ball_dy = -4;
			}

			if (ball_x < 0 || ball_x > SCREEN_W - BALL_SIZE) {
				ball_dx = -ball_dx;
			}


			if ((ball_y < 0) || ((ball_y+BALL_SIZE> player_y) && (ball_y<player_y+PLAYER_SIZEY) && (ball_x+BALL_SIZE> player_x) && (ball_x <player_x + PLAYER_SIZEX))) {
				ball_dy = -ball_dy;
			}

			if (!(destroyed) && (ball_y + BALL_SIZE > brick.getLocY()) && (ball_y < brick.getLocY() + brick.getSizeY()) && (ball_x + BALL_SIZE > brick.getLocX()) && (ball_x < brick.getLocX() + brick.getSizeY()))
			{
				destroyed = true;
				ball_dx *= -1;
				ball_dy *= -1;
				al_set_target_bitmap(brick.getBitMap());
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_set_target_bitmap(al_get_backbuffer(display));
				al_flip_display();
				std::cout << "Score is 1: " << ++score;
			}

			for (int i = 0; i < 10; i++)
			{
				bool check = b.arr[i]->detectCollision(ball_x,ball_y,BALL_SIZE);
				if (check && !b.arr[i]->isDestroyed())
				{
					b.arr[i]->destroy(true);
					ball_dx *= -1;
					ball_dy *= -1;
					al_set_target_bitmap(b.arr[i]->getBitMap());
					al_clear_to_color(al_map_rgb(0, 0, 0));
					al_set_target_bitmap(al_get_backbuffer(display));
					al_flip_display();
					std::cout << "Score is 1: " << ++score;
				}
			}
	
			ball_x += ball_dx;
			ball_y += ball_dy;

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
			al_draw_bitmap(brick.getBitMap(), brick.getLocX(), brick.getLocY(), 0);
			for (int i = 0; i < 10; i++)
				al_draw_bitmap(b.arr[i]->getBitMap(),b.arr[i]->getLocX(),b.arr[i]->getLocY(),0);
			al_draw_bitmap(player, player_x, player_y, 0);
			al_draw_bitmap(ball, ball_x, ball_y, 100);
			al_flip_display();
		}
	}

	al_destroy_bitmap(player);
	al_destroy_bitmap(ball);
	//brick.~Brick();
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}