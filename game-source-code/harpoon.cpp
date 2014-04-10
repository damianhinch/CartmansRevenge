#include "harpoon.h"

harpoon::harpoon():_active(0),_length(0),_isHarpooning(0){
_tipPos.setxy(0,0);
}

void harpoon::move(int dir,int step)
{
	if( (_active)&&(!_isHarpooning) ){		
		switch(dir)
		{
		case UP:
			_tipPos.y-=step;
			break;
		case DOWN:
			_tipPos.y+=step;
			break;
		case LEFT:
			_tipPos.x-=step;
			break;
		case RIGHT:
			_tipPos.x+=step;
			break;
		case STOP:
			_tipPos.y+=step;
			break;
		}
		_length++;
	}
}

bool harpoon::isActive() const
{
	return _active;
}

xy harpoon::pos() const
{
	return _tipPos;
}

void harpoon::activate(xy pos)
{
	_active=1;
	_tipPos=pos;
}

void harpoon::deactivate()
{
	_active=0;
	_length=0;
	_isHarpooning=0;
}

int harpoon::getLength() const
{
	return _length;
}

void harpoon::harpooning()
{
	_isHarpooning=1;
}
void harpoon::unharpooning()
{
	_isHarpooning=0;
}
bool harpoon::isHarpooning() const
{
	return _isHarpooning;
}
