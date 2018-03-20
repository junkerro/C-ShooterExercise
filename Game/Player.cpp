
#include "Figure.h"
#include "charbuffer.h"
#include "Projectile.h"
#include "Player.h"

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

	//Player() {}

	Player::Player(const char _name, CharBuffer *_buffer) {
		Name = _name;
		PosX = (_buffer->GetSizeX()) / 2;
		PosY = (_buffer->GetSizeY()) / 2;
		direction = 2;
		bufferref = _buffer;
		_buffer->SetCharAt(GetPosX(), GetPosY(), GetName());	// Spieler im Feld Positionieren
	}

	bool Player::Control(char _key, vector <Figure*> _enemies) {
		if (_key == ' ') {
			Attack();
			return false;
		}
		else{
			Movement(_key);
			if(CollisionCheck(_enemies))
				return true;
			else
				return false;
		}
	}

	void Player::ResetPrePlayerPos() {
		bufferref->SetCharAt(PosX, PosY, bufferref->GetDefaultChar());
	}

	bool Player::CheckNextField(char _key) {
		switch (_key) {
		case 'w': {
			if (bufferref->GetCharAt(PosX, PosY - Speed) == '#' )
				return false;
			else
				return true;
			break;
		}
		case 'a': {
			if (bufferref->GetCharAt(PosX - Speed, PosY ) == '#' )
				return false;
			else
				return true;
			break;
		}
		case 's': {
			if (bufferref->GetCharAt(PosX, PosY + Speed) == '#' )
				return false;
			else
				return true;
			break;
		}
		case 'd': {
			if (bufferref->GetCharAt(PosX + Speed, PosY ) == '#')
				return false;
			else
				return true;
			break;
		}
		default:
			return true;
			break;
		}
	}

	void Player::Movement(char _key) {
		_key = tolower(_key);

		if (CheckNextField(_key)) {
			ResetPrePlayerPos();
			switch (_key) {
			case 'w': {
				PosY -= Speed;
				direction = 1;
				break;
			}
			case 'a': {
				PosX -= Speed;
				direction = 4;
				break;
			}
			case 's': {
				PosY += Speed;
				direction = 3;
				break;
			}
			case 'd': {
				PosX += Speed;
				direction = 2;
				break;
			}
			default:
				break;
			}

			bufferref->SetCharAt(GetPosX(), GetPosY(), GetName());
		}
	}

	void Player::Attack() {
		projectiles.push_back( new Projectile(bufferref, this, direction));		
	}

	bool Player::CollisionCheck(vector <Figure*> _enemies) {
		int enemie_count = _enemies.size();
		bool check = false;

		for (int i = 0; i < enemie_count; i++) {
			if (this->GetPosX() == _enemies.at(i)->GetPosX()) {
				if (this->GetPosY() == _enemies.at(i)->GetPosY()) {
					return true;
				}
			}
		}
		return check;
	}

	bool Player::TakeDamage() {
		cout << "TakeDamage" << endl;
		cout << "GameOverNoob!" << endl;
		return true;
	}

	vector <Projectile*> Player::GetProjectiles(){
		return projectiles;
	}

	void Player::DeleteProjectile(Projectile * _projectile) {

		vector <Projectile*> ::iterator it;

		int pos = find(projectiles.begin(), projectiles.end(), _projectile) - projectiles.begin();	// Projektile aus Vector suchen und entfernen
		it = projectiles.begin() + pos;
		projectiles.erase(it);
		delete _projectile;
	}
