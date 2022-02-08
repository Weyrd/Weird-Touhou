#pragma once
#include "Header.h"
#include "Character.h"
#include "RessourceManager.h"
#include "Bezier.h"
#include "Game.h"
#include "Gameplay.h"


class Game;
class Gameplay;

class Bullet;


using namespace sf;
using namespace std;



class Chapter {
private:
	

	Game& game;
	Gameplay& gameplay;
	//type_id 0 = sprite; 1 = background; 2 = gameplay background
	Sprite createSprite(string textureName, Vector2f size = Vector2f(1.f, 1.f), int type_id = 0);
	

public:
	void loadfilesChap(int chapter);
	void loadFilesChap1();
	void useRessourcesChap1();


	Chapter(Game& game, Gameplay& gameplay);
};
