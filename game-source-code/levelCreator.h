#ifndef _LEVEL_CREATOR_H
#define _LEVEL_CREATOR_H

#include "objects.h"
#include "digdug.h"
#include "monsters.h"
#include "tunnels.h"
#include "rock.h"
#include "clydefrog.h"
#include "dragon.h"

#include <fstream>
#include <string>
#include <sstream>

#include <boost/smart_ptr.hpp>
using boost::scoped_ptr;
using boost::shared_ptr;

typedef boost::shared_ptr<rock> rock_ptr;

//! Creates a level from a textfile by populating the objects sent to it.
/*! The class has the ability to read in textfiles of the specified format 
and populate/instantiate the objects that are sent through. In its current state
the class handles less functionality than it could.  With a degree of modification
it could take over further responsibilities from the main loop.
\author Damian Hinch, Joseph Penn
\version v0.3.8
\date 25/09/2012
*/


class levelCreator{
public:
	levelCreator(const int maxLevel):_maxLevel(maxLevel){};

//! Instantiates the objects it is passed for the required level.
/*! Uses the levelNumber variable to create the correct level from the appropriate
level textfile.
\param levelNumber corresponds to the level-containing text file that needs to be loaded.
*/
	void instantiateLevel(digdug& dd,monsters& monstVec,tunnels& tunVec,vector<rock_ptr>& Rocks,const int levelNumber); 
private:
	int _levelNum;
	int _maxLevel;
};

#endif