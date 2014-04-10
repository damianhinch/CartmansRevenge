#include "monster.h"
#include <cmath>
#include <iostream>


monster::monster(xy startPos): _pos(startPos),_animCount(0),_alive(1),_timeStuck(0),_disembodied(0),_countDisembody(0),_curDir(3),
							   _harpoonedCounter(0),_startPos(startPos),_isAttacking(0) {
	for (int i=0;i<5;i++)_dir[i]=0;
	xy temp;temp.setxy(0,0);_lastPos=temp;
}

void monster::moveDecision(tunnels& tunnelNW, xy &playerPos,int squareWidth) //moves the monster based on a shortest path algorithm. Monster must always move one way or the other
{
	if (!_disembodied){
		int emptyTotal=0;
		bool empty[5]={0};
		for (int i=0;i<5;i++)_dir[i]=0; //reset all directions
		for (int i = 0; i < tunnelNW.getSize(); i++){
			if( (tunnelNW.getIthTun(i).x==_pos.x+squareWidth)&&(tunnelNW.getIthTun(i).y==_pos.y)){empty[RIGHT]=1;}
			if( (tunnelNW.getIthTun(i).x==_pos.x-squareWidth)&&(tunnelNW.getIthTun(i).y==_pos.y)){empty[LEFT]=1;}
			if( (tunnelNW.getIthTun(i).y==_pos.y-squareWidth)&&(tunnelNW.getIthTun(i).x==_pos.x)){empty[UP]=1;}
			if( (tunnelNW.getIthTun(i).y==_pos.y+squareWidth)&&(tunnelNW.getIthTun(i).x==_pos.x)){empty[DOWN]=1;}
		}
		emptyTotal = empty[RIGHT]+empty[LEFT]+empty[UP]+empty[DOWN];

		if ((emptyTotal > 2) && (playerPos.x < _pos.x) && (empty[LEFT]) && (_pos.x - squareWidth != _lastPos.x)){_dir[LEFT] = true;}
			else if ((emptyTotal > 2) && (playerPos.x < _pos.x) && (!empty[LEFT]) && (_pos.x - squareWidth != _lastPos.x)){_dir[DOWN] = true;}

			else if ((emptyTotal > 2) && (playerPos.x > _pos.x) && (empty[RIGHT]) && (_pos.x + squareWidth != _lastPos.x)){_dir[RIGHT] = true;}
			else if ((emptyTotal > 2) && (playerPos.x > _pos.x) && (!empty[RIGHT]) && (_pos.x + squareWidth != _lastPos.x)){_dir[UP] = true;}
			else if ((emptyTotal > 2) && (playerPos.y < _pos.y) && (empty[UP]) && (_pos.y - squareWidth != _lastPos.y)){_dir[UP] = true;}
			else if ((emptyTotal > 2) && (playerPos.y < _pos.y) && (!empty[UP]) && (_pos.y - squareWidth != _lastPos.y)){_dir[LEFT] = true;}

			else if ((emptyTotal > 2) && (playerPos.y > _pos.y) && (empty[DOWN]) && (_pos.y + squareWidth != _lastPos.y)){_dir[DOWN] = true;}
			else if ((emptyTotal > 2) && (playerPos.y > _pos.y) && (!empty[DOWN]) && (_pos.y + squareWidth != _lastPos.y)){_dir[RIGHT] = true;}

			else if((emptyTotal <= 2) && (empty[LEFT]) && (_pos.x - squareWidth != _lastPos.x)){_dir[LEFT] = true;}
			else if((emptyTotal <= 2) && (empty[RIGHT]) && (_pos.x + squareWidth != _lastPos.x)){_dir[RIGHT] = true;}
			else if((emptyTotal <= 2) && (empty[UP]) && (_pos.y - squareWidth != _lastPos.y)){_dir[UP] = true;}
			else if((emptyTotal <= 2) && (empty[DOWN]) && (_pos.y + squareWidth != _lastPos.y)){_dir[DOWN] = true;}
		
		else {
				_lastPos=_pos;
				_timeStuck=(_timeStuck+1)%6;
		}
		_lastPos=_pos;
	}
	else{//else if disembodied
		_timeStuck=0;
		for (int i=0;i<5;i++)_dir[i]=0;
		int xdiff=_pos.x-_disembodiedPoint.x;
		int ydiff=_pos.y-_disembodiedPoint.y;

		if (xdiff>0)_dir[LEFT]=1;
		else if (xdiff<0)_dir[RIGHT]=1;//note equal to 0 is left out

		if (ydiff>0)_dir[UP]=1;
		else if (ydiff<0)_dir[DOWN]=1;

	}
}

void monster::move(int stepSize)
{
	if ((!_dir[NOTHING])&&(_harpoonedCounter==0)){ //not else if becuase monsters can move diagonally
		if (_dir[UP]){
			_pos.y-=_dir[UP]*stepSize;
			_curDir=UP;
			_animCount=0;
		}
		if (_dir[DOWN]){
			_pos.y+=_dir[DOWN]*stepSize;
			_curDir=DOWN;
			_animCount++;
			_animCount=_animCount%25;
		}
		if (_dir[LEFT]){
			_pos.x-=_dir[LEFT]*stepSize;
			_curDir=LEFT;
			_animCount=0;
		}
		if (_dir[RIGHT]){
			_pos.x+=_dir[RIGHT]*stepSize;
			_curDir=RIGHT;
			_animCount=0;
		}		
	}
	else _curDir=NOTHING;
}

int monster::gettimeStuck() const
{
	return _timeStuck;
}

bool monster::is_alive() const
{
	return _alive;
}

xy monster::pos() const
{
	return _pos;
}

void monster::setx(int x)
{
	_pos.x=x;
}

void monster::sety(int y)
{
	_pos.y=y;
}

void monster::setpos(xy posToSet)
{
	_pos=posToSet;
}

bool monster::isdisembodied() const
{
	return _disembodied;
}

void monster::disembody(xy whereToGo)
{
	_countDisembody++;
	_disembodied=1;
	_disembodiedPoint=whereToGo;
	_disembodiedStartPt=_pos;
	_dir[NOTHING]=0;
	_harpoonedCounter=0;
}

void monster::reembody()
{
	_disembodied=0;
}

int monster::getCountDisembody()
{
	return _countDisembody;
}

int monster::getDir() const
{
	return _curDir;
}

int monster::isHarpooned() const
{
	return _harpoonedCounter;
}

void monster::harpooned()
{
	_harpoonedCounter=1;
}

void monster::unharpooned()
{
	_harpoonedCounter=0;
}

void monster::increaseCounter()
{
	_harpoonedCounter=_harpoonedCounter+2;
}

void monster::decreaseCounter()
{
	_harpoonedCounter--;
}

void monster::resetMons()
{
	_pos=_startPos;
	_disembodied=0;
	_lastPos=_pos;
	_countDisembody=0;
	_harpoonedCounter=0;
	_disembodiedPoint=_pos; //where he aims to go when disembodied
	_timeStuck=0;
	_curDir=0;
	_isAttacking=0;
	for(int i=0;i<5;i++)_dir[i]=0;
}

bool monster::isAttacking()
{
	return _isAttacking;
}

void monster::setDir(int dir)
{
	_curDir=dir;
	_dir[dir]=1;
}

void monster::giveUpTunnelSearch()
{
	_disembodiedPoint=_disembodiedStartPt;
}

int monster::getAnimCount() const
{
	return _animCount;
}