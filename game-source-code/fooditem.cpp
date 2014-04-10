#include "fooditem.h"

fooditem::fooditem(xy startPos):_pos(startPos),_active(0)
{
	srand(time(NULL));
	_foodType=rand()%4;
}

int fooditem::getFoodType() const
{
	return _foodType;
}

bool fooditem::isActive() const
{
	return _active;
}

void fooditem::deactivate()
{
	_active=0;
}

xy fooditem::pos() const
{
	return _pos;
}

void fooditem::changeFoodType(xy startPos) 
{
	_foodType++;
	_foodType=_foodType%4;
	_active=1;
}

void fooditem::activate()
{
	_active=1;
}