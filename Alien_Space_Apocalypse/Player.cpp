#include "Player.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include "Constants.h"

Player::Player(std::string filename) {

	// Load player image
	playerImage = al_load_bitmap(filename.c_str());

	if (!playerImage) {
		std::cout << "Failed to load player image!" << std::endl;
	}

	// Initialize player state
	playerHeight = 100;
	playerWidth = 100;
	x = 30;
	y = SCREEN_HEIGHT / 2;

	// Initialize player position
	dx = 0;
	dy = 0;
	speed = 5;
	angle = 0;

	// Initialize movement
	left = false;
	right = false;
	up = false;
	down = false;
	fire = false;


	// Initialize player lives
	lives = 3;

	// Initialize event queue
	event_queue = al_create_event_queue();
	// Initialize timer
	timer = al_create_timer(1.0/5);

	//Recovert timer
	recoveryTimer = al_create_timer(2);

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_timer_event_source(recoveryTimer));


}

void Player::update() {
	// Update player
	if (left) {
		dx = -speed;
	}
	else if (right) {
		dx = speed;
	}
	else {
		dx = 0;
	}
	if (up) {
		dy = -speed;
	}
	else if (down) {
		dy = speed;
	}
	else {
		dy = 0;
	}

	x += dx;
	y += dy;


	// Prevent the player from going out of bounds
	if (x < 0) x = 0; // Left boundary
	if (x > SCREEN_WIDTH - playerWidth) x = SCREEN_WIDTH - playerWidth; // Right boundary
	if (y < 0) y = 0; // Top boundary
	if (y > SCREEN_HEIGHT - playerHeight) y = SCREEN_HEIGHT - playerHeight; // Bottom boundary

	// Handle input
	if (fire) {
		// Check if the timer is started to control bullet firing rate
		if (!al_get_timer_started(timer)) {
			al_start_timer(timer);
		}
	}

	ALLEGRO_EVENT event;
	while (al_get_next_event(event_queue, &event)) {
		if (event.type == ALLEGRO_EVENT_TIMER) {
			// Fire a bullet if the fire condition is true and a timer event occurs
			if (fire) {
				fireBullet();
			}
		}
		else {
				// Stop the timer if the fire condition is false
			al_stop_timer(timer);
		}
	}


	// Remove bullets that are out of bounds
	for (auto& bullet : bullets) {
		bullet->update();
	}

	//Remvoe dead bullets



	for (auto bullet = bullets.begin(); bullet != bullets.end(); ) {
		if ((*bullet)->remove()) {
			bullet = bullets.erase(bullet);
		}
		else {
			++bullet;
		}
	}

}

void Player::fireBullet() {
	bullets.emplace_back(new Bullet(0, x + playerWidth, y + playerHeight / 2));
}

void Player::handle_input() {
	// Handle input
	al_get_keyboard_state(&keyState);
	
	// Check if a joystick is connected before polling its state
	if (al_get_num_joysticks() > 0) {
		ALLEGRO_JOYSTICK* joystick = al_get_joystick(0); // Assuming the first joystick
		al_get_joystick_state(joystick, &joyState);
	}

	//Rotate player through an angel of 30 degrees




	

	// Handle keyboard input and joystick input
	left = al_key_down(&keyState, ALLEGRO_KEY_LEFT) || (al_get_num_joysticks() > 0 && joyState.stick[0].axis[0] < -0.5);
	right = al_key_down(&keyState, ALLEGRO_KEY_RIGHT) || (al_get_num_joysticks() > 0 && joyState.stick[0].axis[0] > 0.5);
	up = al_key_down(&keyState, ALLEGRO_KEY_UP) || (al_get_num_joysticks() > 0 && joyState.stick[0].axis[1] < -0.5);
	down = al_key_down(&keyState, ALLEGRO_KEY_DOWN) || (al_get_num_joysticks() > 0 && joyState.stick[0].axis[1] > 0.5);
	fire = al_key_down(&keyState, ALLEGRO_KEY_SPACE) || (al_get_num_joysticks() > 0 && joyState.button[0]);

	


}

void Player::render() {
	//Check if the player is recovering
	if (al_get_timer_started(recoveryTimer)) {
		//Change the player color to red
		al_draw_tinted_scaled_bitmap(playerImage, al_map_rgb(255, 0, 0), 0, 0, al_get_bitmap_width(playerImage), al_get_bitmap_height(playerImage), x, y, playerWidth, playerHeight, 0);
	}else{
		//Draw player in the middle of the background and sclae it to 50x50
		al_draw_scaled_bitmap(playerImage, 0, 0, al_get_bitmap_width(playerImage), al_get_bitmap_height(playerImage), x, y, playerWidth, playerHeight, 0);
	}
	
	

	// Draw bullets
	for (auto& bullet : bullets) {
		bullet->render();
	}

	// Draw player lives
	for (int i = 0; i < lives; i++) {
		al_draw_scaled_bitmap(playerImage, 0, 0, al_get_bitmap_width(playerImage), al_get_bitmap_height(playerImage), 20 + i * 30, 30, 30, 30, 0);
	}

}

void Player::dispose() {

	// Dispose bullets
	for (auto& bullet : bullets) {
		delete bullet;
	}


	bullets.clear();

	// Dispose player
	al_destroy_bitmap(playerImage);
	al_destroy_timer(timer);
	al_destroy_timer(recoveryTimer);
	al_destroy_event_queue(event_queue);

}