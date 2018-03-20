
#include "Figure.h" 
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int Figure::  GetPosX() {
	return PosX;
}

int Figure::GetPosY() {
	return PosY;
}

char Figure::GetName() {
	return Name;
}

 void Figure::RemoveFigure(vector <Figure*> &_enemies) {
	vector <Figure*> ::iterator it;
	int pos = find(_enemies.begin(), _enemies.end(), this) - _enemies.begin();
	it = _enemies.begin() + pos;
	_enemies.erase(it);
}


