#pragma once
#include "Bullet.h"

typedef std::pair<float, Vector2f*> MyPairType;
struct CompareFirst
{
	bool operator()(const MyPairType& left, const MyPairType& right) const
	{
		return left.first < right.first;
	}
};

Bullet::Bullet(int id, Sprite bulletSprite, float damageBullet, Vector2f startPosDiff, Vector2f dir, float BulletSpeed,  bool autoAimB, bool fromPlayerB)  {

		this->id = id;
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


Bullet::Bullet(int id, float damageBullet, Vector2f dir, float BulletSpeed, bool autoAimB, bool fromPlayerB){
	this->id = id;
	this->direction = dir;
	this->damage = damageBullet;
	this->speed = BulletSpeed;
	this->autoAim = autoAimB;
	this->fromPlayer = fromPlayerB;
}


/* --- AIM --- */
/* Pas opti bonjour ? */
Vector2f Bullet::getAutoAim(Vector2f targetPos) {
	Vector2f dirTarget;
	Vector2f dirMax = Vector2f(0.04, 0.04); // vecteur du néo drift max de la bullet

	float x = this->shape.getPosition().x + this->sizeSprite.x / 2;
	float y = this->shape.getPosition().y + this->sizeSprite.y / 2;
	Vector2f bulletCenter = Vector2f(x, y);

	float xTarget = targetPos.x - bulletCenter.x;//(targetPos.x - bulletCenter.x) / (targetPos.x + bulletCenter.x);
	float yTarget = targetPos.y - bulletCenter.y;//(targetPos.y - bulletCenter.y) / (targetPos.y + bulletCenter.y);
	float multiplicator = 1 / (abs(xTarget) + abs(yTarget));


	float currentX = this->direction.x / this->speed;
	float currentY = this->direction.y / this->speed;

	float xTargetAdjust = xTarget * multiplicator;
	float yTargetAdjust = yTarget * multiplicator;


	//cout << "x adjust : " << xTargetAdjust << endl;
	//cout << "y adjust : " << yTargetAdjust << endl;
	if (abs(xTargetAdjust) > dirMax.x) {
		if (currentX - xTargetAdjust > 0) {
			xTargetAdjust = currentX - dirMax.x;
			//cout << "x -- : " << currentX << " | " << xTargetAdjust << endl;
		}
		else if (currentX - xTargetAdjust < 0) {
			xTargetAdjust = currentX + dirMax.x;
			//cout << "x ++ : " << currentX << " | " << xTargetAdjust << endl;
		}
		else {
			xTargetAdjust = 0.5;
		}
	}
	if (abs(yTargetAdjust) > dirMax.y) {
		if (currentY - yTargetAdjust > 0) {
			yTargetAdjust = currentY - dirMax.y;
			//cout << "y -- : " << currentY << " | " << yTargetAdjust << endl;
		}
		else if (currentY - yTargetAdjust < 0) {
			yTargetAdjust = currentY + dirMax.y;
			//cout << "y ++ : " << currentY << " | " << yTargetAdjust << endl;
		}
		else {
			yTargetAdjust = 0.5;
		}
	}

	multiplicator = 1 / (abs(xTargetAdjust) + abs(yTargetAdjust));

	//cout << endl;

	dirTarget = Vector2f(xTargetAdjust * multiplicator, yTargetAdjust * multiplicator);
	//cout << dirTarget.x << " | " << dirTarget.y << endl;
	return dirTarget;
}

Vector2f Bullet::getClosestEnemy(vector<Vector2f*> enemiesCenter) {
	map<float, Vector2f*>  distanceEnemy;
	//cout << " get -> " << bulletAim.bulletCenter.x << " | " << bulletAim.bulletCenter.y << endl;
	for (size_t i = 0; i < enemiesCenter.size(); i++) {
		float x2 = enemiesCenter[i]->x;
		float y2 = enemiesCenter[i]->y;
		float distance = sqrt(abs(
			powf((x2 - this->bulletCenter.x), 2) - /////////////// C4EST FAUX (non c'est vrai je crois)
			powf((y2 - this->bulletCenter.y), 2))
		);

		distanceEnemy[distance] = enemiesCenter[i];
		//cout << distance << " -> " << enemiesCenter[i]->x << " | " << enemiesCenter[i]->y << endl;

	}
	//cout << distanceEnemy.size() << " - " << this->enemiesCenter.size() <<endl;;
	for (map<float, Vector2f*>::iterator it = distanceEnemy.begin(); it != distanceEnemy.end(); ++it) {
		//cout << it->first << " - " << it->second->x << " | " << it->second->y << endl;
	}
	//cout << endl;

	if (!distanceEnemy.empty()) {
		pair<float, Vector2f*> closestEnemy
			= *min_element(distanceEnemy.begin(), distanceEnemy.end(), CompareFirst());


		return Vector2f(closestEnemy.second->x, closestEnemy.second->y);
	}
	else {
		Vector2f straight = Vector2f(20000, this->shape.getPosition().y + this->sizeSprite.y / 2);
		return straight;
	}


}


void Bullet::move_straightForward(Vector2f playerCenter, vector<Vector2f*> enemiesCenter) {
	float x = this->shape.getPosition().x + this->sizeSprite.x / 2;
	float y = this->shape.getPosition().y + this->sizeSprite.y / 2;
	Vector2f bulletCenter = Vector2f(x, y);
	this->bulletCenter = bulletCenter;




	if (this->autoAim) {
		Vector2f targetDir;

		if (this->fromPlayer) {/////////////////////////////// calcul from bullet to closest enemy
			Vector2f closestEnemy = (getClosestEnemy(enemiesCenter));
			//cout << closestEnemy.x << " | " << closestEnemy.y << endl;
			targetDir = getAutoAim(closestEnemy);
			//cout << targetDir.x << " | " << targetDir.y << endl;
		}

		else {/////////////////////////////// calcul from bullet to player
			targetDir = getAutoAim(playerCenter);
		}
		this->direction = targetDir * this->speed;
	}

		//cout << this->direction.x << " | " << this->direction.y << endl;


}

void Bullet::circle_pattern() {

}


void Bullet::move(Vector2f playerCenter, vector<Vector2f*> enemiesCenter) {

	switch (this->id) {
	case 1:
		this->move_straightForward(playerCenter, enemiesCenter);
		break;
	case 2:
		this->circle_pattern();
		break;
	}

}