#pragma once

#include "Figure.h"
#include "charbuffer.h"

using namespace std;

class DiagonalEnemy : public Figure
{
public:

	DiagonalEnemy(const char _name, CharBuffer *_buffer);

	void ResetPreEnemiePos();

	void CheckNextField();

	void Movement();

	void Attack();

	bool TakeDamage();

private:
	bool direction = true;	// true = Links; false = Rechts

};
