#pragma once
#include "Chapter.h"


Chapter::Chapter(Game& game, Gameplay& gameplay)
	: game(game), gameplay(gameplay) {
}

Sprite Chapter::createSprite(string textureName, Vector2f size, bool background) {

	sf::Sprite sprite;
	sprite.setTexture(this->game.resMgr.getRefTex(textureName));
	sprite.setScale(size);
	if (background) {
		float scaleX = (float) this->game.window.getSize().x / sprite.getTexture()->getSize().x;
		float scaleY = (float) this->game.window.getSize().y / sprite.getTexture()->getSize().y;

		sprite.setScale(Vector2f(scaleX, scaleY));
	}

	return sprite;
}


void Chapter::loadTextureChap1() {
	//background
	this->game.resMgr.loadTexture("bg_chap_1", "Assets/Background/SkiesOfGensokyo.jpg");

	//Characters / Enemies
	this->game.resMgr.loadTexture("Marisa", "Assets/Sprites/Player/marisa.png");

	this->game.resMgr.loadTexture("Cirno", "Assets/Sprites/Enemies/cirno.png");
	this->game.resMgr.loadTexture("brown", "Assets/Sprites/Enemies/brown.png");
	this->game.resMgr.loadTexture("red", "Assets/Sprites/Enemies/red.png");

	//Bullets
	this->game.resMgr.loadTexture("bullet_chuni_red", "Assets/Sprites/Bullets/bullet_chuni_red.png");
	this->game.resMgr.loadTexture("bullet_ball_glass_blue", "Assets/Sprites/Bullets/bullet_ball_glass_blue.png");
	this->game.resMgr.loadTexture("bullet_ball_glass_red", "Assets/Sprites/Bullets/bullet_ball_glass_red.png");

	
	
}


void Chapter::loadSpriteChap1() {
	//background
	this->gameplay.background = this->createSprite("bg_chap_1", Vector2f(1.f, 1.f), true);

	/*  --- CHARACTER AND ENNEMIES --- */
	/*
	Character* charPlayer = new Character (this->createSprite("Marisa"), Vector2f(150, this->game.window.getSize().y / 2), 12);
	this->gameplay.player = (*charPlayer);
	*/
	Character charPlayer(this->createSprite("Marisa"), Vector2f(150, this->game.window.getSize().y / 2), 12);
	this->gameplay.player = charPlayer;



	Enemy cirno;
	cirno.cirno(&this->game.resMgr);
	this->gameplay.enemies.push_back(cirno);

	Enemy brown;
	brown.brown_pattern1(&this->game.resMgr);
	this->gameplay.enemies.push_back(brown);


	/*  --- WEAPONS --- */
	//chuni red
	Weapon weapon_bullet_chuni_red;
	weapon_bullet_chuni_red.create_bullet_chuni_red(&this->game.resMgr);
	this->gameplay.bulletMgr["bullet_chuni_red"] = weapon_bullet_chuni_red;

	//ball_glass_blue
	Weapon weapon_ball_glass_blue;
	weapon_ball_glass_blue.create_ball_glass_blue(&this->game.resMgr);
	this->gameplay.bulletMgr["bullet_ball_glass_blue"] = weapon_ball_glass_blue;

	//ball_glass_red
	Weapon weapon_ball_glass_red;
	weapon_ball_glass_red.create_ball_glass_red(&this->game.resMgr);
	this->gameplay.bulletMgr["bullet_ball_glass_red"] = weapon_ball_glass_red;

	//test_special
	Weapon weapon_special_chuni;
	weapon_special_chuni.create_special_chuni(&this->game.resMgr);
	this->gameplay.bulletMgr["special_chuni"] = weapon_special_chuni;
}