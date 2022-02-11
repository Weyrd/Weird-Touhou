#pragma once
#include "Weapon.h"
#include "Bullet.h"

Weapon::Weapon(Bullet bulletW, Time time)
	:clock(new Clock) {

	this->reload = time;
	this->bullets.push_back(bulletW);


}

Weapon::Weapon(vector<Bullet> bulletW, Time time)
	:clock(new Clock) {

	this->reload = time;
	this->bullets = bulletW;


}

int Weapon::get_reload() {
	return (this->reload - this->clock->getElapsedTime()).asMilliseconds();
}


void Weapon::restart_reload() {
	this->clock->restart();
}


Sprite Weapon::createSprite(string textureName, Vector2f size) {

	sf::Sprite sprite;
	sprite.setTexture(this->resMgr->getRefTex(textureName));
	sprite.setScale(size);

	return sprite;
}

//Bullets(int id, Sprite bulletSprite, Vector2f dir, float BulletmaxSpeed bool autoAim = false, bool fromPlayer = true);


void Weapon::create_bullet_chuni_red(RessourceManager* resMgr, float reloadTime) {
	this->resMgr = resMgr;

	/* --- CONFIG --- */
	Time reload_time = milliseconds(reloadTime);
	this->reload = reload_time;
	float damage = 10;
	/* End Config*/


	Bullet bullet_chuni_red(1,  this->createSprite("bullet_chuni_red", Vector2f(0.3, 0.3)), damage, Vector2f(0, 0), Vector2f(1, 0), 15, false);
	this->bullets.push_back(bullet_chuni_red);

}


void Weapon::create_ball_glass_blue(RessourceManager* resMgr, float reloadTime) {
	this->resMgr = resMgr;

	/* --- CONFIG --- */
	Time reload_time = milliseconds(reloadTime);
	this->reload = reload_time;
	float damage = 1;
	/* End Config*/

	

	Bullet bullet_ball_glass_blue(1, this->createSprite("bullet_ball_glass_blue",  Vector2f(1.5, 1.5)), damage, Vector2f(0, 0), Vector2f(1, 0), 15, true);
	this->bullets.push_back(bullet_ball_glass_blue);

}

void Weapon::create_ball_glass_red(RessourceManager* resMgr, float reloadTime) {
	this->resMgr = resMgr;

	/* --- CONFIG --- */
	Time reload_time = milliseconds(reloadTime);
	this->reload = reload_time;
	float damage = 1;
	/* End Config*/


	Bullet bullet_ball_glass_red1(1, this->createSprite("bullet_ball_glass_red", Vector2f(1.5, 1.5)), damage, Vector2f(0, -50), Vector2f(1, 0), 10, false);
	Bullet bullet_ball_glass_red2(1, this->createSprite("bullet_ball_glass_red", Vector2f(1.3, 1.3)), damage, Vector2f(0, 50), Vector2f(1, 0), 10, false);
	Bullet bullet_ball_glass_red3(1, this->createSprite("bullet_ball_glass_red", Vector2f(1.3, 1.3)), damage, Vector2f(0, 150), Vector2f(1, 0), 10, false);

	this->bullets.insert(this->bullets.end(), { bullet_ball_glass_red1, bullet_ball_glass_red2, bullet_ball_glass_red3 });

}

void Weapon::create_special_chuni(RessourceManager* resMgr, float reloadTime) {
	this->resMgr = resMgr;

	/* --- CONFIG --- */
	Time reload_time = milliseconds(reloadTime);
	this->reload = reload_time;
	float damage = 25;
	/* End Config*/


	Bullet bullet_chuni_red_1(1, this->createSprite("bullet_chuni_red", Vector2f(0.5, 0.5)), damage, Vector2f(0.f, -50.f), Vector2f(1, 0), 5.f, false);
	Bullet bullet_chuni_red_2(1, this->createSprite("bullet_chuni_red", Vector2f(0.5, 0.5)), damage, Vector2f(0.f, 50.f), Vector2f(1, 0), 5.f, false);

	this->bullets.insert(this->bullets.end(), { bullet_chuni_red_1, bullet_chuni_red_2});

}