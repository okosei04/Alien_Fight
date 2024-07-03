#
#include <iostream>
#include <allegro5/allegro.h>
#include <cmath>
#include <array>
#include <vector>
#include "Bullet.h"
class Villains {
public:
	Villains(int star_);
	void update(float playerX, float playerY);
	void render();
	void dispose();

	float getX() {
		return x;
	}
	float getY() {
		return y;
	}

	float getWidth(){
		return villainWidth;
	}

    float getHeight() {
        return villainHeight;
    }
	float to_radians(float angle) {
		return angle * 3.14159 / 180;
	}

	void hit() {
		lives--;
	}

	bool isDead() {
		return lives <= 0;
	}

	// Calculate the radius of the bounding circle
    float getBoundingCircleRadius() {
        return sqrt(pow(villainWidth / 2, 2) + pow(villainHeight / 2, 2));
    }

	/**
	void set_lives(int lives_) {
		lives = lives_;
	}
	int get_lives() {
		return lives;
	}
	void set_x(int x_) {
		x = x_;
	}
	void set_y(int y_) {
		y = y_;
	}
	int get_x() {
		return x;
	}
	int get_y() {
		return y;
	}
	void set_dx(float dx_) {
		dx = dx_;
	}
	void set_dy(float dy_) {
		dy = dy_;
	}
	float get_dx() {
		return dx;
	}
	float get_dy() {
		return dy;
	}
	void set_angle(float angle_) {
		angle = angle_;
	}
	float get_angle() {
		return angle;
	}
	void set_speed(float speed_) {
		speed = speed_;
	}
	float get_speed() {
		return speed;
	}
	void set_star(float star_) {
		star = star_;
	}
	float get_star() {
		return star;
	}
	void set_VillainsImage(ALLEGRO_BITMAP* VillainsImage_) {
		VillainsImage = VillainsImage_;
	}
	ALLEGRO_BITMAP* get_VillainsImage() {
		return VillainsImage;
	}
	~Villains() {
		al_destroy_bitmap(VillainsImage);
	}
	*/

	


private:
	int x;
	int y;
	int star;
	float speed;

	std::array<std::string, 5> ImagePaths = {"resources/minions.png", "resources/Sub_boss.png", "resources/Boss_1.png", "resources/Boss_2.png", "resorces/Main_Boss.png" };
	float dx;
	float dy;
	float angle;
	float radius;

	float villainWidth;
	float villainHeight;


	int lives;
	
	ALLEGRO_BITMAP* VillainsImage;
	bool isOnScreen;

	std::vector<Bullet*> bullets;
};

