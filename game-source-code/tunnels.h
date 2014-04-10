#ifndef _TUNNELS_H 
#define _TUNNELS_H

#include <vector>
#include "objects.h"

using namespace std;

//! Tunnels holds a vector of coordinates indicating where tunnels have been dug.
/*! If a coordinate is in the tunnels vector it means that a monster (or
harpoon tip) can pass through that position. Coordinates are added to the vector every 
game loop as digdug moves through the gamescreen.
\author Damian Hinch, Joseph Penn
\version v0.3.8
\date 25/19/2012
*/

class tunnels{
public:

//! Tunnels constructor.
/*! A variety of constructors are provided depending 
on what type of initial tunnel vector you wish to create.
You can pass nothing, you can pass a single tunnel
or you can pass a vector containing a network of tunnels.
*/
	tunnels();
	tunnels(xy); 
	tunnels(vector<xy>);

//! Adds a new tunnel to the vector.
/*! Each time digdug moves, a tunnel position is added to the vector -
provided that it is not already present in the vector. This means that
this vector will be very small initially, but will grow
as the game progresses. Duplicates are not added. 
This method ensures that a large 2D array containing information about every 
point on the screen DOESN'T need to be traversed after each iteration, saving
both CPU cycles and memory.
\param newTun takes a single coordinate that is added to the back of the vector
*/
	void addTunnel(xy newTun);

//! Checks if the given position is within the tunnel vector.
/*! This function can be used by any class that needs to 
check whether a certain position is stored in the tunnels vector. 
The monsters use this every move in order to make sure that they don't 
move out of tunnel. The rocks use it in order to ascertain when they have reached
the ground during the course of their descent.
\param posToCheck the position we want to search for in the tunnel vector
\return 1 if the coordinate is in the tunnel vector, 0 if it is not
*/
	bool inTunnel(xy posToCheck) const;  
	int getSize() const;
	xy getIthTun(int) const;
	void clearTunnels();
private:
	vector<xy> _tunnelNetwork;  /**< Vector that stores all of the positions that make up the tunnel network */

};

#endif