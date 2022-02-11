#pragma once
#include "Header.h"
#include "RessourceManager.h"
#include "Game.h"


class Game;

using namespace sf;
using namespace std;


class Menu {
private:
	/* Menu */
	vector<string> main_menu_id1{"Start", "Select Chapter", "Options", "Quit game"};
	vector<string> select_chapter_menu_id2{ "Chapter 1", "Chapter 2", "Chapter 3", "Back"};
	vector<string> options_menu_id3{ "Volume music :", "Volume SFX :", "Back" };
	vector<int> option_menu_id3_values{};
	vector<string> game_pause_menu_id4{ "Return to game", "Options", "Back to main menu", "Quit game" };

	vector<string> actual_menu = main_menu_id1;

	vector<Text> menu_list_draw;
	vector<Text> menu_values;

	int id_select = 0;
	int id_menu = 1;

	/* Some config var*/
	Color outlineColor = Color(142, 142, 142, 175);
	Game& game;
	bool debug = false;
	int pasMusic = 5;

	/* Draw */
	Text title;
	Sprite background;

	/* Music & Sounds */
	Sound main_theme_music;
	Sound menu_sound_select;
	Sound menu_sound_enter;


	/* Init Functions*/
	void loadMainMenuFiles();
	void useRessourcesMenu();
	Sprite createSprite(string textureName, Vector2f size = Vector2f(1.f, 1.f), bool background = false);

	/* Menu::Menu Functions*/
	void menu_update();
	void updateOptionsValues();
	void draw_menu();
	void key_pressed_mgr();
	void Build_menu();
	void userMove(int select);
	void userMenuChoice();


	/* Menu Functions */
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

