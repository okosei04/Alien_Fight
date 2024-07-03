#pragma once
#include "Game.h"
#include <iostream>



Game::Game() {}

	
void Game::init() {
	// Initialize game objects
	background = new Background("resources/stars.jpg");
	player = new Player("resources/ship2.png");
	
	for (int i = 0; i < 10; i++) {
		villains.push_back(new Villains(3));
		villains.push_back(new Villains(4));
	}
}

void Game::update() {
	// Update game state
	background->update();
	player->update();

	for (auto villain : villains) {
		villain->update(player->getX(), player->getY());
	}

	// Check for collisions
	// Check for bullet-villain collision
	for (auto& Bullet : player->getBullets()) {
		auto bullet_x = Bullet->getX();
		auto bullet_y = Bullet->getY();
		auto bullet_radius = Bullet->getRadius();
		for (auto& villain : villains) {
			auto villain_x = villain->getX();
			auto villain_y = villain->getY();
			auto villain_circle = villain->getBoundingCircleRadius();
			if (check_collision(bullet_x, bullet_y, villain_x, villain_y, bullet_radius, villain_circle)) {
				villain->hit();
				// Remove bullet if it hits a villain
				Bullet->kill();
			}
				
		}
	}

	// Check if player is recovering
	if (player->isRecovering()) {
		if (al_get_timer_count(player->recoveryTimer) >= 3) {
			al_stop_timer(player->recoveryTimer);
		}
	}

	// Check for player-villain collision
	for (auto& villain : villains) {
		auto villain_x = villain->getX();
		auto villain_y = villain->getY();
		auto villain_circle = villain->getBoundingCircleRadius();
		auto player_x = player->getX();
		auto player_y = player->getY();
		auto player_circle = player->getBoundingCircleRadius();
		if (check_collision(villain_x, villain_y, player_x, player_y, villain_circle, player_circle)) {
			player->hit();
			villain->hit();

			if (player->isDead()) {
				/*std::cout << "Game Over" << std::endl;
				exit(0);
				*/
			}
		}
	}
	// Remove dead villains
	for (auto villain = villains.begin(); villain != villains.end(); ) {
		if ((*villain)->isDead()) {
			villain = villains.erase(villain);
		}
		else {
			++villain;
		}
	}


}
  
void Game::render() {
	// Draw game objects
	background->render();
	player->render();
	for (auto& villain : villains) {
		villain->render();
	}

}

void Game::handle_input() {
	// Handle input
	player->handle_input();
}

void Game::dispose() {
	// Dispose game objects
	background->dispose();
	player->dispose();

	for (auto& villain : villains) {
		villain->dispose();
		delete villain;
	}	

	villains.clear();

}
