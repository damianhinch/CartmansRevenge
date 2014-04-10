#include <gtest/gtest.h>
#include "digdug.h"
#include "canvas.h"
#include "monster.h"
#include "monsters.h"
#include "clydefrog.h"
#include "dragon.h"
#include "objects.h"
#include "tunnels.h"
#include "harpoon.h"
#include "rock.h"
#include "fooditem.h"
#include "levelCreator.h"
#include "gameLoop.h"

#include <allegro5\allegro_native_dialog.h>

#include <vector>
#include <iostream>


TEST(ALLEGRO_DISPLAY,isDisplayWorking)
{
  	/*!<ALLEGRO */  
	ALLEGRO_EVENT_QUEUE *event_queue=NULL;
	ALLEGRO_KEYBOARD_STATE key_state;
	ALLEGRO_DISPLAY *display = NULL;

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
	EXPECT_TRUE(al_init()); 
	display = al_create_display(width,height);
	EXPECT_TRUE(display);
	al_destroy_display(display);
}

TEST(movement,canCharacterBeMoved)
{
	/*!<ALLEGRO */  
	ALLEGRO_EVENT_QUEUE *event_queue=NULL;
	ALLEGRO_KEYBOARD_STATE key_state;
	ALLEGRO_DISPLAY *display = NULL;

	/*!<Initialisation */  
	al_init();
	display = al_create_display(width,height);
	event_queue=al_create_event_queue();
	al_register_event_source(event_queue,al_get_display_event_source(display));
	al_init_primitives_addon();
	al_install_keyboard();
	al_install_mouse();
	
	/*!<Register events/sources*/  
	al_register_event_source(event_queue, al_get_keyboard_event_source());


	/*!<Install audio add-ins*/  
	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(30);

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
	al_clear_to_color(al_map_rgb(0,0,0));
	al_draw_text(font24,al_map_rgb(255,255,255),10,height/2-40,0,"Welcome to the testing suite.\n");
	al_draw_text(font24,al_map_rgb(255,255,255),10,height/2,0,"First you need to test if the character can move around the screen.");
	al_draw_text(font24,al_map_rgb(255,255,255),10,height/2+40,0,"Also check if you leave tunnels as you walk.");
	al_flip_display();
	al_rest(8.0);
	al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_text(font24,al_map_rgb(255,255,255),10,height/2-40,0,"Use the directional keys to move.");
	al_draw_text(font24,al_map_rgb(255,255,255),10,height/2,0,"Click the Windows close button when you are done.");
	al_flip_display();
	al_rest(6.0);
	Creator.instantiateLevel(dd,monstVec,tunnelArr,Rocks,43); 
	start(dd,monstVec,tunnelArr,Rocks,Harpoon,Canvas,Food,display,0);	

	int button = al_show_native_message_box(
     display,
     "Confirmation",
     "Did everything work?",
     "Please click \"Yes\" if everything worked as it was supposed to."
     "You should have been able to move the character and create tunnels."
     "Click \"No\" if you were not able to do this.",
	 NULL,
	ALLEGRO_MESSAGEBOX_YES_NO);
	EXPECT_EQ(button,1);
	al_destroy_display(display);
}

TEST(movement,canKillMonsterWithHarpoon)
{
	/*!<ALLEGRO */  
	ALLEGRO_EVENT_QUEUE *event_queue=NULL;
	ALLEGRO_KEYBOARD_STATE key_state;
	ALLEGRO_DISPLAY *display = NULL;

	/*!<Initialisation */  
	al_init();
	display = al_create_display(width,height);
	event_queue=al_create_event_queue();
	al_register_event_source(event_queue,al_get_display_event_source(display));
	al_init_primitives_addon();
	al_install_keyboard();
	al_install_mouse();

	/*!<Register events/sources*/  
	al_register_event_source(event_queue, al_get_keyboard_event_source());


		/*!<Install audio add-ins*/  
	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(30);

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
	al_clear_to_color(al_map_rgb(0,0,0));
	al_draw_text(font24,al_map_rgb(255,255,255),10,height/2-40,0,"Well done, you can move around properly!\n");
	al_draw_text(font24,al_map_rgb(255,255,255),10,height/2,0,"In the game there are monsters which attack you.");
	al_draw_text(font24,al_map_rgb(255,255,255),10,height/2+40,0,"But you can hit them first with your harpoon!");
	al_draw_text(font24,al_map_rgb(255,255,255),10,height/2+80,0,"You progress to new levels by killing all the monsters.");
	al_flip_display();
	al_rest(10.0);
	al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_text(font24,al_map_rgb(255,255,255),10,height/2-40,0,"Press and hold the space bar to fire the harpoon.");
	al_draw_text(font24,al_map_rgb(255,255,255),10,height/2,0,"You have 3 lives, displayed on the right of the screen.");
	al_flip_display();
	al_rest(7.0);
	Creator.instantiateLevel(dd,monstVec,tunnelArr,Rocks,44); 
	char playerState=start(dd,monstVec,tunnelArr,Rocks,Harpoon,Canvas,Food,display,0);	

	int button = al_show_native_message_box(
     display,
     "Confirmation",
     "Did the monster pop?",
     "Please click \"Yes\" if everything worked as it was supposed to."
     "The monster should have swollen up and exploaded after a few seconds."
     "Click \"No\" if you were not able to do this.",
     NULL,
     ALLEGRO_MESSAGEBOX_YES_NO);
  EXPECT_EQ(button,1);
  EXPECT_EQ(playerState,'A');
  al_destroy_display(display);
}

TEST(movement,canKillMonsterWithHarpoonWhenFacingSideways)
{
	/*!<ALLEGRO */  
	ALLEGRO_EVENT_QUEUE *event_queue=NULL;
	ALLEGRO_KEYBOARD_STATE key_state;
	ALLEGRO_DISPLAY *display = NULL;

	/*!<Initialisation */  
	al_init();
	display = al_create_display(width,height);
	event_queue=al_create_event_queue();
	al_register_event_source(event_queue,al_get_display_event_source(display));
	al_init_primitives_addon();
	al_install_keyboard();
	al_install_mouse();

	/*!<Register events/sources*/  
	al_register_event_source(event_queue, al_get_keyboard_event_source());

		/*!<Install audio add-ins*/  
	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(30);

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
	al_clear_to_color(al_map_rgb(0,0,0));
	al_draw_text(font24,al_map_rgb(255,255,255),10,height/2-40,0,"That was an easy one.\n");
	al_draw_text(font24,al_map_rgb(255,255,255),10,height/2,0,"If a monster is not underneath you, you need to turn to face it.");
	al_flip_display();
	al_rest(8.0);
	al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_text(font24,al_map_rgb(255,255,255),10,height/2-40,0,"Move towards the monster and fire the harpoon.");
	al_flip_display();
	al_rest(6.0);
	Creator.instantiateLevel(dd,monstVec,tunnelArr,Rocks,45); 
	char playerState=start(dd,monstVec,tunnelArr,Rocks,Harpoon,Canvas,Food,display,0);	
	int button = al_show_native_message_box(
     display,
     "Confirmation",
     "Did the monster pop?",
     "Please click \"Yes\" if everything worked as it was supposed to."
     "The monster should have swollen up and exploaded after a few seconds."
     "Click \"No\" if you were not able to do this.",
     NULL,
     ALLEGRO_MESSAGEBOX_YES_NO);
  EXPECT_EQ(button,1);
  EXPECT_EQ(playerState,'A');
  al_destroy_display(display);
}

TEST(movement,canKillMonsterWithARock)
{
	/*!<ALLEGRO */  
	ALLEGRO_EVENT_QUEUE *event_queue=NULL;
	ALLEGRO_KEYBOARD_STATE key_state;
	ALLEGRO_DISPLAY *display = NULL;

	/*!<Initialisation */  
	al_init();
	display = al_create_display(width,height);
	event_queue=al_create_event_queue();
	al_register_event_source(event_queue,al_get_display_event_source(display));
	al_init_primitives_addon();
	al_install_keyboard();
	al_install_mouse();

	/*!<Register events/sources*/  
	al_register_event_source(event_queue, al_get_keyboard_event_source());

		/*!<Install audio add-ins*/  
	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(30);

	ALLEGRO_FONT *font28 = al_load_font("south park.ttf",28,0);
	ALLEGRO_FONT *font24 = al_load_font("south park.ttf",24,0);

	/*!<Object Creation*/  
	canvas Canvas(square_width,scorePanelWidth,scr_width,scr_height,font28);
	digdug dd;
	dd.dead();dd.dead();//you only get one shot at this
	harpoon Harpoon;
	vector<rock_ptr> Rocks;
	monsters monstVec;
	fooditem Food(xy::makestruct(360,360));
	levelCreator Creator(3);
	tunnels tunnelArr;
	al_clear_to_color(al_map_rgb(0,0,0));
	al_draw_text(font24,al_map_rgb(255,255,255),10,height/2-40,0,"Great shot!\n");
	al_draw_text(font24,al_map_rgb(255,255,255),10,height/2,0,"You can also kill monsters by dropping coffins on them.");
	al_draw_text(font24,al_map_rgb(255,255,255),10,height/2+40,0,"Coffins can only be used once, and can also kill you!");
	al_flip_display();
	al_rest(8.0);
	al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_text(font24,al_map_rgb(255,255,255),10,height/2-40,0,"Move directly beneath the coffin, but don't linger too long!");
	al_flip_display();
	al_rest(5.0);
	Creator.instantiateLevel(dd,monstVec,tunnelArr,Rocks,46); 
	char playerState=start(dd,monstVec,tunnelArr,Rocks,Harpoon,Canvas,Food,display,0);	

	int button = al_show_native_message_box(
     display,
     "Confirmation",
     "Did the monster die?",
     "Please click \"Yes\" if everything worked as it was supposed to."
     "The monster should have been crushed by the rock."
     "Click \"No\" if you were not able to do this.",
     NULL,
     ALLEGRO_MESSAGEBOX_YES_NO);
  EXPECT_EQ(button,1);
  EXPECT_EQ(playerState,'A');
  al_destroy_display(display);
}

TEST(movement,rockCanKillDigDug)
{
	/*!<ALLEGRO */  
	ALLEGRO_EVENT_QUEUE *event_queue=NULL;
	ALLEGRO_KEYBOARD_STATE key_state;
	ALLEGRO_DISPLAY *display = NULL;

	/*!<Initialisation */  
	al_init();
	display = al_create_display(width,height);
	event_queue=al_create_event_queue();
	al_register_event_source(event_queue,al_get_display_event_source(display));
	al_init_primitives_addon();
	al_install_keyboard();
	al_install_mouse();

	/*!<Register events/sources*/  
	al_register_event_source(event_queue, al_get_keyboard_event_source());

		/*!<Install audio add-ins*/  
	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(30);

	ALLEGRO_FONT *font28 = al_load_font("south park.ttf",28,0);
	ALLEGRO_FONT *font24 = al_load_font("south park.ttf",24,0);

	/*!<Object Creation*/  
	canvas Canvas(square_width,scorePanelWidth,scr_width,scr_height,font28);
	digdug dd;
	dd.dead();dd.dead();
	harpoon Harpoon;
	vector<rock_ptr> Rocks;
	monsters monstVec;
	fooditem Food(xy::makestruct(360,360));
	levelCreator Creator(3);
	tunnels tunnelArr;
	al_clear_to_color(al_map_rgb(0,0,0));
	al_draw_text(font24,al_map_rgb(255,255,255),10,height/2-40,0,"Spot on!\n");
	al_draw_text(font24,al_map_rgb(255,255,255),10,height/2,0,"Falling coffins can also kill you. Let this happen now.");
	al_flip_display();
	al_rest(8.0);
	al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_text(font24,al_map_rgb(255,255,255),10,height/2-40,0,"Remain beneath the coffin and witness first hand.");
	al_flip_display();
	al_rest(5.0);
	Creator.instantiateLevel(dd,monstVec,tunnelArr,Rocks,47); 
	char playerState=start(dd,monstVec,tunnelArr,Rocks,Harpoon,Canvas,Food,display,0);	

	int button = al_show_native_message_box(
     display,
     "Confirmation",
     "Did the coffin kill you?",
     "Please click \"Yes\" if everything worked as it was supposed to."
     "You should have been crushed."
     "Click \"No\" if this did not happen.",
     NULL,
     ALLEGRO_MESSAGEBOX_YES_NO);
  EXPECT_EQ(button,1);
  EXPECT_EQ(playerState,'D');
  al_destroy_display(display);
}

TEST(movement,flamesCanKillDigDug)
{
	/*!<ALLEGRO */  
	ALLEGRO_EVENT_QUEUE *event_queue=NULL;
	ALLEGRO_KEYBOARD_STATE key_state;
	ALLEGRO_DISPLAY *display = NULL;

	/*!<Initialisation */  
	al_init();
	display = al_create_display(width,height);
	event_queue=al_create_event_queue();
	al_register_event_source(event_queue,al_get_display_event_source(display));
	al_init_primitives_addon();
	al_install_keyboard();
	al_install_mouse();

	/*!<Register events/sources*/  
	al_register_event_source(event_queue, al_get_keyboard_event_source());

		/*!<Install audio add-ins*/  
	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(30);

	ALLEGRO_FONT *font28 = al_load_font("south park.ttf",28,0);
	ALLEGRO_FONT *font24 = al_load_font("south park.ttf",24,0);

	/*!<Object Creation*/  
	canvas Canvas(square_width,scorePanelWidth,scr_width,scr_height,font28);
	digdug dd;
	dd.dead();dd.dead();
	harpoon Harpoon;
	vector<rock_ptr> Rocks;
	monsters monstVec;
	fooditem Food(xy::makestruct(360,360));
	levelCreator Creator(3);
	tunnels tunnelArr;
	al_clear_to_color(al_map_rgb(0,0,0));
	al_draw_text(font24,al_map_rgb(255,255,255),10,height/2-40,0,"Ouch...\n");
	al_draw_text(font24,al_map_rgb(255,255,255),10,height/2,0,"There are different types of monsters, both of which can kill you.");
	al_draw_text(font24,al_map_rgb(255,255,255),10,height/2+40,0,"If a monster catches you by reaching your position, you will die.");
	al_draw_text(font24,al_map_rgb(255,255,255),10,height/2+80,0,"Dragons have the additional skill of roasting you in their flames.");
	al_flip_display();
	al_rest(10.0);
	al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_text(font24,al_map_rgb(255,255,255),10,height/2-40,0,"Stand still and feel the burn!");
	al_flip_display();
	al_rest(5.0);
	Creator.instantiateLevel(dd,monstVec,tunnelArr,Rocks,48); 
	char playerState=start(dd,monstVec,tunnelArr,Rocks,Harpoon,Canvas,Food,display,1);	

	int button = al_show_native_message_box(
     display,
     "Confirmation",
     "Did your goose get cooked?",
     "Please click \"Yes\" if everything worked as it was supposed to."
     "You should have been killed."
     "Click \"No\" if this did not happen.",
     NULL,
     ALLEGRO_MESSAGEBOX_YES_NO);
  EXPECT_EQ(button,1);
  EXPECT_EQ(playerState,'D');
  al_destroy_display(display);
}


TEST(movement,canCollectBonusFoodItems)
{
	/*!<ALLEGRO */  
	ALLEGRO_EVENT_QUEUE *event_queue=NULL;
	ALLEGRO_KEYBOARD_STATE key_state;
	ALLEGRO_DISPLAY *display = NULL;

	/*!<Initialisation */  
	al_init();
	display = al_create_display(width,height);
	event_queue=al_create_event_queue();
	al_register_event_source(event_queue,al_get_display_event_source(display));
	al_init_primitives_addon();
	al_install_keyboard();
	al_install_mouse();

	/*!<Register events/sources*/  
	al_register_event_source(event_queue, al_get_keyboard_event_source());

		/*!<Install audio add-ins*/  
	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(30);

	ALLEGRO_FONT *font28 = al_load_font("south park.ttf",28,0);
	ALLEGRO_FONT *font24 = al_load_font("south park.ttf",24,0);

	/*!<Object Creation*/  
	canvas Canvas(square_width,scorePanelWidth,scr_width,scr_height,font28);
	digdug dd;
	dd.dead();dd.dead();
	harpoon Harpoon;
	vector<rock_ptr> Rocks;
	monsters monstVec;
	fooditem Food(xy::makestruct(360,360));
	levelCreator Creator(3);
	tunnels tunnelArr;
	al_clear_to_color(al_map_rgb(0,0,0));
	al_draw_text(font24,al_map_rgb(255,255,255),10,height/2-40,0,"You seem to be excellent at getting killed!");
	al_draw_text(font24,al_map_rgb(255,255,255),10,height/2,0,"Bonus food items appear repeatedly throughout the game.");
	al_draw_text(font24,al_map_rgb(255,255,255),10,height/2+40,0,"Bonus items increase your score by 1000 points.");
	al_draw_text(font24,al_map_rgb(255,255,255),10,height/2+80,0,"4 items in total will appear.");
	al_flip_display();
	al_rest(10.0);
	al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_text(font24,al_map_rgb(255,255,255),10,height/2-40,0,"Wait for an item to appear and move over it to take a bite!");
	al_draw_text(font24,al_map_rgb(255,255,255),10,height/2,0,"Move away from the centre, and wait for the next food to appear.");
	al_draw_text(font24,al_map_rgb(255,255,255),10,height/2+40,0,"Click the Windows close button when you are done eating.");
	al_flip_display();
	al_rest(8.0);
	Creator.instantiateLevel(dd,monstVec,tunnelArr,Rocks,49); 
	char playerState=start(dd,monstVec,tunnelArr,Rocks,Harpoon,Canvas,Food,display,4);	

	int button = al_show_native_message_box(
     display,
     "Confirmation",
     "Did you collect the food item and did your score increase?",
     "Please click \"Yes\" if everything worked as it was supposed to."
     "Click \"No\" if this did not happen.",
     NULL,
     ALLEGRO_MESSAGEBOX_YES_NO);
	EXPECT_EQ(button,1);

	al_draw_text(font24,al_map_rgb(255,255,255),10,height/2-40,0,"Snack time! You're not fat, you're just big boned!");
	al_draw_text(font24,al_map_rgb(255,255,255),10,height/2,0,"WELL DONE you have completed the test suite.");
	al_draw_text(font24,al_map_rgb(255,255,255),10,height/2+40,0,"Looks like you're ready for the real game!");
	al_flip_display();
	al_rest(10.0);
	al_destroy_display(display);
}