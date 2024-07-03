#pragma once
#include <allegro5/allegro.h>

class Bullet {
public:
	Bullet(float angle, float x, float y);
	void init();
	void update();
	void render();

	float getX() {
		return x;
	}
	float getY() {
		return y;
	}

	float getRadius() {
		return radius;
    }

	bool isAlive() {
		return alive;
	}
	
	void kill() {
		alive = false;
	}
	float to_radians(float angle) {
		return angle * 3.14159 / 180;
	}

	void setColor(ALLEGRO_COLOR color_) {
		color = color_;
	}
	bool remove() {
		return x >= al_get_display_width(al_get_current_display())
			|| x < 0|| y >= al_get_display_height(al_get_current_display()) || y < 0|| !alive;
	}
	
private:
	float angle;
	float x;
	float y;
	float radius;
	float dx;
	float dy;
	float speed;
	bool alive;

	ALLEGRO_COLOR color;
	
	
};