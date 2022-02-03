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
	Sprite createSprite(string textureName, Vector2f size = Vector2f(1.f, 1.f), bool background = false);
	

public:
	void loadTextureChap1();
	void loadSpriteChap1();


	Chapter(Game& game, Gameplay& gameplay);
};
