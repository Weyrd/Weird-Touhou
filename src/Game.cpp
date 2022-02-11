#pragma once
#include "Game.h"
#include "Menu.h"
#include <math.h>
using namespace sf;
using namespace std;

Game::Game(RenderWindow & windowPost)
	: window(windowPost) {
	this->window.setFramerateLimit(60);
	//this->window.setVerticalSyncEnabled(true);

}

void Game::loadFonts() {
	this->resMgr.loadFont("AnimeRegular", "Assets/Fonts/anime-ace.regular.ttf");
	this->resMgr.loadFont("Touhoufont", "Assets/Fonts/DFPPOPCorn-W12.ttf");

	

	info.setFont(this->resMgr.getRefFont("Touhoufont"));
	info.setCharacterSize(15);
	
}

void Game::fps_update(int numberBullets, int numberEnnemies) {
	this->framerate = 1 / this->clock.restart().asSeconds();
	this->info.setString("fps : " + to_string(this->framerate) +
						"\nBullet : " + to_string(numberBullets) +
						"\nEnemies : " + to_string(numberEnnemies)
						);
}

void Game::_run() {
	this->loadFonts();
	bool diabledmenu = true;

	Gameplay loadGameplay((*this));
	Menu loadMenu((*this));


	this->window.setKeyRepeatEnabled(false);

	while (this->window.isOpen())
	{
		if (!this->in_game && !diabledmenu) { loadMenu.main_menu_run(); }
		else { loadGameplay.chapter_run(); }
		
		this->window.clear();

	}

}
