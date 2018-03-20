#pragma once


#include "charbuffer.h"
#include "Figure.h"




class Projectile
{
public:
	Projectile();
	Projectile(CharBuffer *_buffer, Figure *_player, int _direction);
	~Projectile(){}

	void  Movement(vector <Figure*> &_enemies);

	void CollisionCheck(vector <Figure*> &_enemies);

	void DestructProjectile();
	 
	void ResetPreProjectilePos();

	bool CheckNextField();

	int GetPosX() {
		return PosX;
	}

	int GetPosY() {
		return PosY;
	}

	char GetName() {
		return Name;
	}

protected:
	CharBuffer *bufferref;
	Figure *player;
	char Name;
	int Damage = 1;
	int PosX;
	int PosY;
	int direction;

};
