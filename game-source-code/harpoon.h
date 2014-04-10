#ifndef HARPOON_H 
#define HARPOON_H
#include "objects.h"

//! Models digdug's harpoon weapon
/*! The harpoon has various states which need to be collected together
so that its interactions with other objects in the game can be managed 
appropriately. The harpoon is created when the user presses the space key and 
deactivated when its deployment is complete. 
\author Damian Hinch, Joseph Penn
\version v0.3.8
\date 25/09/2012
*/


class harpoon
{
public:
	harpoon();

//! Moves the harpoon tip by the desired step amount.
/*! When digdug deploys the harpoon weapon, it is moved in the desired
direction by incrementing/decrementing the x (or y) coordinate by the amount of step.
The length variable is incremented when this function is called, storing the amount by
which the cord has been extended.
\param dir digdug's direction (i.e the direction in which harpoon will be fired)
\param step the amount by which to move harpoon
*/
	void move(int dir,int step);
	bool isActive() const;
	xy pos() const;
	void activate(xy pos);
	void deactivate();
	int getLength() const;

//! Start whenever the harpoon is deployed.
/*! Whenever the user deploys the harpoon this function 
is called, regardless of whether or not a monster has been
hit.
*/
	void harpooning(); 

//! Stops the harpooning process.
/*! This function is called to terminate the harpooning process when the harpoon 
reaches a wall, the cord length exceeds it's maximum allowed value 
(some constant) or the user releases the spacebar key.*/
	void unharpooning();

//! Indicates that a monster is hit with the harpoon.
/*! When the harpoon hits a monster this function is called,
initiating the animation swelling sequence for the impaled monster.
*/
	bool isHarpooning() const;

private:
	xy _tipPos;
	bool _active;
	int _length; /*!< Length of the harpoon cord. Used for drawing the cord and limiting the harpoon's range */  
	bool _isHarpooning;
};

#endif