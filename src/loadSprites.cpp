#include "Player.h"
#include "Bullet.h"
#include "loadSprites.h"


void init() {
	//Player
	sf::Texture Marisa;
	Marisa.loadFromFile("Sprites/Player/marisa.png");
	Marisa.setSmooth(true);
	sf::Sprite spritePlayer;
	spritePlayer.setTexture(Marisa);


	Player player(spritePlayer, 10.f);



	//Bullets
	sf::Texture bulletsClassiqueTexture;
	sf::Texture bullet_ball_glass_blueTexture;
	bulletsClassiqueTexture.loadFromFile("Sprites/Bullets/classique.png");
	bulletsClassiqueTexture.setSmooth(true);
	bullet_ball_glass_blueTexture.loadFromFile("Sprites/Bullets/bullet_ball_glass_blue.png");
	bullet_ball_glass_blueTexture.setSmooth(true);


	sf::Sprite bulletsClassiqueSprite;
	bulletsClassiqueSprite.setTexture(bulletsClassiqueTexture);
	bulletsClassiqueSprite.setScale(Vector2f(0.5, 0.5));

	sf::Sprite bullet_ball_glass_blueSprite;
	bullet_ball_glass_blueSprite.setTexture(bullet_ball_glass_blueTexture);
	bullet_ball_glass_blueSprite.setScale(Vector2f(3, 3));

	Bullet rainbow(bulletsClassiqueSprite);
	Bullet smarties(bullet_ball_glass_blueSprite, 15.f);
}