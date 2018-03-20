
#include "Figure.h"
#include "charbuffer.h"
#include "HorizontalEnemy.h"

#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


using namespace std;

	HorizontalEnemy::HorizontalEnemy(const char _name, CharBuffer *_buffer) {
		int x = _buffer->GetSizeX()-4;
		int y = _buffer->GetSizeY()-4;
		Name = _name;
		cout << "";
		PosX = rand() % x + 2;
		PosY = rand() % y + 2;
		bufferref = _buffer;
		_buffer->SetCharAt(GetPosX(), GetPosY(), GetName());
	}	

	void HorizontalEnemy::ResetPreEnemiePos() {
		bufferref->SetCharAt(PosX, PosY, bufferref->GetDefaultChar());
	}

	void HorizontalEnemy::CheckNextField() {
		if (direction) {
			if (bufferref->GetCharAt(PosX - 1, PosY) == '#')
				direction = false;
		}
		else {
			if (bufferref->GetCharAt(PosX + 1, PosY) == '#')
				direction = true;
		}		
	}

	void HorizontalEnemy::Movement() {
		
		ResetPreEnemiePos();
		CheckNextField();

		if (direction)
			PosX -= 1;
		else
			PosX += 1;

		bufferref->SetCharAt(GetPosX(), GetPosY(), GetName());
	}

	void HorizontalEnemy::Attack() {
		cout << "ENEMIE Attack" << endl;
	}

	bool HorizontalEnemy::TakeDamage() {
		cout << "ENEMIE TakeDamage" << endl;
		return true;
	}
