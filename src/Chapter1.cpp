#pragma once
#include "Chapter.h"
#include "AnimatedSprite.h"




void Chapter::loadFilesChap1() {
	/*  --- BACKGROUND --- */
	this->game.resMgr.loadTexture("bg_chap_1", "Assets/Background/TempleOfWeyrd.png");
	this->game.resMgr.loadTexture("bg_gameplay_1", "Assets/Background/Gameplay/SkiesOfGensokyo.jpg");

	/*  --- CHARACTER & ENNEMIES --- */
	this->game.resMgr.loadTexture("Marisa", "Assets/Sprites/Player/marisa.png");
	this->game.resMgr.loadTexture("Reimu", "Assets/Sprites/Player/reimu.png");


	this->game.resMgr.loadTexture("Cirno", "Assets/Sprites/Enemies/cirno.png");
	this->game.resMgr.loadTexture("brown", "Assets/Sprites/Enemies/brown.png");
	this->game.resMgr.loadTexture("red", "Assets/Sprites/Enemies/red.png");

	/* --- BULLETS --- */
	this->game.resMgr.loadTexture("bullet_chuni_red", "Assets/Sprites/Bullets/bullet_chuni_red.png");
	this->game.resMgr.loadTexture("bullet_chuni_red_reverse", "Assets/Sprites/Bullets/bullet_chuni_red_reverse.png");
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
	Animation driftingDown;
	driftingDown.setSpriteSheet(this->game.resMgr.getRefTex("Reimu"));
	driftingDown.addFrame(sf::IntRect(115, 0, 45, 32));
	driftingDown.addFrame(sf::IntRect(115, 32, 45, 32));
	driftingDown.addFrame(sf::IntRect(115, 64, 45, 32));
	driftingDown.addFrame(sf::IntRect(115, 96, 45, 32));
	driftingDown.addFrame(sf::IntRect(115, 128, 45, 32));
	driftingDown.addFrame(sf::IntRect(115, 128 + 32, 45, 32));
	driftingDown.addFrame(sf::IntRect(115, 128 + 32*2, 45, 32));
	driftingDown.addFrame(sf::IntRect(115, 128 + 32*3, 45, 32));

	Animation driftingUp;
	driftingUp.setSpriteSheet(this->game.resMgr.getRefTex("Reimu"));
	driftingUp.addFrame(sf::IntRect(162, 0, 45, 32));
	driftingUp.addFrame(sf::IntRect(162, 32, 45, 32));
	driftingUp.addFrame(sf::IntRect(162, 64, 45, 32));
	driftingUp.addFrame(sf::IntRect(162, 96, 45, 32));
	driftingUp.addFrame(sf::IntRect(162, 128, 45, 32));
	driftingUp.addFrame(sf::IntRect(162, 128 + 32, 45, 32));
	driftingUp.addFrame(sf::IntRect(162, 128 + 32 * 2, 45, 32));
	driftingUp.addFrame(sf::IntRect(162, 128 + 32 * 3, 45, 32));


	Animation driftingAfk;
	driftingAfk.setSpriteSheet(this->game.resMgr.getRefTex("Reimu"));
	driftingAfk.addFrame(sf::IntRect(210, 0, 45, 32));
	driftingAfk.addFrame(sf::IntRect(210, 32, 45, 32));
	driftingAfk.addFrame(sf::IntRect(210, 64, 45, 32));
	driftingAfk.addFrame(sf::IntRect(210, 96, 45, 32));
	driftingAfk.addFrame(sf::IntRect(210, 128, 45, 32));
	driftingAfk.addFrame(sf::IntRect(210, 128 + 32, 45, 32));
	driftingAfk.addFrame(sf::IntRect(210, 128 + 32 * 2, 45, 32));
	driftingAfk.addFrame(sf::IntRect(210, 128 + 32 * 3, 45, 32));


	//paused = false, bool looped = true
	AnimatedSprite* animatedSprite = new AnimatedSprite(sf::seconds(0.2), false, true);

	map<string, Animation> allAnimations;
	allAnimations["down"] = driftingDown;
	allAnimations["up"] = driftingUp;
	allAnimations["afk"] = driftingAfk;

	Character charPlayer(animatedSprite, allAnimations, Vector2f(150, this->game.window.getSize().y / 2), 12);
	this->gameplay.player = charPlayer;



	Enemy cirno;
	cirno.cirno(&this->game.resMgr);
	this->gameplay.enemies.push_back(cirno);


	Enemy brown;
	brown.brown_pattern1(&this->game.resMgr);
	this->gameplay.enemies.push_back(brown);


	/*  --- WEAPONS --- */
	//chuni red
	Pattern pattern_bullet_chuni_red;
	pattern_bullet_chuni_red.create_bullet_chuni_red(&this->game.resMgr);
	this->gameplay.bulletMgr["bullet_chuni_red"] = pattern_bullet_chuni_red;

	//ball_glass_blue
	Pattern pattern_ball_glass_blue;
	pattern_ball_glass_blue.create_ball_glass_blue(&this->game.resMgr);
	this->gameplay.bulletMgr["bullet_ball_glass_blue"] = pattern_ball_glass_blue;

	//ball_glass_red
	Pattern pattern_ball_glass_red;
	pattern_ball_glass_red.create_ball_glass_red(&this->game.resMgr);
	this->gameplay.bulletMgr["bullet_ball_glass_red"] = pattern_ball_glass_red;

	//test_special
	Pattern pattern_special_chuni;
	pattern_special_chuni.create_special_chuni(&this->game.resMgr);
	this->gameplay.bulletMgr["special_chuni"] = pattern_special_chuni;


	//this->gameplay.create_bullets_player(cirno.patterns[0]);
}