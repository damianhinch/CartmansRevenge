#include "digdug.h"

digdug::digdug(): _lives(3),_curDir(STOP),_score(0){}

void digdug::move(bool dir[],int step)
{
	if(!dir[NOTHING])
		if (dir[UP])
		{
			_pos.y-=step;
			_curDir=UP;
		}
		else if (dir[DOWN])
		{
			_pos.y+=step;
			_curDir=DOWN;
		}
		else if (dir[LEFT])
		{
			_pos.x-=step;
			_curDir=LEFT;
		}
		else if (dir[RIGHT])
		{
			_pos.x+=step;
			_curDir=RIGHT;
		}
		else 
			_curDir=STOP;
}

bool digdug::dead()
{
	_lives--;
	_curDir=STOP;
	if(_lives<0)_lives=0;
	if (_lives<=0)
		return true;
	else return false;
}

xy digdug::pos()
{
	return _pos;
}

void digdug::setx(int x)
{
	_pos.x=x;
}

void digdug::sety(int y)
{
	_pos.y=y;
}

void digdug::setpos(xy pos)
{
	_pos=pos;
}

int digdug::getDir() const
{
	return _curDir;
}

int digdug::getScore() const 
{
	return _score;
}

void digdug::increaseScore(int increment)
{
	_score+=increment;
}

int digdug::getLives() const
{
	return _lives;
}

void digdug::restoreLives()
{
	_lives=3;
}