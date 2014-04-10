#ifndef OBJECTS_H
#define OBJECTS_H

#include "objects.h"
#include "tunnels.h"

//! Models a generic monster which is used as a base class for the other monster types.
/*! The other monster types inherit from this class.
They have the ability to implement their own attack function (it is virtual here).
Other monsters that inherit from this class MUST implement their own attack functions in
order to take advantage of the position-storing functionality.
\author Damian Hinch, Joseph Penn
\version v0.3.8
\date 25/09/2012
*/

class monster
{
public:
	monster(xy startPos);			

//! Makes the decision for where the monster will move next.
/*! Does not move the monster, but sets its direciton to
the direction in which it will move for the next series of steps.
\param playerPos digdug's current position
\param tunnelNW the network of tunnels into which the monster is allowed to move
\param squareWidth the size of the grid
*/
	void moveDecision(tunnels& tunnelNW,xy& playerPos,int squareWidth); 
	void move(int stepSize); 
	bool is_alive() const;
	xy pos() const;
	void setx(int x);
	void sety(int y);
	void setpos(xy posToSet);
	void setDir(int dir);

//! Returns the number of times the monster has been stuck.
/*! When the monster cannot make a constructive move, this counter
is incremented. This allows the main game to know when to make the 
monsters enter the disembodied state.
\return times monster has reported that it is stuck.
*/
	int gettimeStuck() const;
	bool isdisembodied() const;

//! Sets the monster's state to disembodied.
/*! This is called when the monster is stuck a certain number of times.
\param whereToGo the current position of digdug, i.e. the position to move to before re-embodying
*/
	void disembody(xy whereToGo);
	void reembody();
	int getCountDisembody();
	int getDir() const;
	int isHarpooned() const; 

//! Called when the monster has been harpooned.
/*! Sets the condition that the monster has been shot by the harpoon.
*/
	void harpooned(); 
	void unharpooned();

//! Increases the harpoon counter.
/*! The harpoon counter is increased whilst the monster is in the harpooned state and decreased if
the harpoon is released before the swelling sequence has terminated in the monster's demise.
*/
	void increaseCounter();
	void decreaseCounter();

//!  A virtual attack function that must be implemented by any monster who inherits from this class.
/*! This function currently has no implementation and always returns that the attack has missed.
The different types of monster will implement this function differently, depending on how they
can attack.
\param ddpos digdug's current position
\return 1 if the monster has killed digdug, 0 otherwise
*/
	virtual bool attack(xy ddpos)=0;//returns 1 if dd was killed by this monster, 0 if not

//! Resets the monster to its initial position.
/*! NOTE: if the monster has been killed, it will no longer
be present in the vector and won't be recreated again.
*/
	void resetMons();
	bool isAttacking();

//!  Gives up the search for a valid tunnel position in which to re-embody.
/*! If a disembodied monster cannot find a suitable tunnel position in which
to re-embody within a certain period of time, this function is called in order
to instruct the monster to give up its search and return to the position at
which it initially entered the disembodied state.  Thus, it avoids any errors 
that might occur should the monster remain in the disembodied state indefinitely 
due to its failure to locate a suitable tunnel position in which to re-embody.
*/
	void giveUpTunnelSearch();
	int getAnimCount() const;
private:
	xy _startPos; /*!< Set when constructed, used to reset monster to original position betweeen lives */  
	bool _dir[5]; /*!< Stores the current direction of the monster*/ 
	xy _lastPos; /*!< Stores the monster's last position for the moveDecision algorithm*/  
	xy _disembodiedStartPt;/*!< Position where monster entered the disembodied state */  
	int _countDisembody; 
	int _harpoonedCounter;
	xy _disembodiedPoint; /*!< Position where monster aims to move to while in disembodied state */  
	int _timeStuck;
	int _animCount; /*!< The current animation state that should be drawn. Increased for every move in downwards direction */  
protected:
	bool _alive; 
	bool _disembodied;
	xy _pos;	
	int _curDir; 
	bool _isAttacking; 
};

#endif