#pragma once
#include "Gameplay.h"
#include "Weapon.h"
#include "Enemy.h"
#include "Bezier.h"
#include "Chapter.h"

typedef std::pair<float, Vector2f*> MyPairType;
struct CompareFirst
{
	bool operator()(const MyPairType& left, const MyPairType& right) const
	{
		return left.first < right.first;
	}
};

Gameplay::Gameplay(Game& game)
	: game(game){
}





void Gameplay::loadSprite() {
	Chapter load_chapter(this->game, (*this));

	switch (this->game.chapter) {
		case 1:
			load_chapter.loadTextureChap1();
			load_chapter.loadSpriteChap1();
			
			break;
		default:
			break;
	}
	cout << "Chap \"" << this->game.chapter << "\" load." << endl;

}




/* Moves */
void Gameplay::move_player() {

	this->player.center = Vector2f(this->player.shape.getPosition().x + this->player.sizeSprite.x / 2,
		this->player.shape.getPosition().y + this->player.sizeSprite.y / 2);


	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		if (player.shape.getPosition().x > 0) {
			player.shape.move(-player.Speed, 0.f);
			player.hitbox.move(-player.Speed, 0.f);
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		if (player.shape.getPosition().x + player.sizeSprite.x < this->game.window.getSize().x) {
			player.shape.move(player.Speed, 0.f);
			player.hitbox.move(player.Speed, 0.f);
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		if (player.shape.getPosition().y > 0) {
			player.shape.move(0.f, -player.Speed);
			player.hitbox.move(0.f, -player.Speed);
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		if (player.shape.getPosition().y + player.sizeSprite.y < this->game.window.getSize().y > 0) {
			player.shape.move(0.f, player.Speed);
			player.hitbox.move(0.f, player.Speed);
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::LShift)) {
		this->player.Speed = 5.f;
	}
	else
	{
		this->player.Speed = 10.f;
	}

	
}

void Gameplay::move_enemies() {

	for (size_t i = 0; i < this->enemies.size(); i++) {
		for (size_t j = 0; j < this->enemies[i].enemies.size(); j++) {


			if (this->enemies[i].enemies[j].spawn) {	
				Vector2f enemyCenter = Vector2f(this->enemies[i].enemies[j].shape.getPosition().x + this->enemies[i].enemies[j].sizeSprite.x / 2,
					this->enemies[i].enemies[j].shape.getPosition().y + this->enemies[i].enemies[j].sizeSprite.y / 2);

				this->enemies[i].enemies[j].center = enemyCenter;


				float pathPos = this->enemies[i].enemies[j].pathPos;

				int currentPathUse = this->enemies[i].currentPath;
				this->enemies[i].set_current_path();
				int currentUpdate = this->enemies[i].currentPath;

				if (currentPathUse != currentUpdate) {
					if (pathPos >= this->enemies[i].allPath[currentPathUse].pathPoints.size())
					{
						this->enemies[i].enemies[j].pathPos = 0;
						this->enemies[i].enemies[j].nextStepPath = 1;
						pathPos = 0;
						currentPathUse == currentUpdate;
						this->enemies[i].restart_reload();
					}
					else {
						if (this->enemies[i].currentPath > 0) { //on gère le retour au path 0

							this->enemies[i].currentPath--;
						}
						else {
							this->enemies[i].currentPath++;
						}
					}

				}



				if (pathPos >= this->enemies[i].allPath[currentPathUse].pathPoints.size())
				{
					

					this->enemies[i].enemies[j].pathPos = 0;
					this->enemies[i].enemies[j].nextStepPath = 1;
					pathPos = 0;
				}


				this->enemies[i].enemies[j].Speed = this->enemies[i].allPath[currentPathUse].speed;//set le sdpeed du path
				this->enemies[i].enemies[j].pathPos += this->enemies[i].enemies[j].Speed;
				
				if (pathPos > this->enemies[i].enemies[j].nextStepPath)
				{
					this->enemies[i].enemies[j].nextStepPath += 1;
					Vector2f curvePoint = this->enemies[i].allPath[currentPathUse].pathPoints[pathPos];
					Vector2f lastCurvePoint = this->enemies[i].enemies[j].lastPosition;

			
					Vector2f diffCurvePoint = Vector2f(lastCurvePoint.x- curvePoint.x, lastCurvePoint.y- curvePoint.y);

			
					this->enemies[i].enemies[j].shape.move(diffCurvePoint.x, diffCurvePoint.y);
					this->enemies[i].enemies[j].hitbox.move(diffCurvePoint.x, diffCurvePoint.y);

					this->enemies[i].enemies[j].lastPosition = Vector2f(curvePoint.x, curvePoint.y);
				}
				this->enemiesCenter.push_back(&this->enemies[i].enemies[j].center);


			}
				else{
					if (this->enemies[i].enemies[j].offset < this->enemies[i].enemies[j].get_time())
					{
						this->enemies[i].enemies[j].spawn = true;
						this->enemies[i].enemies[j].restart_reload();
						this->enemies[i].restart_reload();
					}
				}


				


		}
	}
	/*for (size_t i = 0; i < this->enemiesCenter.size(); i++) {
		cout << "(" << this->enemiesCenter[i]->x << ", " << this->enemiesCenter[i]->y << ")  |---|   ";
	

	}
	cout << endl;*/

}



/* Aim */
/* Pas opti bonjour ? */
Vector2f Gameplay::getAutoAim(Bullet bulletAim, Vector2f targetPos) {
	Vector2f dirTarget;
	Vector2f dirMax = Vector2f(0.04, 0.04); // vecteur du néo drift max de la bullet

	float x = bulletAim.shape.getPosition().x + bulletAim.sizeSprite.x / 2;
	float y = bulletAim.shape.getPosition().y + bulletAim.sizeSprite.y / 2;
	Vector2f bulletCenter = Vector2f(x, y);

	float xTarget = targetPos.x - bulletCenter.x;//(targetPos.x - bulletCenter.x) / (targetPos.x + bulletCenter.x);
	float yTarget = targetPos.y - bulletCenter.y;//(targetPos.y - bulletCenter.y) / (targetPos.y + bulletCenter.y);
	float multiplicator = 1 / (abs(xTarget) + abs(yTarget));


	float currentX = bulletAim.direction.x / bulletAim.speed;
	float currentY = bulletAim.direction.y / bulletAim.speed;

	float xTargetAdjust = xTarget * multiplicator;
	float yTargetAdjust = yTarget * multiplicator;


		//cout << "x adjust : " << xTargetAdjust << endl;
		//cout << "y adjust : " << yTargetAdjust << endl;
		if (abs(xTargetAdjust) > dirMax.x) {
			if (currentX - xTargetAdjust > 0) {
				xTargetAdjust = currentX  - dirMax.x;
				//cout << "x -- : " << currentX << " | " << xTargetAdjust << endl;
			}
			else if(currentX - xTargetAdjust < 0) {
				xTargetAdjust = currentX + dirMax.x;
				//cout << "x ++ : " << currentX << " | " << xTargetAdjust << endl;
			}
			else {
				xTargetAdjust = 0.5;
			}
		}
		if (abs(yTargetAdjust) > dirMax.y) {
			if (currentY - yTargetAdjust > 0) {
				yTargetAdjust = currentY - dirMax.y;
				//cout << "y -- : " << currentY << " | " << yTargetAdjust << endl;
			}
			else if(currentY - yTargetAdjust < 0) {
				yTargetAdjust = currentY + dirMax.y;
				//cout << "y ++ : " << currentY << " | " << yTargetAdjust << endl;
			}
			else {
				yTargetAdjust = 0.5;
			}
		}

		multiplicator = 1 / (abs(xTargetAdjust) + abs(yTargetAdjust));
	
		//cout << endl;

	dirTarget = Vector2f(xTargetAdjust * multiplicator, yTargetAdjust * multiplicator);
	//cout << dirTarget.x << " | " << dirTarget.y << endl;
	return dirTarget;
}
Vector2f Gameplay::getClosestEnemy(Bullet bulletAim) {
	map<float, Vector2f*>  distanceEnemy;
	//cout << " get -> " << bulletAim.bulletCenter.x << " | " << bulletAim.bulletCenter.y << endl;
	for (size_t i = 0; i < this->enemiesCenter.size(); i++)
	{
		float x2 = enemiesCenter[i]->x;
		float y2 = enemiesCenter[i]->y;
		float distance = sqrt(abs(
			powf((x2 - bulletAim.bulletCenter.x), 2) - /////////////// C4EST FAUX (non c'est vrai je crois)
			powf((y2 - bulletAim.bulletCenter.y), 2))
		);

		distanceEnemy[distance] = enemiesCenter[i];
		//cout << distance << " -> " << enemiesCenter[i]->x << " | " << enemiesCenter[i]->y << endl;
		
	}
	//cout << distanceEnemy.size() << " - " << this->enemiesCenter.size() <<endl;;
	for (map<float, Vector2f*>::iterator it = distanceEnemy.begin(); it != distanceEnemy.end(); ++it) {
		//cout << it->first << " - " << it->second->x << " | " << it->second->y << endl;
	}
	//cout << endl;
	
	if (!distanceEnemy.empty())
	{
		pair<float, Vector2f*> closestEnemy
			= *min_element(distanceEnemy.begin(), distanceEnemy.end(), CompareFirst());
		

		this->debugClosetEnemy = Vector2f(closestEnemy.second->x, closestEnemy.second->y);
		return Vector2f(closestEnemy.second->x, closestEnemy.second->y);
	}
	else
	{
		Vector2f straight = Vector2f(this->game.window.getSize().x, bulletAim.shape.getPosition().y + bulletAim.sizeSprite.y / 2);
		return straight;
	}
	

}


/* Bullets */
/* Pas opti 2 bonsoir ? */
void Gameplay::check_collision() {
	for (int b = 0; b < this->bullets.size(); b++) { // for bullets
		for (int i = 0; i < this->enemies.size(); i++) { // for Enemies
			if (i < this->enemies.size() && this->enemies.size()!=0) { // dunno if utile
				int jmax = this->enemies[i].enemies.size();
				for (int j = 0; j < jmax; j++) { // for character
						if (b < this->bullets.size()) {
							if (j < this->enemies[i].enemies.size()) { 
					if (this->enemies[i].enemies[j].spawn) { //if character is ready

								int xHitbox = this->enemies[i].enemies[j].hitbox.getPosition().x;
								int yHitbox = this->enemies[i].enemies[j].hitbox.getPosition().y;
								int xMaxHitbox = xHitbox + this->enemies[i].enemies[j].sizeSprite.x;
								int yMaxHitbox = yHitbox + this->enemies[i].enemies[j].sizeSprite.y;

								int xBullet = this->bullets[b].shape.getPosition().x;
								int yBullet = this->bullets[b].shape.getPosition().y;
								int xMaxBullet = xBullet + this->bullets[b].sizeSprite.x;
								int yMaxBullet = yBullet + this->bullets[b].sizeSprite.y;

								//if from player touch player ?
								if (
									(xMaxBullet > xHitbox && xMaxBullet < xMaxHitbox && yBullet > yHitbox && yBullet < yMaxHitbox) ||

									(xMaxBullet > xHitbox && xMaxBullet < xMaxHitbox && yMaxBullet > yHitbox && yMaxBullet < yMaxHitbox) ||

									(xBullet < xMaxHitbox && xBullet > xHitbox && yBullet > yHitbox && yMaxBullet < yMaxHitbox) ||

									(xBullet < xMaxHitbox && xBullet > xHitbox && yMaxBullet > yHitbox && yMaxBullet < yMaxHitbox)
									) {

									this->enemies[i].enemies[j].life -= this->bullets[b].damage;
									cout << "------------------- "
										<< this->enemies[i].enemies[j].life << "[" << this->bullets[b].damage << "] -------------------" << endl;



									RectangleShape t1 = RectangleShape(Vector2f((xMaxBullet - xBullet), (yMaxBullet - yBullet)));
									t1.setPosition(xBullet, yBullet);
									t1.setFillColor(Color::Red);

									this->colisions.push_back(t1);
									if (this->colisions.size() > 15) {
										this->colisions.erase(this->colisions.begin());

									}

									if (this->enemies[i].enemies[j].life <= 0) {
										this->enemies[i].enemies.erase(this->enemies[i].enemies.begin() + j); /////////// + i ?
										if (this->enemies[i].enemies.size() == 0) {
											jmax = j;
											this->enemies.erase(this->enemies.begin() + i);////////////////// + i ???
										}
									}

									this->bullets.erase(this->bullets.begin() + b);
								}
							}

						}
					}
				}
			}
		}
	}

}

void Gameplay::move_bullets() {

	for (size_t i = 0; i < this->bullets.size(); i++) {
		Bullet  currentBullet = this->bullets[i];
		//cout << "-- New bullet --" << endl;
			float x = currentBullet.shape.getPosition().x + currentBullet.sizeSprite.x / 2;
			float y = currentBullet.shape.getPosition().y + currentBullet.sizeSprite.y / 2;
			Vector2f bulletCenter = Vector2f(x, y);
			this->bullets[i].bulletCenter = bulletCenter;
		
			if (currentBullet.autoAim) {
				Vector2f targetDir;

				if (currentBullet.fromPlayer) {/////////////////////////////// calcul from bullet to closest enemy
					Vector2f closestEnemy = (getClosestEnemy(currentBullet));
					//cout << closestEnemy.x << " | " << closestEnemy.y << endl;
					targetDir = getAutoAim(currentBullet, closestEnemy);
				}

				else {/////////////////////////////// calcul from bullet to player
					targetDir = getAutoAim(currentBullet, this->player.center);
				}
				this->bullets[i].direction = targetDir * currentBullet.speed;
			}

			

			this->bullets[i].shape.move(this->bullets[i].direction);
			


		if (currentBullet.shape.getPosition().x < 0 || currentBullet.shape.getPosition().x > this->game.window.getSize().x
			|| currentBullet.shape.getPosition().y < 0 || currentBullet.shape.getPosition().y > this->game.window.getSize().y)
		{
			this->bullets.erase(this->bullets.begin() + i);

		}

	}
	//cout << "--------- END FRAME -----------" <<endl;


}

void Gameplay::create_bullets(Weapon weapon, bool fromPlayer, bool autoAim) {

	if (weapon.get_reload() < 0) {

		for (size_t i = 0; i < weapon.bullets.size(); i++)
		{
			Bullet bullet_ = weapon.bullets[i];

			Vector2f bulletCenter = Vector2f( //center in front of players, sprite
				player.center.x + player.sizeSprite.x / 2 + bullet_.startPosDiff.x,
				player.center.y - bullet_.sizeSprite.y / 2 + bullet_.startPosDiff.y
			);

			bullet_.shape.setPosition(bulletCenter);
			Vector2f targetDir;

			// Bullet from player
			if (bullet_.fromPlayer) {
			

				// Bullet with autoAim | calcul from player to closest enemy
				if (bullet_.autoAim) {
					bullet_.autoAim = true;
					Vector2f closestEnemy = (getClosestEnemy(bullet_));
					targetDir = getAutoAim(bullet_, closestEnemy);
				}
			
				//Bullet without autoAim
				else {
					targetDir = bullet_.direction;
				}
			}

			//Bullet from bot
			else {
				bullet_.fromPlayer = false;
				// Bullet with autoAim |  calcul from bullet to player
				if (bullet_.autoAim) {
					bullet_.autoAim = true;
					targetDir = getAutoAim(bullet_, this->player.center);
				}

				//Bullet without autoAim
				else {
					targetDir = bullet_.direction;
				}
			}

			bullet_.direction = targetDir * bullet_.speed;
			this->bullets.push_back(Bullet(bullet_)); 
		}


		weapon.restart_reload();
	}

}


/* Key manager */
void Gameplay::key_pressed_mgr() {

	while (this->game.window.pollEvent(this->game.event)) {
		if (this->game.event.type == Event::Closed) {
			this->chapterFinish = true;
			this->game.window.close();
		}


		if (this->game.event.type == sf::Event::KeyPressed) {
			if (this->game.event.key.code == sf::Keyboard::Escape) {
				this->game.in_game = false;
				this->chapterFinish = true;
				cout << "Quit game." << endl;
			}

			if (this->game.event.key.code == sf::Keyboard::D) {
				if (!this->debug) { this->debug = true; }
				else { this->debug = false; }
			}

			if (this->game.event.key.code == sf::Keyboard::P) {
				if (!this->pause) { this->pause = true; }
				else { this->pause = false; }
			}

		}

	}
}

void Gameplay::create_bullet_mgr() {
	/*
	if (Mouse::isButtonPressed(Mouse::)) {
		Weapon weapon = this->bulletMgr["bullet_ball_glass_blue"];
		create_bullets(weapon, true, true);
	}*/

	if (Keyboard::isKeyPressed(Keyboard::W)) {
		Weapon weapon = this->bulletMgr["bullet_ball_glass_blue"];
		create_bullets(weapon);
		//Weapon weapon2 = this->bulletMgr["bullet_ball_glass_red"];
		//create_bullets(weapon2);
	}

	if (Keyboard::isKeyPressed(Keyboard::Q)) {
		Weapon weapon = this->bulletMgr["bullet_ball_glass_red"];
		create_bullets(weapon);
	}

	if (Keyboard::isKeyPressed(Keyboard::X)) {
		Weapon weapon = this->bulletMgr["bullet_chuni_red"];
		create_bullets(weapon);
	}

	if (Keyboard::isKeyPressed(Keyboard::C)) {
		Weapon weapon = this->bulletMgr["special_chuni"];
		create_bullets(weapon);
	}
}




void Gameplay::chapter_run() {
	this->loadSprite();
	this->game_update();
}





void Gameplay::game_update() {
	this->chapterFinish = false;
	while (!chapterFinish) {


		if (!pause){
			this->enemiesCenter.clear();
			this->enemiesHitbox.clear();

			this->move_enemies();
		
			this->move_player();

			this->move_bullets();
			this->create_bullet_mgr();

			this->check_collision();
			
		}
		this->draw_gameplay();
		this->key_pressed_mgr();
		this->game.fps_update(this->bullets.size(), this->enemiesCenter.size());
		
	}
	this->chapterFinish = true;
	//delete[] this->bullets;
	this->bullets.clear();
	this->enemies.clear();
	/* delete le background + le perso ?*/
	//delete this->player;
}

void Gameplay::draw_gameplay() {

	this->game.window.clear();
	this->game.window.draw(this->background);

	/* Draw bullet */
	for (size_t i = 0; i < this->bullets.size(); i++)
	{
		this->game.window.draw(this->bullets[i].shape);
		//cout << "x : " << this->bullets[i].direction.x << "y : " << this->bullets[i].direction.y << endl;

		if (this->debug) { // DEBUG
		//bullet aim
		for (size_t j = 0; j < 15; j++) {
			sf::CircleShape shape(2);
			shape.setFillColor(sf::Color(221, 51, 255));
			shape.setPosition(this->bullets[i].bulletCenter.x + this->bullets[i].direction.x * (3 * j), 
				this->bullets[i].bulletCenter.y + this->bullets[i].direction.y * (3 * j));

			this->game.window.draw(shape);
		}

		//enemy target 
		sf::RectangleShape shape(sf::Vector2f(120, 120));
		shape.setPosition(this->debugClosetEnemy.x- shape.getSize().x/2, this->debugClosetEnemy.y - shape.getSize().y / 2);
		this->game.window.draw(shape);
		}
	}


	/* Draw ennemies */
	for (size_t i = 0; i < this->enemies.size(); i++) {
		for (size_t j = 0; j < this->enemies[i].enemies.size(); j++) {
			if (this->enemies[i].enemies[j].spawn) {

				this->game.window.draw(this->enemies[i].enemies[j].shape);
				if (this->debug)  { // DEBUG
				this->game.window.draw(this->enemies[i].enemies[j].hitbox);
				}
			}
		}


		if (this->debug) { // DEBUG
		/* Draw path ennemies */
		if (this->enemies[i].enemies[0].spawn) {

			int currentPathUse = this->enemies[i].currentPath;


			Vector2f curvePoint;
			for (float m = 0; m < this->enemies[i].allPath[currentPathUse].pathPoints.size(); m++) {
				curvePoint = this->enemies[i].allPath[currentPathUse].pathPoints[m];
				Vector2f lastCurvePoint = this->enemies[i].startEnemyPosition;

				Vector2f diffCurvePoint = Vector2f(lastCurvePoint.x - curvePoint.x, lastCurvePoint.y - curvePoint.y);

				sf::CircleShape circle;
				circle.setRadius(3);
				circle.setFillColor(sf::Color::Green);

				circle.setPosition(diffCurvePoint.x, diffCurvePoint.y);

				this->game.window.draw(circle);
			}
		}

		}
		
	}

	

	if (this->debug) { // DEBUG
		/* Draw impact */
		for (size_t i = 0; i < this->colisions.size(); i++) {
			this->game.window.draw(this->colisions[i]);
			
		}
	}
	

	
	this->game.window.draw(player.shape);
	this->game.window.draw(player.hitbox);
	this->game.window.draw(this->game.info);
	this->game.window.display();
}









//Var
	//Vector2f mousePosWindow;
	//Vector2f aimDir;
	//Vector2f aimDirNorm;

//aimDir = mousePosWindow - this->player.center;
		//aimDirNorm = aimDir / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
		//mousePosWindow = Vector2f(Mouse::getPosition(this->game.window));
		//this->enemyCenter.push_back(&mousePosWindow);
