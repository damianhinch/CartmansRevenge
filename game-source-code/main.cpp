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
#include "levelCreator.h"

#include "gameLoop.h"

using namespace std;

//! Overall control loop for the game.
/*! The menu and splash screens, initialisation and high score management are
performed within the main function. The function 'start', which executes the 
the actual game, is called from within the main function control loop. When the 
'start' function terminates, it returns to this control loop and allows the user 
to choose whether to play the game again or quit.
\author Damian Hinch, Joseph Penn
\version v0.3.8
\date 25/09/2012
*/


int main()
{
	/*!<ALLEGRO */  
	ALLEGRO_EVENT_QUEUE *event_queue=NULL;
	ALLEGRO_KEYBOARD_STATE key_state;
	ALLEGRO_DISPLAY *display = NULL;

	/*!<ALLEGRO audio */  
	ALLEGRO_SAMPLE *hereWeGo = NULL;
	ALLEGRO_SAMPLE *winHippies = NULL;
	ALLEGRO_SAMPLE *busStop = NULL;
	ALLEGRO_SAMPLE *winGame = NULL;
	ALLEGRO_SAMPLE *menuSong = NULL;
	ALLEGRO_SAMPLE_INSTANCE *songInstance = NULL;

	/*!<Initialisation */  
	al_init();
	display = al_create_display(width,height);
	event_queue=al_create_event_queue();
	al_register_event_source(event_queue,al_get_display_event_source(display));
	al_init_primitives_addon();
	al_install_keyboard();
	al_install_mouse();
	al_init_font_addon(); 
    al_init_ttf_addon();
	
	/*!<Register events/sources*/  
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue,al_get_display_event_source(display));

	/*!<Install audio add-ins*/  
	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(30);

	/*!<Fonts */  
	ALLEGRO_FONT *font28 = al_load_font("south park.ttf",28,0);
	ALLEGRO_FONT *font24 = al_load_font("south park.ttf",24,0);

	/*!<Object Creation*/  
	canvas Canvas(square_width,scorePanelWidth,scr_width,scr_height,font28);
	digdug dd;
	harpoon Harpoon;
	vector<rock_ptr> Rocks;
	monsters monstVec;
	fooditem Food(xy::makestruct(360,360));
	levelCreator Creator(3);
	tunnels tunnelArr;

	/*!<Load audio samples*/  
	hereWeGo = al_load_sample("HereWeGo.wav");
	winHippies = al_load_sample("WinHippies.wav");
	busStop = al_load_sample("BusStop.wav");
	winGame=al_load_sample("NaNaHaHa.wav");
	menuSong = al_load_sample("menuSong.wav");

	songInstance = al_create_sample_instance(menuSong);
	al_set_sample_instance_playmode(songInstance,ALLEGRO_PLAYMODE_LOOP);

	al_attach_sample_instance_to_mixer(songInstance,al_get_default_mixer());

	int levelCount=1;
	char cPlayerState='A';
	char playerChoice='Z';
	vector<int> scores;
	
	al_clear_to_color(al_map_rgb(0,0,0));
	Canvas.displaySplashScreen(display);
	al_flip_display();

	/*!<Start of control loop */  

	while(playerChoice!='q')
	{
		cPlayerState='A'; 
		al_play_sample_instance(songInstance);
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue,&ev);
		if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
		switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_SPACE:  	/*!< Game begins when the user presses space bar key*/  
				while(cPlayerState=='A'){ 	/*!<While character is alive*/  
					al_stop_sample_instance(songInstance);
					al_play_sample(hereWeGo, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					if(levelCount==1)al_rest(0.5);
					Canvas.displaySplashScreenEmpty(display,dd.getScore(),dd.getLives());
					Canvas.displayLevel(display,levelCount,dd.getScore(),dd.getLives());
					if(levelCount==1){
						al_play_sample(busStop, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					}
					Creator.instantiateLevel(dd,monstVec,tunnelArr,Rocks,levelCount); 	/*!<Instantiates the appropriate level*/  
					cPlayerState=start(dd,monstVec,tunnelArr,Rocks,Harpoon,Canvas,Food,display);
					cout<<cPlayerState;
					if(cPlayerState!='q'){
						if(cPlayerState=='A'){ //if the player is still alive
							levelCount++; //increase the level
						}
						else if (cPlayerState=='D'){ //if player is now dead
							al_clear_to_color(al_map_rgb(0,0,0));
							Canvas.displaySplashScreenEmpty(display,dd.getScore(),dd.getLives());
							Canvas.displayLose(display,dd.getScore());
							Canvas.displaySplashScreenEmpty(display,dd.getScore(),dd.getLives());
							if(highScoreManager(dd.getScore())){ //if the user has got a high score, congratulate him
								Canvas.displayHighScore(display);
								al_play_sample(winHippies, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
								al_flip_display();
								al_rest(5);
							}
							Canvas.displaySplashScreen(display);
							levelCount=1; //reset the level count so that if the user plays again it will start at the beginning
							dd.restoreLives();
							dd.increaseScore(-1*dd.getScore()); //reset his score to 0
							al_flush_event_queue(event_queue);
						}
						if(levelCount>=4){//i.e. the player has now completed all availible levels
							al_play_sample(winGame, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
							Canvas.displaySplashScreenEmpty(display,dd.getScore(),dd.getLives());
							Canvas.displayWin(display,dd.getScore());
							Canvas.displaySplashScreenEmpty(display,dd.getScore(),dd.getLives());
							if(highScoreManager(dd.getScore())){ //if the user has got a high score, congratulate him
								Canvas.displayHighScore(display);
								al_play_sample(winHippies, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
								al_flip_display();
								al_rest(5);
							}
							Canvas.displaySplashScreen(display);
							levelCount=1; //reset level count
							dd.increaseScore(-1*dd.getScore());//reset score
							dd.restoreLives(); //restore dds lives 
							al_flush_event_queue(event_queue);
							cPlayerState='T'; //anything that isn't q to A
						}
					}
					else playerChoice='q';

				}//end while
				break;
			case ALLEGRO_KEY_Q:
				playerChoice='q'; //this will make the game exit
				break;
			default:
				break;
			}
		}
		if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) playerChoice = 'q';

	}
    al_destroy_display(display);
	al_destroy_sample(hereWeGo);
	al_destroy_sample(winHippies);
	al_destroy_sample(busStop);
	al_destroy_sample(winGame);
	al_destroy_sample(menuSong);
	al_destroy_sample_instance(songInstance);
    return 0;
}
