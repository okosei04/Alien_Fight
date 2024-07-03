#include "Villains.h"
#include <iostream>
#include "Constants.h"
#include <allegro5/allegro_primitives.h>



Villains::Villains(int star_) {
	star = star_;
	switch (star) {
	case 1:
		speed = 3;
		lives = 1;
		villainWidth = 120;
		villainHeight = 80;

		break;
	case 2:
		speed = 4;
		lives = 2;
		villainWidth = 130;
		villainHeight = 100;
		break;
	case 3:
		speed = 6;
		lives = 3;
		villainWidth = 160;
		villainHeight = 120;
		
		break;
	case 4:
		speed = 8;
		lives = 6;
		villainWidth = 180;
		villainHeight = 140;
		
		break;
	case 5:
		lives = 10;
		speed = 11;
		villainWidth = 200;
		villainHeight = 160;
		break;
	}
	// Initialize villain state
	x = SCREEN_WIDTH - villainWidth;
	y = SCREEN_HEIGHT / 2;

	
	angle = (rand() % 360) + 1; // Initialize angle before using it
	dx = -(abs(cos(to_radians(angle)) * speed));
	dy = sin(to_radians(angle)) * speed;

	VillainsImage = al_load_bitmap(ImagePaths[star - 1].c_str());
	if (!VillainsImage) {
		std::cerr << "Failed to load villain image from path: " << ImagePaths[star - 1] << std::endl;
	}

    isOnScreen = false;
}

void Villains::update(float playerX, float playerY) {
	x += dx;
	y += dy;

	// Check if the villain is fully on-screen
	if (!isOnScreen && x < SCREEN_WIDTH - villainWidth) {
		isOnScreen = true;
	}
	


	

		if (isOnScreen) {
			// Boundary checks to keep the villain within the screen
			if (x < 0) {
				x = 0; // Adjust position slightly away from the edge
				dx = -dx; // Change direction
			}
			else if (x > SCREEN_WIDTH - villainWidth) {
				x = SCREEN_WIDTH - villainWidth; // Adjust position slightly away from the edge
				dx = -dx; // Change direction
			}

			if (y < 0) {
				y = 0; // Adjust position slightly away from the edge
				dy = -dy; // Change direction
			}
			else if (y > SCREEN_HEIGHT - villainHeight) {
				y = SCREEN_HEIGHT - villainWidth; // Adjust position slightly away from the edge
				dy = -dy; // Change direction
			}
		}

		if (star > 2) {
			int random = rand() % 100;
			if (random == 4) {
				float angle = atan2(playerY - y, playerX - x);
				Bullet* bullet = new Bullet(angle, x + villainWidth / 2, y + villainHeight / 2);
				bullet->setColor(al_map_rgb(255, 0, 0));
				bullets.push_back(bullet);
			}
		}

		for (auto& bullet : bullets) {
			bullet->update();
		}
}

void Villains::render() {
	al_draw_scaled_bitmap(VillainsImage, 0, 0, al_get_bitmap_width(VillainsImage), al_get_bitmap_height(VillainsImage), x, y, villainWidth, villainHeight, 0);

	for (auto& bullet : bullets) {
		bullet->render();
	}
}

void Villains::dispose() {
	al_destroy_bitmap(VillainsImage);
	for (auto& bullet : bullets) {
		delete bullet;
	}
	bullets.clear();
}
