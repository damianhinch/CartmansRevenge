#ifndef DIGDUG_H 
#define DIGDUG_H

#include "objects.h"
//! Models the game's main character (digdug).
/*! The main character's attributes and position on the game screen
are stored and processed within this class. 
\author Damian Hinch, Joseph Penn
\version v0.3.8
\date 25/09/2012
*/


class digdug
{
public:
	digdug();			

//! Moves digdug in the direction requested by the player.
/*! Moves digdug a single step in the direction specified by 
the dir array. If NOTHING is set to 1, digdug will not be moved in any direction and 
his direction will be set to STOP. Such is the case occurs when digdug is firing the harpoon.
\param dir an array that corresponds to the four directions in which digdug can move
\param step the amount by which to move
*/
	void move(bool dir[],int step);	

//! Decreases digdug's lives and returns whether or not he is still alive.
/*!This is called when a monster successfully attacks digdug. This function is 
used to determine whether or not the game loop should continue.
\return 1 if digdug is dead, 0 if he has lives remaining.
*/
	bool dead();					
	xy pos();
	void setx(int);
	void sety(int);
	void setpos(xy);
	int getDir() const;
	int getScore() const;
	void increaseScore(int increment);
	int getLives() const;

//! Restores all of digdug's lives.
/*! When the game restarts, digdug is restored to his full complement of 3 lives.
*/
	void restoreLives();
private:
	xy _pos;	
	int _lives;
	int _curDir; /*!< The current direction in which digdug is facing */  
	int _score;
};

#endif