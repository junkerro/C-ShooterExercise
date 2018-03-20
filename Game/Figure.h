#pragma once

#include "charbuffer.h"

#include <iostream>
#include <vector>
using namespace std;

class Figure
{
public:

	virtual void  Movement(){}

	virtual void  Attack() = 0;

	virtual bool  TakeDamage() = 0 ;

	int GetPosX();

	int GetPosY();

	char GetName();

	virtual void RemoveFigure(vector <Figure*> &_enemies);

protected:
	Figure() {}
	virtual ~Figure() {}
	CharBuffer  *bufferref;	
	char Name;
	int Life = 1;
	int Speed = 1;
	int Damage = 1;
	int PosX;
	int PosY;
};
