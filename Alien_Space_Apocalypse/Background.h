#include <iostream>
#include<allegro5/allegro.h>


class Background {
public:
	Background(std::string filename);
	void update();
	void render();
	void dispose();


private:
	int x;
	int y;
	ALLEGRO_BITMAP* backgroundImage;


};