#pragma once
#include "Header.h"
#include "RessourceManager.h"
#include "Game.h"


class Game;

using namespace sf;
using namespace std;


class Menu {
private:
	vector<string> main_menu_id1{"Start", "Select Chapter", "Options", "EXIT"};
	vector<string> select_chapter_menu_id2{ "Chapter 1", "Chapter 2", "Chapter 3", "Back"};
	vector<string> options_menu_id3{ "Options 1", "Options 2", "Options 3", "Back" };

	vector<string> actual_menu = main_menu_id1;

	vector<Text> menu_list_draw;

	int id_select = 0;
	int id_menu = 1;

	bool debug = false;
	Game& game;

	Sprite background;

	void loadMainMenuTex();
	void loadMainMenuSprite();
	Sprite createSprite(string textureName, Vector2f size = Vector2f(1.f, 1.f), bool background = false);

	void menu_update();
	void draw_menu();
	void key_pressed_mgr();
	void Build_menu();
	void userMove(int select);
	void userMenuChoice();


	void menu_id1();
	void menu_id2();
	void menu_id3();



public:
	bool quitMenu = false;


	Menu(Game& game);
	void main_menu_run();
};


