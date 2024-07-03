#include "Background.h"
#include "Player.h"
#include "Villains.h"
#include <vector>

class Game {
public:
	Game();
	void init();
	void update();
	void render();
	void handle_input();
	void dispose();

	bool check_collision(float x1, float y1, float x2, float y2, float radius1, float radius2) {
		float x = x1 - x2;
		float y = y1 - y2;
		float distance = sqrt(x * x + y * y);

		if (distance <= radius1 + radius2) {
			return true;
		}
		return false;
	}

private:
	// Game state
	Background* background;
	Player* player;

	std::vector<Villains*> villains;

};