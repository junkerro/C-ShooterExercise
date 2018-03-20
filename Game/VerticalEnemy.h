#pragma once

#include "Figure.h"
#include "charbuffer.h"

using namespace std;

class VerticalEnemy : public Figure
{
public:

	VerticalEnemy(const char _name, CharBuffer *_buffer);

	void ResetPreEnemiePos();

	void CheckNextField();

	void Movement();

	void Attack();

	bool TakeDamage();

private:
	bool direction = true;	// true = Oben; false = Unten
};
