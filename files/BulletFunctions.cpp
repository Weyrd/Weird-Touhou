#pragma once
#include "Bullet.h"


Bullet::Bullet(Sprite bulletSprite, float damageBullet, Vector2f startPosDiff, Vector2f dir, float BulletSpeed,  bool autoAimB, bool fromPlayerB)  {

		this->damage = damageBullet;
		this->direction = dir;
		this->shape = bulletSprite;
		this->speed = BulletSpeed;

		this->sizeSprite = Vector2f(bulletSprite.getTexture()->getSize().x * bulletSprite.getScale().x,
			bulletSprite.getTexture()->getSize().y * bulletSprite.getScale().y);

		this->autoAim = autoAimB;
		this->fromPlayer = fromPlayerB;

		this->startPosDiff = startPosDiff;
}


Bullet::Bullet(float damageBullet, Vector2f dir, float BulletSpeed, bool autoAimB, bool fromPlayerB) {
	this->direction = dir;
	this->damage = damageBullet;
	this->speed = BulletSpeed;
	this->autoAim = autoAimB;
	this->fromPlayer = fromPlayerB;
}


