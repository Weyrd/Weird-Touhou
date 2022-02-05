#pragma once
#include "Chapter.h"


Chapter::Chapter(Game& game, Gameplay& gameplay)
	: game(game), gameplay(gameplay) {
}

Sprite Chapter::createSprite(string textureName, Vector2f size, int type_id) {

	sf::Sprite sprite;
	sprite.setTexture(this->game.resMgr.getRefTex(textureName));
	sprite.setScale(size);

	if (type_id == 1) { // background
		float scaleX = (float)this->game.window.getSize().x / sprite.getTexture()->getSize().x;
		float scaleY = (float)this->game.window.getSize().y / sprite.getTexture()->getSize().y;

		sprite.setScale(Vector2f(scaleX, scaleY));
	}
	if (type_id == 2) { //gameplay background 
		// 37/51 // 1448/51 2.5% de marge * 2
		float verticalSize = (float)this->game.window.getSize().x - (2 * (2.5 * this->game.window.getSize().x / 100));

		// une marge a 4 l'autre a 30
		float horizontalSize = (float)this->game.window.getSize().y - (4 * this->game.window.getSize().y / 100) - (30 * this->game.window.getSize().y / 100);

		float scaleX = (float)verticalSize / sprite.getTexture()->getSize().x;
		float scaleY = (float)horizontalSize / sprite.getTexture()->getSize().y;

		sprite.setScale(Vector2f(scaleX, scaleY));
		sprite.setPosition(Vector2f(37, 51));
	}

	return sprite;
}





void Chapter::loadfilesChap(int chapter) {
	switch (chapter) {

	case 1:
		loadFilesChap1();
		useRessourcesChap1();
		break;
	default:
		break;
	}
}