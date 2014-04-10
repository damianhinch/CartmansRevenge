#ifndef _OBJECTS_H
#define _OBJECTS_H


/**The enumeration constants are used to improve
readibility and help the programmer by allowing him
to use english words instead of numbers.
*/

enum KEYS{UP, DOWN, LEFT, RIGHT,NOTHING,STOP};
enum FOODS{CITYWOK,DOUBLEDEW,DRUMSTICK,POTPIE};

//! Misc. objects used by all classes.
/*! All of the characters have a private
member of type xy that houses their positions. 
Most of the classes include this file in order
to take advantage of the position storing functionality 
on offer.
\author Damian Hinch, Joseph Penn
\version v0.3.8
\date 25/09/2012
*/


class xy{
public:
    int x;
    int y;

//! Allows for quick comparison of positions.
/*! Speeds up comparisons by allowing the user to 
use the standard == operator in order to compare two objects.
\param rhs is the object we wish to compare the other object to
\return 1 if both x and y are the same, 0 otherwise
*/
    bool operator==(const xy& rhs) const 
		{return  ( (x== rhs.x)&&(y == rhs.y) );}
	void setxy(int xpos,int ypos){x=xpos;y=ypos;}

//! Allows for on-the-fly creation of an xy class.
/*! This replaces the repetitive creation of multiple objects that 
are only needed once in order to create another object.
Static used so that you DON'T need to create an object of xy first, as this would 
negate the advantages of using this method.
\param xpos the desired x position
\param ypos the desired y position
\return a new object of type xy
*/
	static xy makestruct(int xpos,int ypos)
		{
			xy mystruct;
			mystruct.setxy(xpos,ypos);
			return mystruct;
		}
};


#endif