#pragma once
#include "Menu.h"



Menu::Menu(Game& game)
	: game(game) {
}

/* Key manager */
void Menu::key_pressed_mgr() {

	while (this->game.window.pollEvent(this->game.event)) {
		if (this->game.event.type == Event::Closed) {
			this->quitMenu = true;
			this->game.window.close();
		}


		if (this->game.event.type == sf::Event::KeyPressed) {
			if (this->game.event.key.code == sf::Keyboard::P) {
				this->game.in_game = true;
				this->quitMenu = true;
				cout << "Quit Menu" << endl;
			}

			if (this->game.event.key.code == sf::Keyboard::D) {
				if (!this->debug) {
					this->debug = true;
				}
				else {
					this->debug = false;
				}
			}

			if (this->game.event.key.code == sf::Keyboard::Up) {this->userMove(1);}
			if (this->game.event.key.code == sf::Keyboard::Down) { this->userMove(2);}
			if (this->game.event.key.code == sf::Keyboard::Enter) { this->userMenuChoice(); }

		}

	}
}


/* Sprite and texture builder */
Sprite Menu::createSprite(string textureName, Vector2f size, bool background) {

	sf::Sprite sprite;
	sprite.setTexture(this->game.resMgr.getRefTex(textureName));
	sprite.setScale(size);
	if (background) {
		float scaleX = (float)this->game.window.getSize().x / sprite.getTexture()->getSize().x;
		float scaleY = (float)this->game.window.getSize().y / sprite.getTexture()->getSize().y;

		sprite.setScale(Vector2f(scaleX, scaleY));
	}

	return sprite;
}

void Menu::loadMainMenuTex() {
	//background
	this->game.resMgr.loadTexture("bg_main_menu", "Assets/Background/mainMenu.jpg");
}

void Menu::loadMainMenuSprite() {
	//background
	this->background = this->createSprite("bg_main_menu", Vector2f(1.f, 1.f), true);
}
 /* Fin Sprite & Texture */


void Menu::Build_menu() {
	this->menu_list_draw.clear();
	int number_options = actual_menu.size();

	int count = 0;

	for (auto& element : this->actual_menu) {
	
		Text newText;

		newText.setString(element);
		newText.setFont(this->game.resMgr.getRefFont("AnimeRegular"));
		newText.setCharacterSize(35);
		newText.setFillColor(Color(255, 0, 0));

		/* PLACEMENT HERE */
		float posX = (float)this->game.window.getSize().x / 2 - newText.getCharacterSize();
		float posY = (float)this->game.window.getSize().y / number_options + 50 * count;

		Vector2f position = Vector2f(posX, posY);

		newText.setPosition(position);


		this->menu_list_draw.push_back(newText);
		count++;
	}
	this->menu_list_draw[this->id_select].setOutlineThickness(5);
}


void Menu::userMove(int select) {
	this->menu_list_draw[this->id_select].setOutlineThickness(0);
	if (select == 1) { // up
		if (this->id_select > 0) {
			this->id_select--;
		}
	}
	if(select == 2) { //down
		if (this->id_select < this->menu_list_draw.size()-1) {
			this->id_select++;
		}
	}
	this->menu_list_draw[this->id_select].setOutlineThickness(5);
}

void Menu::userMenuChoice() {
	switch (id_menu) {
		case 1: //main menu
			this->menu_id1();
			break;
		case 2: // Select chapter menu
			this->menu_id2();
			break;
		case 3: // Options menu
			this->menu_id3();
			break;
	}
	
	this->Build_menu();
}


void Menu::main_menu_run() {
	cout << "Load main menu : " << endl;
	this->loadMainMenuTex();
	this->loadMainMenuSprite();

	
	this->Build_menu();
	this->menu_update();
}



void Menu::menu_update() {
	this->quitMenu = false;
	while (!quitMenu) {

		
		this->key_pressed_mgr();
		this->draw_menu();

		this->game.fps_update(0,0);
	}

}


void Menu::draw_menu() {

	this->game.window.clear();
	this->game.window.draw(this->background);

	/* Text */
	for (size_t i = 0; i < this->menu_list_draw.size(); i++) {
		this->game.window.draw(menu_list_draw[i]);
	}


	if (this->debug) { // DEBUG
	
	}


	this->game.window.draw(this->game.info);
	this->game.window.display();
}




























/* CE QUE FONT LES MENUS */



void Menu::menu_id1() { // Main Menu
	// Start
	if (id_select == 0){
		game.chapter = 1;
		game.in_game = true;
		quitMenu = true;

		actual_menu = main_menu_id1;
		id_menu = 1;
		cout << "Quit Menu" << endl;
	}

	//Select chapter 
	if (id_select == 1){
		actual_menu = select_chapter_menu_id2;
		id_menu = 2;
	}

	//Options
	if (id_select == 2){
		actual_menu = options_menu_id3;
		id_menu = 3;
	}
	this->id_select = 0;
}


void Menu::menu_id2() { // Select chapter
	if (id_select == select_chapter_menu_id2.size()-1) {
		actual_menu = main_menu_id1;
		id_menu = 1;

	}
	else {
		game.chapter = id_select+1; // select ici
		game.in_game = true;
		quitMenu = true;

		actual_menu = main_menu_id1;
		id_menu = 1;
		cout << "Quit Menu" << endl;
	}
	this->id_select = 0;
		
}

void Menu::menu_id3() { // Select chapter
	if (id_select == select_chapter_menu_id2.size() - 1) {
		actual_menu = main_menu_id1;
		id_menu = 1;
		this->id_select = 0;
	}
	else {
		cout << "Click on : " << options_menu_id3[id_select] << endl;
	}

}