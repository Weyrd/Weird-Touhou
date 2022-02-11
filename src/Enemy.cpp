#pragma once
#include "Enemy.h"

using namespace sf;
using namespace std;


/*Enemy::Enemy() {


}*/
int Enemy::get_time() {
	return this->clock->getElapsedTime().asMilliseconds();
}

void Enemy::restart_reload() {
	this->clock->restart();
}

void Enemy::set_current_path() {
	if (this->get_time() > this->allPath[this->currentPath].time)
	{
		currentPath++;
		if (this->currentPath >= this->allPath.size())
		{
			this->currentPath = 0;
		}
	}
}

Sprite Enemy::createSprite(string textureName, Vector2f size) {

	sf::Sprite sprite;
	sprite.setTexture(this->resMgr->getRefTex(textureName));
	sprite.setScale(size);

	return sprite;
}





// Character(Sprite sprite, Vector2f startPosition = Vector2f(0.f,0.f), float Speed = 10.f, float life = 100.f, float offset = 10.f);
void Enemy::cirno(RessourceManager* resMgr) {
	this->resMgr = resMgr;
	this->name = "Cirno";
	this->startEnemyPosition = Vector2f(1300, 540);

	/*  --- PATH --- */
	Bezier::Bezier<3> curve_1({ {0, 0}, {200, -1080}, {1330, 1230}, {0, 0} });
	Bezier::Bezier<3> curve_2({ {0, 0}, {-200, 1080}, {-1330, -1230}, {0, 0} });
	Path path_1 = Path(15000, 0, curve_1);
	Path path_2 = Path(5000, 30, curve_2);
	
	this->allPath.insert(this->allPath.end(), { path_1, path_2 });

	/*  --- ENNEMIES --- */
	float speed = this->allPath[0].speed;
	Character cirno(this->createSprite("Cirno", Vector2f(0.2, 0.2)), this->startEnemyPosition, speed, 600, 3000);

	this->enemies.push_back(cirno);
	
	

	/*  --- BULLETS --- */
	this->timePatterBullets = 10000;
	Pattern bullet_chuni_red_1;
	bullet_chuni_red_1.create_special_chuni(this->resMgr, 750);

	this->enemies[0].patterns.insert(this->enemies[0].patterns.end(), { bullet_chuni_red_1 });

}



void Enemy::brown_pattern1(RessourceManager* resMgr) {
	this->resMgr = resMgr;
	this->startEnemyPosition = Vector2f(1500, 300);

	/*  --- PATH --- */
	Bezier::Bezier<3> curve_1({ {0, 0}, {800, 500}, {-500, 250}, {0, 0} });
	Path path_1 = Path(100000, 10, curve_1);

	this->allPath.insert(this->allPath.end(), { path_1 });



	/*  --- ENNEMIES --- */
	float speed = this->allPath[0].speed;
	Character brown(this->createSprite("brown", Vector2f(1.7, 1.7)), this->startEnemyPosition, speed, 200);
	Character brown2(this->createSprite("brown", Vector2f(1.7, 1.7)), this->startEnemyPosition, speed, 200, 1500);
	Character brown3(this->createSprite("brown", Vector2f(1.7, 1.7)), this->startEnemyPosition, speed, 200, 3000);

	this->enemies.insert(this->enemies.end(), { brown, brown2, brown3 });

}



