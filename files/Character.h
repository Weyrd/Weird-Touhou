#pragma once
#include "Header.h"

using namespace sf;
using namespace std;




class Character
{
private:
	Clock* clock = new Clock;
public:
	Vector2f sizeSprite;
	Sprite shape;
	Vector2f center;

	float life;

	float Speed;
	float offset;
	float pathPos = 0;
	float nextStepPath = 1;

	bool spawn = false;

	Vector2f lastPosition;

	RectangleShape hitbox;
	Color color;

	

	Character(Sprite sprite, Vector2f startPosition = Vector2f(0.f, 0.f), float Speed = 10.f, float life = 100.f, float offset = 0.f);
	Character(float Speed = 10.f) ;
	~Character() { /*cout << "Delete Char life -> " << life << endl;*/ }

	int get_time();
	void restart_reload();
};
