#pragma once
#include "Header.h"
#include "RessourceManager.h"
#include "Bullet.h"
#include "Character.h"
#include "Weapon.h"
#include "Game.h"
#include "Enemy.h"
#include "Chapter.h"

class Character;
class Enemy;
class Game;
class Bullet;
class Weapon;
class Chapter;


using namespace sf;
using namespace std;


class Gameplay {
private:
	
	vector<Vector2f*> enemiesCenter;
	vector<vector<int>> enemiesHitbox;

	Vector2f debugClosetEnemy = Vector2f(0,0);
	bool debug = false;

	Game& game;

	int weaponLevel = 0;


	
	void loadSprite();
	

	Vector2f getClosestEnemy(Bullet bulletAim);
	Vector2f getAutoAim(Bullet bulletAim, Vector2f targetPos);

	void key_pressed_mgr();
	void create_bullet_mgr();

	void move_enemies();
	void move_player();
	void move_bullets();
	void check_collision();
	void create_bullets(Weapon weapon, bool fromPlayer = true, bool autoAim = false);


	void draw_gameplay();

	vector<RectangleShape> colisions;


public:
	map<string, Weapon> bulletMgr;
	Character player;
	vector<Enemy> enemies;
	vector<Bullet> bullets;
	bool chapterFinish = false;
	Sprite background;
	

	//Gameplay(RenderWindow& windowPointer, Clock& clock);
	Gameplay(Game&game);
	void chapter_run();
	void game_update();
};