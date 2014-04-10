#ifndef CANVAS_H
#define CANVAS_H

#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_native_dialog.h>

#include "tunnels.h"
#include "monsters.h"
#include "harpoon.h"
#include "rock.h"
#include "dragon.h"
#include "fooditem.h"

#include <vector>
#include "cmath"
#include <iostream> 

#include <boost/smart_ptr.hpp>
using boost::scoped_ptr;
using boost::shared_ptr;

typedef boost::shared_ptr<rock> rock_ptr;

//! Canvas is resonsible for the drawing of the characters and game screens.
/*! Canvas draws the main character (digdug) and the monsters in their various stages of animation.  The class draws the game screens, 
game layouts, text messages to the user and all other visual aspects of the game environment.  It holds the screen layouts as its private
data members. 
\author Damian Hinch, Joseph Penn
\version v0.3.8
\date 25/09/2012
*/

class canvas
{
public:
	canvas(const int blockSize,const int _score_panel_width,const int scr_width,const int scr_height,ALLEGRO_FONT *font);

	/*!< Functions for drawing gamescreen, objects and basic screen elements */  
	void drawScreen(ALLEGRO_DISPLAY *display);
	void drawDigDug(ALLEGRO_DISPLAY *display,const xy& pos, const int dir);
	void drawMonsters(ALLEGRO_DISPLAY *display,const monsters& monstVec);
	void drawTunnels(ALLEGRO_DISPLAY *display,const tunnels& tunArr);
	void drawHarpoon(ALLEGRO_DISPLAY *display,const harpoon& Harpoon,const int playerDir,const int stepSize);
	void drawRocks(ALLEGRO_DISPLAY *display,const vector<rock_ptr>& Rocks);
	void drawFood(ALLEGRO_DISPLAY *display,fooditem& Food);

	/*!< Functions for drawing splashscreens for game-player information and feedback */  
	void displaySplashScreen(ALLEGRO_DISPLAY *display);
	void displayDigDugCaught(ALLEGRO_DISPLAY *display,int lives);
	void displayDigDugCrushed(ALLEGRO_DISPLAY *display,const int lives);
	void displayGamePanel(ALLEGRO_DISPLAY *display,const int score,const int lives,const vector<int> highScores);
	void displayWin(ALLEGRO_DISPLAY *display,const int score);
	void displaySplashScreenEmpty(ALLEGRO_DISPLAY *display,const int score,const int lives);
	void displayLevel(ALLEGRO_DISPLAY *display,const int levelCount,const int score, const int lives);
	void displayLose(ALLEGRO_DISPLAY *display,const int score);
	void displayFoodRemaining(ALLEGRO_DISPLAY *display,int& foodLeft,ALLEGRO_FONT *font20);
	void displayHighScore(ALLEGRO_DISPLAY *display);

private:
	int _bSize; //block size, grid size for game screen
	int _score_panel_width;
	ALLEGRO_FONT *_font24;
	int _squareWidth;
	int _scr_height;
	int _scr_width; 

	/*!< Function for drawing earth textures for gamescreen */  
	void pixel_texture(int a, int b, int c1, int c2, int c3);

	/*!< Functions for drawing digdug character in various position animation states */  
	void drawDigDugUp   (ALLEGRO_DISPLAY *display,const xy& pos);
	void drawDigDugDown (ALLEGRO_DISPLAY *display,const xy& pos);
	void drawDigDugLeft (ALLEGRO_DISPLAY *display,const xy& pos);
	void drawDigDugRight(ALLEGRO_DISPLAY *display,const xy& pos);
	void drawDigDugResting(ALLEGRO_DISPLAY *display,const xy& pos);

	/*!< Functions for drawing basic monster (Clyde-Frog) in various position animation states */  
	void drawClydeUp   (ALLEGRO_DISPLAY *display,xy pos);
	void drawClydeLeft (ALLEGRO_DISPLAY *display,xy pos);
	void drawClydeRight(ALLEGRO_DISPLAY *display,xy pos);
	void drawClydeDown1(ALLEGRO_DISPLAY *display,xy pos);
	void drawClydeDown2(ALLEGRO_DISPLAY *display,xy pos);
	void drawClydeDown3(ALLEGRO_DISPLAY *display,xy pos);
	void drawClydeDown4(ALLEGRO_DISPLAY *display,xy pos);
	void drawClydeDown5(ALLEGRO_DISPLAY *display,xy pos);

	/*!< Functions for drawing basic monster (Clyde-Frog) in various swelling animation states */  
	void drawClydeSwelling1(ALLEGRO_DISPLAY *display,xy pos);
	void drawClydeSwelling2(ALLEGRO_DISPLAY *display,xy pos);
	void drawClydeSwelling3(ALLEGRO_DISPLAY *display,xy pos);
	void drawClydeSwelling4(ALLEGRO_DISPLAY *display,xy pos);
	void drawClydeSwelling5(ALLEGRO_DISPLAY *display,xy pos);
	void drawClydeSwelling6(ALLEGRO_DISPLAY *display,xy pos);
	void drawClydeSwellingPop(ALLEGRO_DISPLAY *display,xy pos);

	/*!< Function for drawing both monster types in disembodied animation state */  
	void drawMonstersDisembodied(ALLEGRO_DISPLAY *display,xy pos);

	/*!< Functions for drawing dragon in various position animation states */ 
	void drawDragonUp   (ALLEGRO_DISPLAY *display,xy pos);
	void drawDragonLeft (ALLEGRO_DISPLAY *display,xy pos);
	void drawDragonRight(ALLEGRO_DISPLAY *display,xy pos);
	void drawDragonDown1(ALLEGRO_DISPLAY *display,xy pos);
	void drawDragonDown2(ALLEGRO_DISPLAY *display,xy pos);
	void drawDragonDown3(ALLEGRO_DISPLAY *display,xy pos);
	void drawDragonDown4(ALLEGRO_DISPLAY *display,xy pos);
	void drawDragonDown5(ALLEGRO_DISPLAY *display,xy pos);

	/*!< Functions for drawing dragon in various swelling animation states */  
	void drawDragonSwelling1(ALLEGRO_DISPLAY *display,xy pos);
	void drawDragonSwelling2(ALLEGRO_DISPLAY *display,xy pos);
	void drawDragonSwelling3(ALLEGRO_DISPLAY *display,xy pos);
	void drawDragonSwelling4(ALLEGRO_DISPLAY *display,xy pos);
	void drawDragonSwelling5(ALLEGRO_DISPLAY *display,xy pos);
	void drawDragonSwelling6(ALLEGRO_DISPLAY *display,xy pos);
	void drawDragonSwellingPop(ALLEGRO_DISPLAY *display,xy pos);

	/*!< Functions for drawing dragon's flames in various position animation states */   
	void drawFlames(ALLEGRO_DISPLAY *display,xy pos,int curDirofDragon);
	void drawFlamesUp(ALLEGRO_DISPLAY *display,xy pos);
	void drawFlamesDown(ALLEGRO_DISPLAY *display,xy pos);
	void drawFlamesLeft(ALLEGRO_DISPLAY *display,xy pos);
	void drawFlamesRight(ALLEGRO_DISPLAY *display,xy pos);

	/*!< Functions for drawing harpoon tip in various position animation states */  
	void drawHarpoonTipUp   (ALLEGRO_DISPLAY *,xy pos);
	void drawHarpoonTipDown (ALLEGRO_DISPLAY *,xy pos);
	void drawHarpoonTipLeft (ALLEGRO_DISPLAY *,xy pos);
	void drawHarpoonTipRight(ALLEGRO_DISPLAY *,xy pos);

	/*!< Functions for drawing harpoon follow cord in relevant directional extensions */  
	void drawHarpoonCordUp   (ALLEGRO_DISPLAY *,xy pos,int cordLen);
	void drawHarpoonCordDown (ALLEGRO_DISPLAY *,xy pos,int cordLen);
	void drawHarpoonCordLeft (ALLEGRO_DISPLAY *,xy pos,int cordLen);
	void drawHarpoonCordRight(ALLEGRO_DISPLAY *,xy pos,int cordLen);

	/*!< Functions for drawing rocks (coffins) in open/closed and left/right orientation animation states */  
	void drawRockClosedLeft(ALLEGRO_DISPLAY *,xy pos);
	void drawRockClosedRight(ALLEGRO_DISPLAY *,xy pos);
	void drawRockOpenLeft(ALLEGRO_DISPLAY *,xy pos);
	void drawRockOpenRight(ALLEGRO_DISPLAY *,xy pos);

	/*!< Functions for drawing food-types graphics */   
	void drawCityWok(ALLEGRO_DISPLAY *,xy pos);
	void drawDrumStick(ALLEGRO_DISPLAY *,xy pos);
	void drawDoubleDew(ALLEGRO_DISPLAY *,xy pos);
	void drawPotPie(ALLEGRO_DISPLAY *,xy pos);

};

#endif