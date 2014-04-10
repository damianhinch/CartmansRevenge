#ifndef DRAGON_H 
#define DRAGON_H

#include "monster.h"
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

//! Models a specific type of monster, namely the fire-breathing dragon.
/*! The dragon has a different attack function to that possesed by the basic monster type (Clyde-Frog), 
which needs to be managed seperately. The virtual attack function of monster is implemented in
a manner that models fire breathing.
\author Damian Hinch, Joseph Penn
\version v0.3.8
\date 25/09/2012
*/


class dragon: public monster
{
public:
	dragon(xy startPos):monster(startPos){}

//! Attack function for the dragon.
/*! Here the virtual attack function found in the base class is implemented.
This function allows the dragon to attack in the same way as the basic monster type
(Clyde-frog), as well as adding the flame-blowing option if the user
is within the required range along the x-axis.
\param playerPos digdug's current position
\return 1 if digdug has been killed by this monster.
*/

	virtual bool attack(xy PlayerPos); 
};

#endif