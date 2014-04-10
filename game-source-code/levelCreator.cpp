#include "levelCreator.h"


void levelCreator::instantiateLevel(digdug& dd,monsters& monstVec,tunnels& tunVec,vector<rock_ptr>& Rocks,const int levelNumber)
{
	monstVec.killAllMonsts();
	Rocks.clear();
	tunVec.clearTunnels();
	stringstream ss;//create a stringstream
    ss << levelNumber;//add number to the stream
	string filename="Level"+ss.str()+".txt";
	ifstream levelfile(filename); 
	string line;
	if (levelfile.is_open())
	{
		//dd pos
		getline(levelfile,line); 
		xy ddpos=xy::makestruct(atoi(line.substr(0,3).c_str()),atoi(line.substr(4,7).c_str()));
		dd.setpos(ddpos);
		//tunnels
		getline(levelfile,line);
		while(line.size()>0)
		{
			xy tunStart=xy::makestruct(atoi(line.substr(0,3).c_str()),atoi(line.substr(4,7).c_str()));
			int i=atoi(line.substr(8,11).c_str());
			int HorVert=atoi(line.substr(12,13).c_str());
			line.erase (0,14);
			if(HorVert==0)
				for (int j=0;j<i;j++)tunVec.addTunnel(xy::makestruct(tunStart.x+j*4,tunStart.y));
			else
				for (int j=0;j<i;j++)tunVec.addTunnel(xy::makestruct(tunStart.x,tunStart.y+j*4));
		}

		//monsters
		getline(levelfile,line);
		while(line.size()>0)
		{
			xy monstStart=xy::makestruct(atoi(line.substr(0,3).c_str()),atoi(line.substr(4,7).c_str()));
			string MorD=line.substr(8,1);
			line.erase(0,10);
			if(MorD=="D")
				monstVec.addMonster(new dragon(monstStart));
			else
				monstVec.addMonster(new clydefrog(monstStart));
		}
		//rocks
		getline(levelfile,line);
		while(line.size()>0)
		{
			xy rockStart=xy::makestruct(atoi(line.substr(0,3).c_str()),atoi(line.substr(4,7).c_str()));
			string LorR=line.substr(8,1);
			line.erase(0,10);
			if(LorR=="R"){
				rock_ptr rock3_ptr(new rock(rockStart,1));
				Rocks.push_back(rock3_ptr);
			}
			else{
				rock_ptr rock3_ptr(new rock(rockStart,0));
				Rocks.push_back(rock3_ptr);
			}
		}

		
		levelfile.close();
   }
	


}