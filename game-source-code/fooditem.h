#ifndef FOODITEM_H
#define FOODITEM_H

#include "objects.h"
#include <ctime>
#include <cstdlib>

//! Models a bonus food item, consumption of which gives digdug extra points.
/*! The food can have one of four states, each of which 
corresponds to a different food type. 
\author Damian Hinch, Joseph Penn
\version v0.3.8
\date 25/09/2012
*/


class fooditem
{
public:
	fooditem(xy startPos);
	int getFoodType() const;
	void activate();
	bool isActive() const;
	void deactivate();
	xy pos() const;

//! Changes the type of food that is to be drawn to screen.
/*! Cycles between the 4 different food types within the course of a level.
Ensures that the same food type is not repeated during a level.
*/
	void changeFoodType(xy startPos);
private:
	xy _pos;
	int _foodType;
	bool _active;
};

#endif