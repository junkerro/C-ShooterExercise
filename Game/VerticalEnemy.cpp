
#include "Figure.h"
#include "charbuffer.h"
#include "VerticalEnemy.h"

#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

	VerticalEnemy:: VerticalEnemy(const char _name, CharBuffer *_buffer) {
		int x = _buffer->GetSizeX() - 4;
		int y = _buffer->GetSizeY() - 4;
		Name = _name;
		PosX = rand() % x + 2;
		PosY = rand() % y + 2;
		bufferref = _buffer;
		_buffer->SetCharAt(GetPosX(), GetPosY(), GetName());
	}

	void VerticalEnemy:: ResetPreEnemiePos() {
		bufferref->SetCharAt(PosX, PosY, bufferref->GetDefaultChar());
	}

	void VerticalEnemy:: CheckNextField() {
		if (direction) {
			if (bufferref->GetCharAt(PosX, PosY - 1) == '#')
				direction = false;
		}
		else {
			if (bufferref->GetCharAt(PosX, PosY +1) == '#')
				direction = true;
		}
	}

	void VerticalEnemy:: Movement() {

		ResetPreEnemiePos();
		CheckNextField();

		if (direction)
			PosY -= 1;
		else
			PosY += 1;

		bufferref->SetCharAt(GetPosX(), GetPosY(), GetName());
	}

	void VerticalEnemy:: Attack() {
		cout << "ENEMIE Attack" << endl;
	}

	bool VerticalEnemy:: TakeDamage() {
		cout << "ENEMIE TakeDamage" << endl;
		return true;
	}

