#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <typeinfo>
#include <fstream>
#include <sstream>
#include <string>

#include <algorithm>

#include "objects.h"
#include "digdug.h"
#include "monsters.h"
#include "tunnels.h"
#include "canvas.h"
#include "harpoon.h"
#include "dragon.h"
#include "clydefrog.h"
#include "fooditem.h"
#include "rock.h"


#include <boost/smart_ptr.hpp>
using boost::scoped_ptr;
using boost::shared_ptr;


//GLOBAL VARIABLES//
const int width = 985;  
const int height = 760;
const int scr_width = 680;
const int scr_height = 720;
const int square_width=40;
const int scorePanelWidth = 265;
const int FPS = 35;
const int step=4;
////////////////////

vector<int> getHighScores();
bool highScoreManager(int playerScoreForRound);

//! The actual game-play loop
/*! This is where the actual game takes place. 
If succesfull in game-play, the player will exit this loop
and progress to the next level.  However, if digdug's 3 lives
have been used up the game will be over 
and the player will be returned to the beginning 
of the control loop (main.cpp).
\author Damian Hinch, Joseph Penn
\version v0.3.8
\date 25/09/2012
*/

char start(digdug& dd,monsters& monstVec,tunnels& tunnelArr,vector<rock_ptr>& Rocks,harpoon& Harpoon,canvas& Canvas,fooditem& Food,ALLEGRO_DISPLAY *display,const int foodMax=4)
{
	/**<ALLEGRO */
	ALLEGRO_EVENT_QUEUE *event_queue=NULL;
	ALLEGRO_TIMER *timer=NULL;
	ALLEGRO_KEYBOARD_STATE key_state;
	/**<ALLEGRO audio*/
	ALLEGRO_SAMPLE *harpoonZip = NULL;
	ALLEGRO_SAMPLE *harpoonImpact = NULL;
	ALLEGRO_SAMPLE *dieOnce = NULL;	
	ALLEGRO_SAMPLE *dieThree = NULL;	
	ALLEGRO_SAMPLE *win = NULL;	
	ALLEGRO_SAMPLE *killMonst = NULL;	
	ALLEGRO_SAMPLE *coffinDrop = NULL;
	ALLEGRO_SAMPLE *cityWok = NULL;	
	ALLEGRO_SAMPLE *kfcChicken = NULL;	
	ALLEGRO_SAMPLE *potPie = NULL;	
	ALLEGRO_SAMPLE *doubleDew = NULL;	
	ALLEGRO_SAMPLE *splat = NULL;
	ALLEGRO_SAMPLE *foodRegister = NULL;
	ALLEGRO_SAMPLE *rockGrunt = NULL;
	ALLEGRO_SAMPLE *hooray = NULL;
		
	/**<Event queue and timer creation*/
	event_queue=al_create_event_queue();
	timer=al_create_timer(1.0/FPS);

	/**<FONTS*/
	ALLEGRO_FONT *font28 = al_load_font("south park.ttf",28,0);
	ALLEGRO_FONT *font24 = al_load_font("south park.ttf",24,0);

	/**<Register event queues/sources */
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue,al_get_display_event_source(display));
	
	/**<Audio sample loading */
	harpoonZip = al_load_sample("HarpoonZip.wav");
	harpoonImpact= al_load_sample("HarpoonImpact.wav");
	dieOnce = al_load_sample("CaughtByMonster.wav");
	dieThree = al_load_sample("DeathOfCartman.wav");		
	killMonst = al_load_sample("Pop.wav");	
	coffinDrop = al_load_sample("CoffinOpen.wav");
	cityWok = al_load_sample("CityWok.wav");
	kfcChicken = al_load_sample("Chicken.wav");	
	potPie = al_load_sample("Potpie.wav");	
	doubleDew = al_load_sample("DoubleDew.wav");	
	splat = al_load_sample("Splat.wav");	
	foodRegister= al_load_sample("FoodRegister.wav");	
	rockGrunt= al_load_sample("RockGrunt.wav");	
	hooray = al_load_sample("Hooray.wav");

	/**<variables*/
	bool playerIn[6]={0};	//saves which direction the user wants to move in
	xy ddpos,ddposGrid;
	bool done=false;	
	bool redraw=true;
	bool shoot=0;			//whether or not to shoot
	int moveCounter=0;		//things must only happen after a certain number of timer counts to keep monsters in grid
	int disembcount=0;		//times how long monsters are disembodied for
	int rockCount=0;		//used to time when coffin should start falling (it shakes first)
	int openCount=0;		//used to time when coffin should play "open" animation	
	int foodCount=0;		//used to time when new food should appear	
	int direction =5;		//5 = STOP in enum constants
	int iMonstToKill=0;
	int levelCount=1;		//initial level to load, can be changed for testing etc
	int foodFull=0;			//so that new foods don't keep loading indefinitely leading to a potentially infinite player score

	vector<int> highScores=getHighScores();

	vector<bool> monstStuck;
	Food.deactivate();
	xy ddStartPos(dd.pos());
	ddpos=dd.pos();
	al_start_timer(timer);	
	while(!done){  /**<This cyles until either the player eliminates all the monsters, or loses all of his lives*/
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue,&ev);
		direction=STOP;
		if(ev.type == ALLEGRO_EVENT_TIMER) /**<Wait for the timer to trigger, and then process the user's input*/
		{	
			//get direction from user keypress
			al_get_keyboard_state(&key_state);	
			if (al_key_down(&key_state, ALLEGRO_KEY_UP))
				{direction = UP;} 
			else if (al_key_down(&key_state, ALLEGRO_KEY_RIGHT))
				{direction = RIGHT;}
			else if(al_key_down(&key_state, ALLEGRO_KEY_DOWN))
				{direction = DOWN;}
			else if (al_key_down(&key_state, ALLEGRO_KEY_LEFT))
				{direction = LEFT;}
			else  direction=STOP;
			//see if user has pressed the space bar
			if (al_key_down(&key_state,ALLEGRO_KEY_SPACE))
				shoot=true;	 //if he presses shoot, activate the harpoon
			else
				shoot=false; //deactivate harpoon if user isn't pressing space

			moveCounter++;
			disembcount++;
			if(!Rocks.size()==0)//fail safe so that rockCount doesn't keep increasing indefinitely, potentially leading to an overflow
				rockCount++;
			foodCount++;

			for (int i=0;i<Rocks.size();i++){
				if ( (Rocks[i]->isBottom())&&(Rocks[i]->isActive()) )
					openCount++;  //play open animations
			}

			if(Harpoon.isActive()){
				direction=NOTHING;
			}

			if(iMonstToKill!=0){
				if(monstVec.getithMonster(iMonstToKill-1)->isHarpooned()>90)
				{
					monstVec.increaseHarpoonCount(iMonstToKill-1); //increase swelling animation
				}

				else if ( Harpoon.isHarpooning()){
					monstVec.increaseHarpoonCount(iMonstToKill-1);
				}
			
				else if ( (!Harpoon.isHarpooning())&&(monstVec.getithMonster(iMonstToKill-1)->isHarpooned()!=0) )
					if(monstVec.getithMonster(iMonstToKill-1)->isHarpooned()<90)
				{
					monstVec.decreaseHarpoonCount(iMonstToKill-1);	//de-swells the monsters if you let go, they still can't move at this point
				}
				

			}
	}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) return 'q';
		
		//drawing
		if (al_is_event_queue_empty(event_queue))//we only want to draw if the queue is empty. This will most likely sill happen every 1/30 seconds anyway.
		{
			monstVec.attack(dd.pos()); //This is to make the monsters blow fire if they are near to dd. The result returned is not used. Work-around that isn't perfect. Without it the dragons' fire wouldn't display though.
			Canvas.displayGamePanel(display,dd.getScore(),dd.getLives(),highScores);
			Canvas.displayFoodRemaining(display,foodFull,font24);
			Canvas.drawScreen(display);
			Canvas.drawTunnels(display,tunnelArr);
			Canvas.drawDigDug(display,dd.pos(),dd.getDir());
			Canvas.drawMonsters(display,monstVec);
			Canvas.drawHarpoon(display,Harpoon,dd.getDir(),step);
			Canvas.drawRocks(display,Rocks);
			Canvas.drawFood(display,Food);
			al_flip_display();
		}
		if (moveCounter == 10){
			ddposGrid=dd.pos();
			for (int i=0;i<6;i++)playerIn[i]=0;

			bool bfound=0;
			
			for (int i=0;i<Rocks.size();i++){
				if((Rocks[i]->isNearRock(dd.pos())==direction)){  //checks if digdug is next to a rock and doesn't let him move there if he is.
					bfound=1;
				}
			}
			if(!bfound)playerIn[direction]=1;	
			monstVec.moveDecisionMonsters(tunnelArr,dd.pos(),square_width);
			moveCounter=0;
			//harpoons monster
			if ( (shoot)&&(!Harpoon.isActive())&&(dd.pos().x%40==0)&&(dd.pos().y%40==0) ) //we only want to shoot when we are on a grid square properly.
			{
				al_play_sample(harpoonZip, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
				Harpoon.activate(dd.pos());
				playerIn[NOTHING]=1; //set NOTHING=1 so he won't move and his direction won't change next iteration of move
			}
			else if (Harpoon.isActive())
				playerIn[NOTHING]=1;
	
			//releases monster if de-swelled and not harpooned
			if (iMonstToKill != 0){
				if (monstVec.getithMonster(iMonstToKill - 1)->isHarpooned() == 0){
					monstVec.unharpoonithMonster(iMonstToKill-1);
					xy moPos = monstVec.getithPos(iMonstToKill-1);
					monstVec.setithpos(iMonstToKill-1,xy::makestruct( (moPos.x/40)*40, (moPos.y/40)*40));
					iMonstToKill = 0;	
				}
			}
		}
		
		//monster attacking
		if (monstVec.attack(dd.pos())){ //i.e. if a monster has successfully attacjed
			if(dd.dead()){ //if he is out of lives now
				al_play_sample(dieThree, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
				done=1;
				Canvas.displayGamePanel(display,dd.getScore(),dd.getLives(),highScores);
				Canvas.displayFoodRemaining(display,foodCount,font24);
				al_flip_display();
				return 'D';
			}
			else{ //i.e he has been attacked but still has lives remaining
				al_play_sample(dieOnce, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
				monstVec.resetAllMonsts();
				dd.setpos(ddStartPos);
				for(int i=0;i<monstStuck.size();i++) monstStuck[i]=0;
				moveCounter=0;
				foodCount=0;
				disembcount=0;
				Harpoon.deactivate();
				Canvas.displayDigDugCaught(display, dd.getLives());
				al_flip_display();
				al_rest(3);
				al_set_timer_count(timer,0);
				al_start_timer(timer);
				al_flush_event_queue(event_queue);
			}
		}

		if(shoot == false) 
			Harpoon.deactivate();

		//check for colission with tunnels
		if(Harpoon.isActive())
			if ( (!tunnelArr.inTunnel(Harpoon.pos()))||((Harpoon.getLength()>20)))
			{
				al_play_sample(harpoonImpact, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
				Harpoon.deactivate();
				shoot=0;
			}

		if(iMonstToKill!=0)
			if(monstVec.getHarpoonCount(iMonstToKill-1) == 105) //at this point we check if the monster has swollen up to the point where it must now die
			{
				al_play_sample(killMonst, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
				monstVec.killMonster(iMonstToKill-1);
				Harpoon.deactivate();
				dd.increaseScore(250); //reward digdug for killing a monster with a harpoon
			}

		//harpoon collision detection
		if (!Harpoon.isHarpooning()){
			iMonstToKill=monstVec.isShot(Harpoon.pos()); //are any of the monsters shot by the harpoon?
			if ((!iMonstToKill==0)&&(Harpoon.isActive()))
			{
				monstVec.harpoonithMonster(iMonstToKill-1);
				al_play_sample(harpoonImpact, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
				Harpoon.harpooning();//set that we are currently harpooning a monster
			}
		}

		//rocks
		for (int i=0;i<Rocks.size();i++){			
			if ((Rocks[i]->pos().y%40==0)&&(!Rocks[i]->isFalling())) //this is a check to see if a rock must start falling i.e. if dd is under the rock
			{
				if ( (tunnelArr.inTunnel(xy::makestruct(Rocks[i]->pos().x,Rocks[i]->pos().y+square_width))) )
				{
					Rocks[i]->startFalling();
					rockCount=0;
					al_play_sample(coffinDrop, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
				}
			}
			if (Rocks[i]->pos().y%40==0)
				if (!tunnelArr.inTunnel(xy::makestruct(Rocks[i]->pos().x,Rocks[i]->pos().y+square_width)))
					if(Rocks[i]->hasFallen())
					{
						Rocks[i]->stopFalling();  //stop falling if it has hit the ground
					}
		
			if (Rocks[i]->isFalling())
				if (rockCount==40)
					Rocks[i]->setPos(xy::makestruct( (Rocks[i]->pos().x/10)*10, (Rocks[i]->pos().y/10)*10));
				else if(rockCount>40) //ie it's falling now
				{
					for(int j=0;j<2;j++){  //we do this twice becuase we want the rock to move double as fast
						Rocks[i]->move(step);
						for(int k=0;k<monstVec.getSize();k++)//step through monster vector
						{
							if( (k<=monstVec.getSize())&&(i<=monstVec.getSize()) ){ //just a fail safe
 								if( (monstVec.getithPos(k).x==Rocks[i]->pos().x)&&(abs(monstVec.getithPos(k).y-Rocks[i]->pos().y)<20) ){
									if(!monstVec.isDisembodied(k)){ //don't kill a monster by a rock if it is disembodied
										monstVec.killMonster(k);
										k--;//try to ensure all monsters are killed
										dd.increaseScore(500);
										al_play_sample(splat, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
									}
								}
	
								if (dd.pos()==Rocks[i]->pos()) //kill digdug by the rock
									if(dd.dead()){
										al_play_sample(dieThree, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
										done=1;
										al_flip_display();
										return 'D';
										break;
									}
									else{
										al_play_sample(dieOnce, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
										monstVec.resetAllMonsts(); //put all alive monter back to their starting positions
										dd.setpos(ddStartPos);
										for(int i=0;i<monstStuck.size();i++) monstStuck[i]=0; //reset the stuck vector
										moveCounter=0;
										foodCount=0;
										disembcount=0;
										Harpoon.deactivate();
										Canvas.displayDigDugCrushed(display,dd.getLives());
										al_flip_display();
										al_rest(1.0);
										al_set_timer_count(timer,0);
										al_start_timer(timer);
										al_flush_event_queue(event_queue);
									}
								}
							}
						}
					}
				else{
					switch(rockCount%10) //this just gets the rock to shake back and forth
					{
					case 0:
					case 1:
					case 2:
					case 3:
					case 4:
						Rocks[i]->setPos(xy::makestruct(Rocks[i]->pos().x+2,Rocks[i]->pos().y));
						break;
					case 5:
					case 6: 
					case 7:
					case 8:
					case 9:
						Rocks[i]->setPos(xy::makestruct(Rocks[i]->pos().x-2,Rocks[i]->pos().y));
						break;
					}
				}
			if ( (openCount>5)&&(Rocks[i]->hasFallen()) ){
				Rocks[i]->open(); //play the "open" animation
			}
			if ( (openCount>60)&&(Rocks[i]->hasFallen())) {
				Rocks[i]->deactivate();
				Rocks.erase(Rocks.begin()+i);
				openCount=0;
			}
		}
		
		//add new tunnels
		tunnelArr.addTunnel(ddpos); //add dds position to the tunnel vector (only new ones are added, see implementation of this function in tunnels.cpp)
		dd.move(playerIn,step);
		ddpos=dd.pos(); //so next loop we have his previous pos if we need it
		if (ddpos.x<square_width)ddpos.x=square_width;
			else if (ddpos.y<square_width*2)ddpos.y=square_width*2;
		if (ddpos.x+square_width>scr_width)ddpos.x=scr_width-square_width;
				else if (ddpos.y+square_width>scr_height)ddpos.y=scr_height-square_width;
		
		dd.setpos(ddpos);
		
		Harpoon.move(dd.getDir(),step);
		monstVec.moveMonsters(step);
		monstStuck=monstVec.whosStuck();
		for (int i=0;i<monstStuck.size();i++) //disembody monsters who are stuck
		{
			if (monstStuck[i]==1)
			{
				bool found=0;
				int counter=0;
				while ( (!found)&&(counter<monstVec.getSize())&&(monstVec.isAlive(i)) )
					if ( monstVec.isDisembodied(counter))
						found=true;
					else counter++;
					if ((!found)&&(!monstVec.isDisembodied(i)&&(monstVec.getCountDisembodyIth(i)<5))){
						monstVec.setDisembodied(i,ddposGrid);
						disembcount=0;
				}
			}
		}
		//see if disembodied monsters has found a tunnel, only check after 0.5 seconds

		if (disembcount>60){ 
			for (int i=0;i<monstVec.getSize();i++)
			{
				if ( (tunnelArr.inTunnel(monstVec.getithPos(i)))&&(monstVec.isDisembodied(i)))
				{
					monstVec.reembody(i);
					bool found=0;
					int counter=0;
					disembcount=0;
				}
			}
		}
		else if (disembcount>120){
			for (int i=0;i<monstVec.getSize();i++)
				monstVec.giveUpTunnelSearch(i); //gives up the tunnel search if it still hasn't found a tunnel at this point
			disembcount=0;
		}
		//food

		if ( (foodCount>200)&&(!Food.isActive())&&(foodFull<foodMax) )
		{
			Food.changeFoodType(xy::makestruct(400,320));
			switch(Food.getFoodType()) //play thr appropriate sound clip depending on the food type generated
			{
				case CITYWOK:
					al_play_sample(cityWok, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					break;
				case DOUBLEDEW:
					al_play_sample(doubleDew, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					break;
				case DRUMSTICK:
					al_play_sample(kfcChicken, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					break;
				case POTPIE:
					al_play_sample(potPie, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					break;
			}
			foodFull++; //when foodFull=4 no more food will be generated
		}
		else if ( (foodCount>550))
		{
			foodCount=0;
			Food.deactivate();
		}
		
		if ( (dd.pos()==Food.pos())&&(Food.isActive()) )
		{
			al_play_sample(foodRegister, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			dd.increaseScore(1000);
			Food.deactivate();
			foodCount=0;
		}
		
		bool found=0;
		int counter=0;
		if (monstVec.getSize()==0)
		{
			al_flip_display();
			done=0;
			dd.increaseScore(250*dd.getLives()); //bonus points for having remaining lives
			al_play_sample(hooray, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			al_rest(1.5);
			return 'A';
		}
		al_clear_to_color(al_map_rgb(0,0,0));		//clear screen between rounds

	}
	//destory all allegro objects
	al_destroy_sample(harpoonZip);
	al_destroy_sample(dieOnce);
	al_destroy_sample(dieThree);
	al_destroy_sample(killMonst);
	al_destroy_sample(coffinDrop);
	al_destroy_sample(cityWok);
	al_destroy_sample(kfcChicken);
	al_destroy_sample(potPie);
	al_destroy_sample(doubleDew);
	al_destroy_sample(splat);
	al_destroy_sample(foodRegister);
	al_destroy_sample(rockGrunt);
	al_destroy_sample(hooray);
}

//other functions needed by the game loop which did not warrant a class

vector<int> getHighScores() //function that gets the high scores from the textfile and returns them in a vector
{
	ifstream highScoresFile("Highscores.txt");
	string line;
	vector<int> scores;
	if (highScoresFile.is_open())
		while (!highScoresFile.eof())
		{
			getline(highScoresFile,line);
			scores.push_back(atoi(line.c_str()));
		}
	return scores;
}

bool highScoreManager(int playerScoreForRound) //adds news highscores to the textfile if it is indeed a highscore. If the score passed is not a high score it leaves the file unmodified
{
	fstream highScoresFile("Highscores.txt");
	vector<int> scores;
	scores=getHighScores();
	bool found=0;
	int counter=scores.size()-1;
	while( (!found)&&(counter>=0) )
	{
		if (scores[counter]<playerScoreForRound)
			found=1;
		else
			counter--;
	}
	if(!found){
		highScoresFile.close();
		return 0;
	}
	else{
		scores[counter]=playerScoreForRound;
		sort(scores.begin(),scores.end());
		highScoresFile.clear();
		for(int i=scores.size()-1;i>=0;i--){
			highScoresFile<<scores[i];
			if(i!=0)
				highScoresFile<<endl; //don't add a line on the last entry
		}
		highScoresFile.close();
		return 1;
	}
} 

#endif
