#pragma once
#include "Header.h"
#include "RessourceManager.h"
#include "Game.h"


class Game;

using namespace sf;
using namespace std;


class Menu {
private:
	vector<string> main_menu_id1{"Start", "Select Chapter", "Options", "Quit game"};
	vector<string> select_chapter_menu_id2{ "Chapter 1", "Chapter 2", "Chapter 3", "Back"};
	vector<string> options_menu_id3{ "Volume music :", "Volume SFX :", "Back" };
	vector<int> option_menu_id3_values{};
	vector<string> game_pause_menu_id4{ "Return to game", "Options", "Back to main menu", "Quit game" };

	vector<string> actual_menu = main_menu_id1;

	vector<Text> menu_list_draw;
	vector<Text> menu_values;

	int id_select = 0;
	int id_value_select = 0;
	int id_menu = 1;

	bool value_select = false;

	bool debug = false;
	Game& game;
	Color outlineColor = Color(142, 142, 142, 175);

	Sprite background;
	Sound main_theme_music;

	void loadMainMenuFiles();
	void useRessourcesMenu();
	Sprite createSprite(string textureName, Vector2f size = Vector2f(1.f, 1.f), bool background = false);

	void menu_update();
	void updateOptionsValues();
	void draw_menu();
	void key_pressed_mgr();
	void Build_menu();
	void userMove(int select);
	void userMenuChoice();


	void menu_id1();
	void menu_id2();
	void menu_id3();
	void menu_id3(int select);
	void menu_id4();




public:
	bool quitMenu = false;

	Menu(Game& game);
	void main_menu_run();
};


