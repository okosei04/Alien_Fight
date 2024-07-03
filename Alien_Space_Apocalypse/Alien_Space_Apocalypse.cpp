// Alien_Fight.cpp : Defines the entry point for the application.
//
#include <iostream>
#include<allegro5/allegro.h>
#include<allegro5/allegro_image.h>
#include<allegro5/allegro_primitives.h>


#include "Constants.h"
#include "Game.h"

void update();
void render();
void handle_input();
void dispose();

ALLEGRO_DISPLAY* display = nullptr;
ALLEGRO_EVENT_QUEUE* event_queue = nullptr;
ALLEGRO_TIMER* timer = nullptr;

Game game;

int main() {

	srand(time(0));
	if (!al_init()) return -1;

	display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS); // Shoot 60 times per second

	al_install_keyboard();
	al_install_joystick();
	al_init_image_addon();
	al_init_primitives_addon();

	//Generate game events
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_joystick_event_source());

	bool running = true;
	bool redraw = true;

	game.init();

	al_start_timer(timer);

	while (running) {
		ALLEGRO_EVENT event;
		al_wait_for_event(event_queue, &event);
		switch (event.type) {
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			running = false;
			break;
		case ALLEGRO_EVENT_TIMER:
			handle_input();
			update();
			redraw = true;
			break;
		}

		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;
			render();
		}

	}
	dispose();

	return 0;
}

void update() {
	// Update game state
	game.update();
}
void render() {

	// Clear screen
	al_clear_to_color(al_map_rgb_f(0,0,0));

	//Draw other game objects
	game.render();

	// Draw game state
	al_flip_display();

}
void handle_input() {
	// Handle input
	game.handle_input();
}
void dispose() {

	// Dispose game
	game.dispose();

	// Clean up
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
}


