#pragma once
#include "Header.h"
#include "Bullet.h"
#include "RessourceManager.h"

class Bullet;

using namespace sf;
using namespace std;




class Pattern {
private:
	Time reload;
	Clock* clock;
	RessourceManager* resMgr;

	Sprite createSprite(string textureName, Vector2f size = Vector2f(1.f, 1.f));
public:
	float offset;
	vector<Bullet> bullets;	
	

	Pattern(vector<Bullet> bullet, Time time);
	Pattern(Bullet bullet, Time time);
	Pattern():clock(new Clock) {};

	int get_reload();
	void restart_reload();


	void create_bullet_chuni_red(RessourceManager* resMgr, float reloadTime = 150);
	void create_ball_glass_blue(RessourceManager* resMgr, float reloadTime = 50);
	void create_ball_glass_red(RessourceManager* resMgr, float reloadTime = 80);

	void create_special_chuni(RessourceManager* resMgr, float reloadTime = 500);
};
