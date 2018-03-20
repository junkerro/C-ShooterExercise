#pragma once

#include "Projectile.h"
#include "charbuffer.h"
#include "Figure.h"

#include <vector>
#include <iostream>

using namespace std;

class Player : public Figure
{
public:

	//Player();

	Player(const char _name, CharBuffer *_buffer);

	bool Control(char _key, vector <Figure*> _enemies);

	void ResetPrePlayerPos();

	bool CheckNextField(char _key);

	void Movement(char _key);

	void Attack();

	bool CollisionCheck(vector <Figure*> _enemies);

	bool TakeDamage();

	vector <Projectile*> GetProjectiles();

	void DeleteProjectile(Projectile * _projectile);



private:
	int direction;	// 1 = Oben; 2 = Rechts; 3 = Unten; 4 = Links
	vector <Projectile*> projectiles;
};
