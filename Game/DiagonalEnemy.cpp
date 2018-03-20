
#include "Figure.h"
#include "charbuffer.h"
#include "DiagonalEnemy.h"

#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


using namespace std;

DiagonalEnemy:: DiagonalEnemy(const char _name, CharBuffer *_buffer) {
	int x = _buffer->GetSizeX() - 4;
	int y = _buffer->GetSizeY() - 4;
	Name = _name;
	cout << "";
	PosX = rand() % x + 2;
	PosY = rand() % y + 2;
	bufferref = _buffer;
	_buffer->SetCharAt(GetPosX(), GetPosY(), GetName());
	}

	void DiagonalEnemy:: ResetPreEnemiePos() {
		bufferref->SetCharAt(PosX, PosY, bufferref->GetDefaultChar());
	}

	void DiagonalEnemy:: CheckNextField() {
		if (direction) {
			if (bufferref->GetCharAt(PosX - 1, PosY) == '#' ||
				bufferref->GetCharAt(PosX , PosY - 1) == '#')
				direction = false;
		}
		else {
			if (bufferref->GetCharAt(PosX + 1, PosY) == '#' ||
				bufferref->GetCharAt(PosX, PosY + 1) == '#')
				direction = true;
		}
	}

	void DiagonalEnemy:: Movement() {


		ResetPreEnemiePos();
		CheckNextField();

		if (direction) {
			PosX -= 1;
			PosY -= 1;
		}
		else {
				PosX += 1;
				PosY += 1;
			}

		bufferref->SetCharAt(GetPosX(), GetPosY(), GetName());
	}

	void DiagonalEnemy:: Attack() {
		cout << "ENEMIE Attack" << endl;
	}

	bool DiagonalEnemy:: TakeDamage() {
		cout << "ENEMIE TakeDamage" << endl;
		return true;
	}



