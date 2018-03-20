
#include "Projectile.h"
#include "Player.h"
#include "charbuffer.h"

#include <iostream>
#include <vector>
using namespace std;

Projectile::Projectile() {
	cout << "Construct Default Projectile" << endl;
}

Projectile::Projectile(CharBuffer *_buffer, Figure *_player, int _direction){
	Name = 'o';
	bufferref = _buffer;
	player = _player;
	PosX = _player->GetPosX();
	PosY = _player->GetPosY();
	direction = _direction;
}

void  Projectile::ResetPreProjectilePos() {
	 if(bufferref->GetCharAt(this->PosX, this->PosY) != player->GetName())
		bufferref->SetCharAt(this->PosX, this->PosY, bufferref->GetDefaultChar());
}

bool Projectile:: CheckNextField() {
	 switch (direction) {
		 case 1: {
			 if (bufferref->GetCharAt(PosX, PosY - 1) == '#')
				 return false;
			 else
				 return true;
			 break;
		 }
		 case 2: {
			 if (bufferref->GetCharAt(PosX + 1, PosY) == '#')
				 return false;
			 else
				 return true;
			 break;
		 }
		 case 3: {
			 if (bufferref->GetCharAt(PosX, PosY + 1) == '#')
				 return false;
			 else
				 return true;
			 break;
		 }
		 case 4: {
			 if (bufferref->GetCharAt(PosX - 1, PosY) == '#')
				 return false;
			 else
				 return true;
			 break;
		 }
		 default:
			 return false;
			 break;
	}
 }

void Projectile::CollisionCheck(vector <Figure*> &_enemies) {
	for (unsigned i = 0; i < _enemies.size(); i++) {
		if (this->GetPosX() == _enemies.at(i)->GetPosX()) {
			if (this->GetPosY() == _enemies.at(i)->GetPosY()) {
				_enemies.at(i)->RemoveFigure(_enemies);
				this->DestructProjectile();
			}
		}
	}
}

void Projectile::Movement(vector <Figure*> &_enemies) {

	if (CheckNextField()) {
		ResetPreProjectilePos();
		switch (direction) {
			case 1: {
				PosY -= 1;
				break;
			}
			case 2: {
				PosX += 1;
				break;
			}
			case 3: {
				PosY += 1;
				break;
			}
			case 4: {
				PosX -= 1;
				break;
			}
			default:
				break;
		}
		bufferref->SetCharAt(this->PosX, this->PosY, this->Name);
		this->CollisionCheck(_enemies);
		
	}
	else {
		this->DestructProjectile();		
	}
}

void Projectile::DestructProjectile() {

 	ResetPreProjectilePos();	// von Spielfeld entfernen

	Player *_player = (Player*)player;
	_player->DeleteProjectile(this);
}


