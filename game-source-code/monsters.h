#ifndef MONSTERS_H
#define MONSTERS_H

#include "monster.h"
#include "objects.h"
#include "tunnels.h"
#include <vector>
#include <cmath>
#include <typeinfo>

//! Manages the group of monsters that chase digdug.
/*! Adds bulk functionality, allowing for quick
control of all the monsters via the use of a single 
function call.  Also manages the vector of monsters and deletes any
that have been killed by digdug or crushed by falling rocks.
The vector here stores pointers to the base class. The actual
monsters are dynamically cast at run time. The vector will 
therefore hold different monster types, and all of its functions
work with either of the two monster types.
\author Damian Hinch, Joseph Penn
\version v0.3.8
\date 25/09/2012
*/

class monsters
{
public:
	void addMonster(monster* monst);

//! Kills the monster at the specified position.
/*! This function deletes the monster from the vector. 
This prevents it from being revived accidentally.  
Additionally, the FOR loops that traverse the vector perform faster.
\param monst a pointer to the base type monster.
*/
	void killMonster(int index);

//! Makes the decision for where the monsters will move next.
/*! Does not move the monster, but sets its direciton to
the direction in which it will move for the next series of steps.
\param playerPos digdug's current position
\param tunnelNW the network of tunnels into which the monster is allowed to move
\param squareWidth the size of the grid
*/
	void moveDecisionMonsters(tunnels& tunnelNW,xy& playerPos,int squareWidth);//moves all monsters. Ensures there is no overlap
	void moveMonsters(int stepSize);
	int getSize() const;
	xy getithPos(int i) const;

//! Uses the appropriate attack function in order to try and attack digdug.
/*! The virutal attack function of monster is overloaded in 
different ways. This function cycles through the vector, allowing each monster
to attack in a manner in accordance with it's characteristics - i.e: normal
or flame attack.
\param playerPos digdug's current position
\return 1 if digdug has been killed by any of the monsters in the vector.
*/
	bool attack(xy playerPos) const;
	bool isAlive(int index) const;
	void setithpos(int index,xy pos);
	bool isDisembodied(int index) const;

//! Sets the monsters at the specified position to enter the disembodied state.
/*! This is called when the monster is deemed to be stuck for a certain number of moves.
\param playerPos the current position of digdug, i.e. the position to move to before becoming re-embodied
\param index which monster in the vector to disembody
*/
	void setDisembodied(int index,xy playerPos);
	void reembody(int index);
	vector<bool> whosStuck(); 
	int getCountDisembodyIth(int index);
	int isShot(xy harpoonPos); 
	int getithDir(int index) const;
	monster* getithMonster(int index) const;

//! Called when the monster at the specified index has been harpooned.
/*! Sets that monster as having been shot by the harpoon.
*/

	void harpoonithMonster(int index);
	void unharpoonithMonster(int index);

//! Increases the harpoon counter of the monster at the specified index.
/*! The harpoon counter is increased whilst the monster is harpooned and decreased if
the harpoon is released before the swelling sequence has terminated in the monster's demise.
*/
	void increaseHarpoonCount(int index);
	int getHarpoonCount(int index) const;
	void decreaseHarpoonCount(int index);


//! Resets all the monsters to their initial positions.
/*! NOTE: if the monster has been killed, it will no longer
be present in the vector and will thus not be recreated.
*/
	void resetAllMonsts();
	bool getithIsAttacking(int index) const;


//!  Gives up the search for a valid tunnel position in which to re-embody.
/*! If a disembodied monster cannot find a suitable tunnel position in which
to re-embody within a certain period of time, this function is called in order
to instruct the monster to give up its search and return to the position at
which it initially entered the disembodied state.  Thus, it avoids any errors 
that might occur should the monster remain in the disembodied state indefinitely 
due to its failure to locate a suitable tunnel position in which to re-embody.
*/
	void giveUpTunnelSearch(int index);

//! Deletes all monsters from the vector.
/*! Called in order to kill (i.e delete) all 
the monsters that are currently in the vector.
*/
	void killAllMonsts();
private:
	vector<monster*> _monstVec; 
};

#endif