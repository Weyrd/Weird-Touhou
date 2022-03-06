#pragma once
#include "Character.h"
#include "AnimatedSprite.h"

using namespace sf;
using namespace std;

Character::Character(AnimatedSprite* animatedSprite, map<string, Animation> allAnimations, Vector2f startPosition, float Speed, float life, float offset):
	offset(offset), life(life){

	this->Speed = Speed;
	this->animatedSprite = animatedSprite;
	this->allAnimations = allAnimations;
	this->currentAnimation = allAnimations["afk"];
	/*this->shape = sprite;*/
	Vector2f sizeSpriteCalc = Vector2f(4, 35);
	this->sizeSprite = sizeSpriteCalc;

	
	Vector2f startPos = Vector2f(startPosition.x - this->sizeSprite.x / 2, startPosition.y - this->sizeSprite.y / 2);

	this->animatedSprite->setPosition(startPos);

	Vector2f centerPlayer = Vector2f(this->animatedSprite->getPosition().x + this->sizeSprite.x / 2,
		this->animatedSprite->getPosition().y + this->sizeSprite.y / 2);




	this->center = centerPlayer;

	/* Hitbox */
	this->hitbox = RectangleShape(sizeSpriteCalc);
	this->hitbox.setFillColor(Color(255, 0, 0, 55));
	
	this->hitbox.setOutlineThickness(4);
	this->hitbox.setOutlineColor(Color(255, 255, 0));
	this->hitbox.setPosition(startPos);

}
Character::Character(Sprite sprite, Vector2f startPosition, float Speed, float life, float offset) :
	offset(offset), life(life) {

	this->Speed = Speed;
	this->shape = sprite;
	Vector2f sizeSpriteCalc = Vector2f(sprite.getTexture()->getSize().x * sprite.getScale().x,
		sprite.getTexture()->getSize().y * sprite.getScale().y);
	this->sizeSprite = sizeSpriteCalc;


	Vector2f startPos = Vector2f(startPosition.x - this->sizeSprite.x / 2, startPosition.y - this->sizeSprite.y / 2);

	this->shape.setPosition(startPos);

	Vector2f centerPlayer = Vector2f(this->shape.getPosition().x + this->sizeSprite.x / 2,
		this->shape.getPosition().y + this->sizeSprite.y / 2);




	this->center = centerPlayer;

	/* Hitbox */
	this->hitbox = RectangleShape(sizeSpriteCalc);
	this->hitbox.setFillColor(Color(255, 0, 0, 55));

	this->hitbox.setOutlineThickness(4);
	this->hitbox.setOutlineColor(Color(255, 255, 0));
	this->hitbox.setPosition(startPos);

}


Character::Character(float Speed) {
	this->Speed = Speed;

}

int Character::get_time() {
	return this->clock->getElapsedTime().asMilliseconds();
}

void Character::restart_reload() {
	this->clock->restart();
}
