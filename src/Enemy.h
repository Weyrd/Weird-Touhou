#pragma once
#include "Header.h"
#include "Character.h"
#include "RessourceManager.h"
#include "Bezier.h"
#include "Path.h"
#include "Pattern.h"

class Character;

using namespace sf;
using namespace std;



class Enemy
{
private:
	Time reload;
	Clock* clock;
	RessourceManager* resMgr;

	Sprite createSprite(string textureName, Vector2f size = Vector2f(1.f, 1.f));
public:
	vector<Character> enemies;

	int currentPath = 0; 
	vector<Path> allPath;
	

	int timePatterBullets;
	String name = "unknown";

	Vector2f startEnemyPosition;

	Enemy() :clock(new Clock) {};

	int get_time();
	void restart_reload();
	void set_current_path();

	void cirno(RessourceManager* resMgr);
	void brown_pattern1(RessourceManager* resMgr);

};




//get tiume %temp pattern == temreload