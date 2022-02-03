#include "Game.h"
#include "Gameplay.h"
#include "Character.h"
#include "Bullet.h"
#include "Lines.h"


using namespace sf;

int get_random(int x, int y) {
	int random = (rand() % (y - x)) + x;
	return random;

}

int main() {
	srand(time(NULL));
	
	/*sf::ContextSettings settings;
	settings.antialiasingLevel = 89;*/
	
	RenderWindow window(VideoMode(1920, 1080), "jsépa");//, settings
	Game game(window);

	game._run();


	return 0;
}