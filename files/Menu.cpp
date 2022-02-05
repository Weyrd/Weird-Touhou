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
			if (this->game.event.key.code == sf::Keyboard::Left) { this->userMove(3); }
			if (this->game.event.key.code == sf::Keyboard::Right) { this->userMove(4); }
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

void Menu::loadMainMenuFiles() {
	//background
	this->game.resMgr.loadTexture("bg_main_menu", "Assets/Background/mainMenu2.png");
	this->game.resMgr.loadSoundBuffer("menu_theme", "Assets/Sounds/1 main_menu.wav");

	this->useRessourcesMenu();
}

void Menu::useRessourcesMenu() {
	//background
	this->background = this->createSprite("bg_main_menu", Vector2f(1.f, 1.f), true);

	Sound main_theme_music;
	main_theme_music.setBuffer(this->game.resMgr.getRefSoundBuffer("menu_theme"));
	main_theme_music.setVolume(this->game.volumeMusic);
	main_theme_music.setLoop(true);


	this->main_theme_music = main_theme_music;
	this->main_theme_music.play();

	
}
 /* Fin Ressources */

void Menu::updateOptionsValues() {
	this->option_menu_id3_values.clear();
	this->option_menu_id3_values.insert(this->option_menu_id3_values.end(), {(int)this->game.volumeMusic, (int)this->game.volumeSFX });
}

void Menu::Build_menu() {
	this->menu_list_draw.clear();
	int number_options = actual_menu.size();

	int count = 0;

	for (auto& element : this->actual_menu) {
		Text newText;

		newText.setString(element);
		newText.setFont(this->game.resMgr.getRefFont("Touhoufont"));
		newText.setCharacterSize(50);
		newText.setFillColor(Color(0, 0, 0));

		/* PLACEMENT HERE */
		float posX = (float)(5 * this->game.window.getSize().x / 100);
		float posY = (float)(37.5 * this->game.window.getSize().x / 100) + 100 * count;

		Vector2f position = Vector2f(posX, posY);

		newText.setPosition(position);


		this->menu_list_draw.push_back(newText);
		count++;
	}

	count = 0;
	if (id_menu == 3) { // option menu on affiche les values
		this->updateOptionsValues();
		this->menu_values.clear();
		for (auto& element : this->option_menu_id3_values) {
			Text newText;

			newText.setString(to_string(element));
			newText.setFont(this->game.resMgr.getRefFont("Touhoufont"));
			newText.setCharacterSize(50);
			newText.setFillColor(Color(0, 0, 0));

			/* PLACEMENT HERE */
			float posX = (float)(32.5 * this->game.window.getSize().x / 100);
			float posY = (float)(37.5 * this->game.window.getSize().x / 100) + 100 * count;

			Vector2f position = Vector2f(posX, posY);

			newText.setPosition(position);


			this->menu_values.push_back(newText);
			count++;
		}
	}

	if (!value_select) {
		this->menu_list_draw[this->id_select].setOutlineThickness(4);
		this->menu_list_draw[this->id_select].setOutlineColor(outlineColor);
	}
}


void Menu::userMove(int select) {
	this->menu_list_draw[this->id_select].setOutlineThickness(0);
	if (select == 1) { // up
		if (this->id_select > 0 && !value_select) { this->id_select--; }
		else if(!value_select) { this->id_select = this->menu_list_draw.size() - 1; }
	}
	if(select == 2) { //down
		if (this->id_select < this->menu_list_draw.size()-1 && !value_select) { this->id_select++; }
		else if(!value_select) { this->id_select = 0; }

	}

	

	//options
	if (id_menu == 3) { menu_id3(select); }

	if (!value_select) {
		this->menu_list_draw[this->id_select].setOutlineThickness(4);
		this->menu_list_draw[this->id_select].setOutlineColor(outlineColor);
	}

	
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
		case 4: // In Game menu
			this->menu_id4();
			break;
	}
	
	this->Build_menu();
}


void Menu::main_menu_run() {
	

	if (game.in_game) {
		cout << "Load Game menu : " << endl;
		actual_menu = game_pause_menu_id4;
		this->id_menu = 4;
		this->useRessourcesMenu();
	}
	else {
		cout << "Load main menu : " << endl;
		this->loadMainMenuFiles();
	}
	
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
	this->main_theme_music.stop();

}


void Menu::draw_menu() {

	this->game.window.clear();
	this->game.window.draw(this->background);

	/* Text */
	for (size_t i = 0; i < this->menu_list_draw.size(); i++) {
		this->game.window.draw(menu_list_draw[i]);
	}


	if (id_menu == 3) { //options 
		for (size_t i = 0; i < this->menu_values.size(); i++) {
			this->game.window.draw(menu_values[i]);
		}
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

	if (id_select == 3) {
		//leave ty for playing
		this->game.window.close();
		quitMenu = true;
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
	if (id_select == options_menu_id3.size() - 1) {
		//in game ?
		if (this->game.in_game){ actual_menu = game_pause_menu_id4; id_menu = 4; }

		//main menu
		else { actual_menu = main_menu_id1; id_menu = 1; }
		
		this->id_select = 0;
	}

	else { cout << "Click on : " << options_menu_id3[id_select] << endl; }

}

void Menu::menu_id3(int select) {
	if (select == 1 && value_select) { // up
		switch (id_value_select) {
		case 0: // volume music
			if (this->game.volumeMusic < 100) {this->game.volumeMusic += 10; }
			break;
		default:
			break;
		}
	}


	if (select == 2 && value_select) { //down
		switch (id_value_select) {
		case 0: // volume music
			if (this->game.volumeMusic > 0) { this->game.volumeMusic -= 10; }
			break;
		default:
			break;
		}
	}
		
	

	if (select == 4 && this->id_select < this->menu_list_draw.size() - 1 && !value_select) { //Right // on select le meme
		this->id_value_select = id_select;
		this->menu_list_draw[this->id_select].setOutlineThickness(0);
		value_select = true;

	}

	if (select == 3 && this->id_select < this->menu_list_draw.size() - 1 && value_select) {//left // on deselect
		this->menu_values[this->id_value_select].setOutlineThickness(0);
		this->menu_list_draw[this->id_select].setOutlineThickness(4);
		this->menu_list_draw[this->id_select].setOutlineColor(outlineColor);
		value_select = false;
	}

	if (value_select) {
		this->menu_values[this->id_value_select].setOutlineThickness(4);
		this->menu_values[this->id_value_select].setOutlineColor(outlineColor);
	}
	
	this->Build_menu();
}


void Menu::menu_id4() { // Main Menu
	// return to game
	if (id_select == 0) {
		quitMenu = true;

		actual_menu = main_menu_id1;
		id_menu = 1;
		cout << "Quit Menu - return to game" << endl;
	}

	//Options
	if (id_select == 1) {
		actual_menu = options_menu_id3;
		id_menu = 3;
	}

	//Back to main menu
	if (id_select == 2) {
		this->game.in_game = false;
		quitMenu = true;

		actual_menu = main_menu_id1;
		id_menu = 1;
		cout << "Quit Menu - return to main screen" << endl;
	}

	if (id_select == 3) {
		//leave ty for playing
		this->game.window.close();
		this->game.in_game = false;
		quitMenu = true;
	}
	this->id_select = 0;
}