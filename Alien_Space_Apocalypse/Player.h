
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <vector>
#include "Bullet.h"


class Player {

public:
	Player(std::string filename);
	void update();
	void render();
	void dispose();
	void handle_input();
	ALLEGRO_TIMER* recoveryTimer;


	void fireBullet() ;
	float getX() {
		return x;
	}
	float getY() {
		return y;
	}

	float getBoundingCircleRadius() {
		return sqrt(pow(playerWidth / 2, 2) + pow(playerHeight / 2, 2));
	}


	std::vector<Bullet*> getBullets() {
		return bullets;
	}

	void hit() {
		lives--;
		al_start_timer(recoveryTimer);
	}

	bool isDead() {
		return lives <= 0;
	}

	bool isRecovering() {
		return al_get_timer_started(recoveryTimer) > 0;
	}

private:
	// Player state
	float x;
	float y;
	int playerWidth;
	int playerHeight;
	

	//Player lives
	int lives;


	// Player postion
	float dx;
	float dy;
	float speed;
	float angle;

	// movement
	bool left;
	bool right;
	bool up;
	bool down;
	bool fire;

	ALLEGRO_KEYBOARD_STATE keyState;
	ALLEGRO_JOYSTICK_STATE joyState;

	ALLEGRO_BITMAP* playerImage;

	std::vector<Bullet*> bullets;


	ALLEGRO_TIMER* timer;
	
	ALLEGRO_EVENT_QUEUE* event_queue;
	

};