#pragma once

#include "Figure.h"
#include "charbuffer.h"

using namespace std;

class HorizontalEnemy : public Figure
{
public:

	HorizontalEnemy(const char _name, CharBuffer *_buffer);

	void ResetPreEnemiePos();

	void CheckNextField();

	void Movement();

	void Attack();

	bool TakeDamage();

private:
	bool direction = true;	// true = Links; false = Rechts

};
