#ifndef CLYDE_H
#define CLYDE_H

#include "monster.h"
#include "objects.h"

//! Models a basic monster with the standard (non-flame) attack.
/*! Unlike the dragon, the clyde-frog monster can only attack
digdug when he occupies the same position in the gamescreen. He does not possess the dragon's ability 
to attack from range. 
\author Damian Hinch, Joseph Penn
\version v0.3.8
\date 25/09/2012
*/


class clydefrog: public monster
{
public:
	clydefrog(xy startPos):monster(startPos){};

//! Attack function for the basic monster type.
/*!This function implements the virtual attack found
in monster. The attack function returns whether or
not this monster has caught digdug.
\param ddpos digdug's current position.
\return 1 if he has caught digdug, 0 otherwise
*/

	virtual bool attack(xy ddpos);
private:
	
};

#endif