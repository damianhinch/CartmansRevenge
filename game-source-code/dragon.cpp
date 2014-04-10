#include "dragon.h"

bool dragon::attack(xy ddPos)//is the player in the dragons flames or has there been a normal collission
{
	if ((!_disembodied)){//can't attack if disembodied
		if (ddPos==_pos)
			return true;
			switch (_curDir)
			{
			case LEFT:
				if ( (abs(ddPos.y-_pos.y)<=40)&&(_pos.x-ddPos.x<80)&&(_pos.x-ddPos.x>0) )
					_isAttacking=1;
				else _isAttacking=0;
				
				if(_isAttacking)
					if( (ddPos.y==_pos.y)&&(_pos.x-ddPos.x<=40) )
						return true;
				break;
			case RIGHT:
				if ( (abs(ddPos.y-_pos.y)<=40)&&(ddPos.x-_pos.x<80)&&(ddPos.x-_pos.x>0) )
					_isAttacking=1;
					else _isAttacking=0;
				if(_isAttacking)
					if( (ddPos.y==_pos.y)&&(ddPos.x-_pos.x<=40) )
						return true;
				break;
			default:
				_isAttacking=0;
				return 0;
			}
			return false;
	}
	return false;
}
