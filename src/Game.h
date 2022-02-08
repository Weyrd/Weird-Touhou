#pragma once
#include "Header.h"
#include "RessourceManager.h"
#include "Gameplay.h"
#include "Menu.h"



class Gameplay;

using namespace sf;
using namespace std;


class Game {
	

private:
	Clock clock;
	int framerate;
	
	

	void loadTexture();
	Sprite createSprite(string textureName);

public:
	RenderWindow& window;
	RessourceManager resMgr;


	int chapter = 1;
	bool in_game = false;
	float volumeMusic = 0;
	float volumeSFX = 40;

	Text info;

	Event event;

	Game(RenderWindow & windowPost);
	void _run();
	void loadFonts();
	void fps_update(int numberBullets, int numberEnnemies);
};
