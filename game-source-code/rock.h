#ifndef ROCKS_H
#define ROCKS_H

#include "objects.h"
#include <cmath>

//! Rock models a rock (coffin) that can fall and crush the game characters.
/*! Rocks are placed around the gamescreen by the initialiser 
(levelCreator). They can be disturbed by the movements of
digdug, if he creates a new tunnel underneath it' position. Following such an event 
they fall through the tunnels and will crush any character whose position they pass through. 
They stop their descent when they hit the ground.
\author Damian Hinch, Joseph Penn
\version v0.3.8
\date 25/09/2012
*/

class rock
{
public:

//! Constructor used to set up inital rock position and orientation.
/*!Each rock that is created needs to be given a position and orientation in 
which it should be drawn.
\param leftRight if = 1, rock faces left, else right
*/
	rock(xy pos,bool leftRight);
	bool isActive() const;
	int getTimeActive() const;
	bool isBottom() const;
	void activate();
	void deactivate();
	void move(int step);
	xy pos() const;
	bool getLeftRight() const;
	void startFalling();
	void stopFalling();
	bool isFalling() const;
	void open();
	bool isOpen() const;
	bool hasFallen() const;

//! Tells the main loop if digdug is near a rock.
/*! If digdug is directly next to a rock, this function will
return the direction in which digdug CANNOT move. This prevents digdug
from walking though rocks. 
\param pos takes a single coordinate that is digdug's current position
\return returns an integer which corresponds to the direction (enum=UP,DOWN,LEFT,RIGHT)
*/
	int isNearRock(xy pos) const; 
	void setPos(xy pos);
private:
	xy _pos; 
	bool _active; /*!< Whether the rock is in gameplay (i.e. rocks that haven't been used up) */  
	bool _bottom;/*!< Rocks that have hit the ground, but that are still active i.e. digdug can't walk through them */  
	bool _leftRight; /*!< Whether the rock is facing left or right; 1=left */  
	bool _falling;/*!<Whether the rock is currently falling. This is the only state in which the rock can kill a character */  
	bool _open; /*!< For drawing purposes, controls "coffin-open" animation */  
	bool _hasFallen;/*!< Whether the coffin has fallen already (for animation purposes) */  
};

#endif
