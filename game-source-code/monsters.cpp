#include "monsters.h"

void monsters::addMonster(monster* monst)
{
	_monstVec.push_back(monst);
}

void monsters::killMonster(int index)
{
	if (index<_monstVec.size())
		_monstVec.erase(_monstVec.begin()+index);
}

void monsters::moveDecisionMonsters(tunnels& tunnelNW,xy& playerPos,int squareWidth)
{
	vector<bool> result;
	for(int i=0;i<_monstVec.size();i++)
		_monstVec[i]->moveDecision(tunnelNW,playerPos,squareWidth);

	for(int i=0;i<_monstVec.size();i++)
		for (int j=i+1;j<_monstVec.size();j++)
			if ( (_monstVec[i]->pos()==_monstVec[j]->pos())&&(!_monstVec[i]->isdisembodied())&&(!_monstVec[j]->isdisembodied()) )
				_monstVec[i]->setDir(NOTHING);//deals with collisions

}

void monsters::moveMonsters(int stepSize)
{
	for(int i=0;i<_monstVec.size();i++)
	{
		if (_monstVec[i]->is_alive())
			_monstVec[i]->move(stepSize);
	}
}

int monsters::getSize() const
{
	return _monstVec.size();
}

xy monsters::getithPos(int i) const
{
	if (i<_monstVec.size())
		return _monstVec[i]->pos();
	else return  _monstVec[0]->pos();
}

bool monsters::attack(xy playerPos) const
{
	bool bfound=0;
	int count=0;
	while ( (!bfound)&&(count<_monstVec.size()) )
	{
		if (_monstVec[count]->attack(playerPos)) //attacks the player. If the player is close enough he will die.
			bfound=true;
		else count++;
	}
	return bfound;
}

bool monsters::isAlive(int index) const
{
	return _monstVec[index]->is_alive();
}


void monsters::setithpos(int index,xy pos)
{
	if (index<_monstVec.size())
		_monstVec[index]->setpos(pos);
}

vector<bool> monsters::whosStuck()
{
	vector<bool> temp;
	for (int i=0;i<_monstVec.size();i++)
	{
		temp.push_back(_monstVec[i]->gettimeStuck()==5); //fix this magic number
	}
	return temp;
}


bool monsters::isDisembodied(int index) const
{
	if (index<_monstVec.size())
		return _monstVec[index]->isdisembodied();
	else return 0;
}

void monsters::setDisembodied(int index,xy playerPos)
{
	if (index<_monstVec.size())
		_monstVec[index]->disembody(playerPos);
}

void monsters::reembody(int index)
{
	if (index<_monstVec.size())
		_monstVec[index]->reembody();
}

int monsters::getCountDisembodyIth(int index)
{
	if (index<_monstVec.size())
		return _monstVec[index]->getCountDisembody();
}

int monsters::isShot(xy harpoonPos)
{
	int counter=0;
	bool found=0;
	while ( (counter<_monstVec.size())&&(!found) )
	{
		int mx=_monstVec[counter]->pos().x;
		int my=_monstVec[counter]->pos().y;
		if ((_monstVec[counter]->is_alive())&&(!_monstVec[counter]->isdisembodied())) 
			if  ( (_monstVec[counter]->pos()==harpoonPos)||
				( (abs(mx-harpoonPos.x)<40)&&(my==harpoonPos.y) )||
				( (abs(my-harpoonPos.y)<40)&&(mx==harpoonPos.x) ) )
					found=true;
			else  counter++;
		else counter++;
		
	}
	if (found){
		return counter+1;
	}
	else return 0;
}

int monsters::getithDir(int index) const
{
	if (index<_monstVec.size())
		return _monstVec[index]->getDir();
	else return 0;
}

monster* monsters::getithMonster(int index) const
{
	if (index<_monstVec.size())
		return _monstVec[index];
}

void monsters::harpoonithMonster(int index)
{
	if (index<_monstVec.size())
		_monstVec[index]->harpooned();
}

void monsters::unharpoonithMonster(int index)
{
	if (index<_monstVec.size())
		_monstVec[index]->unharpooned();
}

void monsters::increaseHarpoonCount(int index)
{
	if (index<_monstVec.size())
		_monstVec[index]->increaseCounter();
}

int  monsters::getHarpoonCount(int index) const
{
	if (index<_monstVec.size())
		return _monstVec[index]->isHarpooned();
	else return 0;
}

void monsters::decreaseHarpoonCount(int index)
{
	if (index<_monstVec.size())
		_monstVec[index]->decreaseCounter();
}

void monsters::resetAllMonsts()
{
	for (int i=0;i<_monstVec.size();i++)
		_monstVec[i]->resetMons();
}

bool monsters::getithIsAttacking(int index) const
{
	if (index<_monstVec.size())
		return _monstVec[index]->isAttacking();
	else return 0;
}

void monsters::giveUpTunnelSearch(int index)
{
	if (index<_monstVec.size())
		if (_monstVec[index]->isdisembodied())
			_monstVec[index]->giveUpTunnelSearch();
}

void monsters::killAllMonsts()
{
	_monstVec.clear();
}