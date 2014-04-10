#include "tunnels.h"

tunnels::tunnels(){} //look at lab 3 and do the same default constructor thing he did

tunnels::tunnels(vector<xy> startingNetwork):_tunnelNetwork(startingNetwork){}

tunnels::tunnels(xy startpos)
{
	_tunnelNetwork[0]=startpos;
}

void tunnels::addTunnel(xy tun) //if you try add a tunnel it will only add one if that tunnel wasn't already there
{
	bool bAddVec=0;
    int j=0;
    while ( (!bAddVec)&&(j<_tunnelNetwork.size()) )
    {
		if (tun==_tunnelNetwork[j])
			bAddVec=1;
            j++;
    }
    if (!bAddVec)
	_tunnelNetwork.push_back(tun);
}

bool tunnels::inTunnel(xy tun) const
{
	int size=_tunnelNetwork.size();
    int i=0;
    bool bfound=false;
    while( (!bfound)&&(i<size) )
    {
        if  (tun==_tunnelNetwork[i])
            bfound=true;
        i++;
    }
    return bfound;
}

int tunnels::getSize() const
{
	return _tunnelNetwork.size();
}

xy tunnels::getIthTun(int ith) const
{
	if (ith<_tunnelNetwork.size())
		return _tunnelNetwork[ith];
	//else throw error. bad to have a way nothing is returned so for now just return 0,0
	else{
		xy tempstruct;
		tempstruct.setxy(0,0);
		return tempstruct;
	}
}

void tunnels::clearTunnels()
{
	_tunnelNetwork.clear();
}
