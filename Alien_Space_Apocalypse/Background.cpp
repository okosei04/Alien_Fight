#include "Background.h"
#include "Constants.h"

Background::Background(std::string filename) {
	x = 0;
	y = 0;

	backgroundImage = al_load_bitmap(filename.c_str());

	if (!backgroundImage) {
		std::cout << "Failed to load background image!" << std::endl;
	}
}

void Background::update() {
	// Update background
	x -= 2;
	if (x < -SCREEN_WIDTH) x = 0;
}



void Background::render() {
	// Draw background

	al_draw_scaled_bitmap(backgroundImage, 0, 0, al_get_bitmap_width(backgroundImage), al_get_bitmap_height(backgroundImage),x, y, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

	al_draw_scaled_bitmap(backgroundImage, 0, 0, al_get_bitmap_width(backgroundImage), al_get_bitmap_height(backgroundImage), SCREEN_WIDTH + x, y, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
}

void Background::dispose() {
	al_destroy_bitmap(backgroundImage);
}

