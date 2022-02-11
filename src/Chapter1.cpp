#pragma once
#include "Chapter.h"





void Chapter::loadFilesChap1() {
	/*  --- BACKGROUND --- */
	this->game.resMgr.loadTexture("bg_chap_1", "Assets/Background/TempleOfWeyrd.png");
	this->game.resMgr.loadTexture("bg_gameplay_1", "Assets/Background/Gameplay/SkiesOfGensokyo.jpg");

	/*  --- CHARACTER & ENNEMIES --- */
	this->game.resMgr.loadTexture("Marisa", "Assets/Sprites/Player/marisa.png");

	this->game.resMgr.loadTexture("Cirno", "Assets/Sprites/Enemies/cirno.png");
	this->game.resMgr.loadTexture("brown", "Assets/Sprites/Enemies/brown.png");
	this->game.resMgr.loadTexture("red", "Assets/Sprites/Enemies/red.png");

	/* --- BULLETS --- */
	this->game.resMgr.loadTexture("bullet_chuni_red", "Assets/Sprites/Bullets/bullet_chuni_red.png");
	this->game.resMgr.loadTexture("bullet_ball_glass_blue", "Assets/Sprites/Bullets/bullet_ball_glass_blue.png");
	this->game.resMgr.loadTexture("bullet_ball_glass_red", "Assets/Sprites/Bullets/bullet_ball_glass_red.png");

	/* --- MUSIC & SOUNDS --- */
	//music
	this->game.resMgr.loadSoundBuffer("main_theme_chap1", "Assets/Sounds/Musics/2_chapter1_ChineseTea.wav");
	//bullets song
	this->game.resMgr.loadSoundBuffer("bulletpiou", "Assets/Sounds/Bullets/piou.wav");
	
}




void Chapter::useRessourcesChap1() {
	/* --- BACKGROUND --- */
	this->gameplay.background = this->createSprite("bg_chap_1", Vector2f(1.f, 1.f), 1);
	this->gameplay.gameplay_background = this->createSprite("bg_gameplay_1", Vector2f(1.f, 1.f), 2);

	/* --- MUSIC & SOUNDS --- */
	Sound main_theme_chap1;
	main_theme_chap1.setBuffer(this->game.resMgr.getRefSoundBuffer("main_theme_chap1"));
	main_theme_chap1.setVolume(this->game.volumeMusic);
	main_theme_chap1.setLoop(true);

	Sound bulletSound_id1;
	bulletSound_id1.setBuffer(this->game.resMgr.getRefSoundBuffer("bulletpiou"));
	bulletSound_id1.setVolume(this->game.volumeSFX);
	this->gameplay.bulletSoundMgr[1] = bulletSound_id1;
	


	this->gameplay.music = main_theme_chap1;
	this->gameplay.music.play();
	/* End Musics & Sounds */


	/*  --- CHARACTER & ENNEMIES --- */
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


	//this->gameplay.create_bullets_player(cirno.weapons[0]);
}