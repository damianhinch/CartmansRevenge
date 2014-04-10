#include "clydefrog.h"

bool clydefrog::attack(xy ddpos)
{
	if(!_disembodied)
		return (ddpos==_pos);
	return false;
}