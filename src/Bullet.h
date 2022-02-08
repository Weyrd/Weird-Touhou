#pragma once
#include "Header.h"

using namespace sf;
using namespace std;



class Bullet{
public:
	int id = 0;
	Sprite shape;
	Vector2f sizeSprite;
	
	Vector2f direction;
	Vector2f startPosDiff;
	Vector2f bulletCenter;

	bool fromPlayer;
	bool autoAim;

	float speed;
	float damage;


	
	Bullet(int id,  Sprite bulletSprite, float damageBullet, Vector2f startPosDiff = Vector2f(0.f, 0.f), Vector2f coefDir = Vector2f(1.f, 0.f), float BulletSpeed = 15.f,
		bool autoAim = false, bool fromPlayer = true);

	// Sound bulletSound
	Bullet(int id, float damageBullet, Vector2f dir = Vector2f(1.f, 0.f), float BulletSpeed = 15.f,
		bool autoAim = false, bool fromPlayer = true);

};