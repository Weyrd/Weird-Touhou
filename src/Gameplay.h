#pragma once
#include "Header.h"
#include "RessourceManager.h"
#include "Bullet.h"
#include "Character.h"
#include "Pattern.h"
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
	float score = 0;

	Game& game;

	int weaponLevel = 0;
	Text displayLife;
	Text displayScore;
	Text displayPower;

	
	void loadSprite();
	

	Vector2f getClosestEnemy(Bullet bulletAim);
	Vector2f getAutoAim(Bullet bulletAim, Vector2f targetPos);

	void key_pressed_mgr();
	void create_bullet_mgr();

	void move_enemies();
	void move_player();
	void move_bullets();
	void enemy_patterns();
	void check_collision();
	


	void draw_gameplay();
	void displayInfo_update();
	void pause_open_menu();

	vector<RectangleShape> colisions;


public:
	map<int, Sound> bulletSoundMgr;
	map<string, Pattern> bulletMgr;
	Character player;
	vector<Enemy> enemies;
	vector<Bullet> bullets;
	bool chapterFinish = false;
	bool pause = false;

	Sprite background;
	Sprite gameplay_background;

	Sound music;
	Sound volumeSFX;
	

	//Gameplay(RenderWindow& windowPointer, Clock& clock);
	void create_bullets_player(Pattern weapon, bool autoAim = false);
	void create_bullets_ennemy(Pattern weapon, Vector2f enemy, bool autoAim = false);
	Gameplay(Game&game);
	void chapter_run();
	void game_update();
};