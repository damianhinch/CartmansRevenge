#include "rock.h"

rock::rock(xy pos,bool leftRight):_pos(pos),_active(1),_leftRight(leftRight),_bottom(0),_falling(0),_open(0),_hasFallen(0){}

bool rock::isActive() const
{
	return _active;
}

void rock::activate()
{
	_active=1;
}

void rock::move(int step)
{
	if(_falling)
	{
		_hasFallen=1;
		_pos.y+=step;
	}
}

void rock::deactivate()
{
	_active=0;
}

bool rock::isBottom() const
{
	return _bottom;
}

xy rock::pos() const
{
	return _pos;
}

bool rock::getLeftRight() const
{
	return _leftRight;
}

void rock::startFalling()
{
	_falling=1;
}

void rock::stopFalling()
{
	_bottom=1;
	_falling=0;
}

bool rock::isFalling() const
{
	return _falling;
}

void rock::open()
{
	_open=1;
}

bool rock::isOpen() const
{
	return _open;
}

bool rock::hasFallen() const
{
	return _hasFallen;
}

int rock::isNearRock(xy pos) const
{
	if (_active){
		if ( (pos.y+40==_pos.y)&&(pos.x==_pos.x))
			return DOWN;
		else if ( (pos.y-40==_pos.y)&&(pos.x==_pos.x) )
			return UP;
		else if ( (pos.y-40==_pos.y)&&(abs(pos.x-_pos.x)<=2) )
			return UP;
		else if ( (pos.x==_pos.x+40)&&(pos.y==_pos.y) )
			return LEFT;
		else if ( (pos.x==_pos.x-40)&&(pos.y==_pos.y) )
			return RIGHT;
		return NOTHING;
	}
	else return NOTHING;

}

void rock::setPos(xy pos)
{
	_pos=pos;
}