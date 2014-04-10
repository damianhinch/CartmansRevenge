#include "canvas.h"

canvas::canvas(const int blockSize,const int score_panel_width,const int scr_width,const int scr_height,ALLEGRO_FONT *font)
	:_bSize(blockSize),_score_panel_width(score_panel_width),_squareWidth(blockSize),_scr_height( scr_height),_scr_width(scr_width),_font24(font){}

void canvas::pixel_texture(int a, int b, int c1, int c2, int c3){
		al_draw_filled_circle(_bSize*a + 7, _bSize*b + _bSize + 5, 1, al_map_rgb(c1,c2,c3));     //1 in book
		al_draw_filled_circle(_bSize*a + 24, _bSize*b + _bSize + 3, 1, al_map_rgb(c1,c2,c3));    //2
		al_draw_filled_circle(_bSize*a + 12, _bSize*b + _bSize + 12, 1, al_map_rgb(c1,c2,c3));	 //3
		al_draw_filled_circle(_bSize*a + 38, _bSize*b + _bSize + 5, 1, al_map_rgb(c1,c2,c3));	 //4
		al_draw_filled_circle(_bSize*a + 28, _bSize*b + _bSize + 14, 1, al_map_rgb(c1,c2,c3));	 //5
		al_draw_filled_circle(_bSize*a + 6, _bSize*b + _bSize + 24, 1, al_map_rgb(c1,c2,c3));	 //6
		al_draw_filled_circle(_bSize*a + 18, _bSize*b + _bSize + 22, 1, al_map_rgb(c1,c2,c3));	 //7
		al_draw_filled_circle(_bSize*a + 31, _bSize*b + _bSize + 22, 1, al_map_rgb(c1,c2,c3));	 //8
		al_draw_filled_circle(_bSize*a + 25, _bSize*b + _bSize + 33, 1, al_map_rgb(c1,c2,c3));	 //10		
		al_draw_filled_circle(_bSize*a + 38, _bSize*b + _bSize + 32, 1, al_map_rgb(c1,c2,c3));	 //11
		al_draw_filled_circle(_bSize*a + 11, _bSize*b + _bSize + 39, 1, al_map_rgb(c1,c2,c3));	 //12
		al_draw_filled_circle(_bSize*a + 15, _bSize*b + _bSize + 31, 1, al_map_rgb(c1,c2,c3));	 //17
		al_draw_filled_circle(_bSize*a + 38, _bSize*b + _bSize + 17, 1, al_map_rgb(c1,c2,c3));	 //18
} 

void canvas::drawScreen(ALLEGRO_DISPLAY *display)
{

	
	for (int i = 1; i < 17; i++){
		for (int j = 1; j < 5; j++){
			al_draw_filled_rectangle(_bSize*i,_bSize*j + _bSize, _bSize*i+_bSize, _bSize*j + 2*_bSize, al_map_rgb(234,252,102));
			pixel_texture(i,j, 254, 172, 78);

		}
		for (int j = 5; j < 9; j++){
			al_draw_filled_rectangle(_bSize*i,_bSize*j + _bSize, _bSize*i+_bSize, _bSize*j + 2*_bSize, al_map_rgb(254,172,78));
			pixel_texture(i,j, 234, 252, 102);
		}
		for (int j = 9; j < 13; j++){
			al_draw_filled_rectangle(_bSize*i,_bSize*j + _bSize, _bSize*i+_bSize, _bSize*j + 2*_bSize, al_map_rgb(254,172,78));
			pixel_texture(i,j, 183, 101, 6);
		}
		for (int j = 13; j < 17; j++){
			al_draw_filled_rectangle(_bSize*i,_bSize*j + _bSize, _bSize*i+_bSize, _bSize*j + 2*_bSize, al_map_rgb(183,101,6));
			pixel_texture(i,j, 254, 172, 78);
		}
	}

	al_draw_line(_bSize-2,_bSize-1,_bSize*17 + _score_panel_width+1,_bSize-1,al_map_rgb(255,255,255),2);							//top horizontal
	al_draw_line(_bSize-2,_bSize*17 + _bSize+1,_bSize*17 + _score_panel_width+1,_bSize*17 + _bSize+1,al_map_rgb(255,255,255),2);	//bottom horizontal			
	al_draw_line(_bSize-1,_bSize,_bSize-1,_bSize*17 + _bSize,al_map_rgb(255,255,255),2);										//left vertical
	al_draw_line(_bSize*17+1,_bSize,_bSize*17+1,_bSize*17 + _bSize,al_map_rgb(255,255,255),2);								//scoreboard left vertical
	al_draw_line(_bSize*17 + _score_panel_width,_bSize,_bSize*17 + _score_panel_width,_bSize*17 + _bSize,al_map_rgb(255,255,255),2);  //right vertical end

}

void canvas::drawDigDug(ALLEGRO_DISPLAY *display,const xy& pos,const int dir)
{
	switch (dir)
	{
	case UP:
		drawDigDugUp(display,pos);
		break;
	case DOWN:
		drawDigDugDown(display,pos);
		break;
	case LEFT:
		drawDigDugLeft(display,pos);
		break;
	case RIGHT:
		drawDigDugRight(display,pos);
		break;
	case STOP:
		drawDigDugResting(display,pos);
	}
}

void canvas::drawMonsters(ALLEGRO_DISPLAY *display,const monsters &monstVec)
{
	int x=0;
	int y=0;
	//if disembodied, draw one thing, else draw another thing

	for (int i=0;i<monstVec.getSize();i++){	
		int harpoonCount=monstVec.getithMonster(i)->isHarpooned();
		int animCount=monstVec.getithMonster(i)->getAnimCount();
		if (monstVec.isAlive(i)){
			if (monstVec.isDisembodied(i)){
				drawMonstersDisembodied(display,monstVec.getithPos(i));
			}
				////////////////////////////////////////
			else {
				bool isDragon=0;
				dragon* pDragon = dynamic_cast<dragon*>(monstVec.getithMonster(i)); // Attempt to convert pointer
				if(pDragon)
				{
					isDragon=1;
				}
				if(!isDragon){
					if (harpoonCount!=0){
						if (harpoonCount<15)
							drawClydeSwelling1(display,monstVec.getithPos(i));
						else if (harpoonCount<30)
							drawClydeSwelling2(display,monstVec.getithPos(i));
						else if (harpoonCount<45)
							drawClydeSwelling3(display,monstVec.getithPos(i));
						else if (harpoonCount<60)
							drawClydeSwelling4(display,monstVec.getithPos(i));
						else if (harpoonCount<75)
							drawClydeSwelling5(display,monstVec.getithPos(i));
						else if (harpoonCount<90)
							drawClydeSwelling6(display,monstVec.getithPos(i));
						else if (harpoonCount>90)
							drawClydeSwellingPop(display,monstVec.getithPos(i));
					}
					else{
						switch(monstVec.getithDir(i))
						{
						case UP:
							drawClydeUp(display,monstVec.getithPos(i));
							break;
						case DOWN:
							if (animCount<5)
								drawClydeDown1(display,monstVec.getithPos(i));
							else if (animCount<10)
								drawClydeDown2(display,monstVec.getithPos(i));
							else if (animCount<15)
								drawClydeDown3(display,monstVec.getithPos(i));
							else if (animCount<20)
								drawClydeDown4(display,monstVec.getithPos(i));
							else if (animCount<25)
									drawClydeDown5(display,monstVec.getithPos(i));
							break;
						case LEFT:
							drawClydeLeft(display,monstVec.getithPos(i));
							break;
						case RIGHT:
							drawClydeRight(display,monstVec.getithPos(i));
							break;
						default:
							drawClydeUp(display,monstVec.getithPos(i));
						}
					}
				}
				else{ //its a dragon
					if (harpoonCount!=0){
						if (harpoonCount<15)
							drawDragonSwelling1(display,monstVec.getithPos(i));
						else if (harpoonCount<30)
							drawDragonSwelling2(display,monstVec.getithPos(i));
						else if (harpoonCount<45)
							drawDragonSwelling3(display,monstVec.getithPos(i));
						else if (harpoonCount<60)
							drawDragonSwelling4(display,monstVec.getithPos(i));
						else if (harpoonCount<75)
							drawDragonSwelling5(display,monstVec.getithPos(i));
						else if (harpoonCount<90)
							drawDragonSwelling6(display,monstVec.getithPos(i));
						else if (harpoonCount>90)
							drawDragonSwellingPop(display,monstVec.getithPos(i));
					}
					else{
						switch(monstVec.getithDir(i))
						{
						case UP:
							drawDragonUp(display,monstVec.getithPos(i));
							break;
						case DOWN:
							if (animCount<5)
								drawDragonDown1(display,monstVec.getithPos(i));
							else if (animCount<10)
								drawDragonDown2(display,monstVec.getithPos(i));
							else if (animCount<15)
								drawDragonDown3(display,monstVec.getithPos(i));
							else if (animCount<20)
								drawDragonDown4(display,monstVec.getithPos(i));
							else if (animCount<25)
								drawDragonDown5(display,monstVec.getithPos(i));
							break;
						case LEFT:
							drawDragonLeft(display,monstVec.getithPos(i));
							break;
						case RIGHT:
							drawDragonRight(display,monstVec.getithPos(i));
							break;
						default:
							drawDragonUp(display,monstVec.getithPos(i));
						}
						if (monstVec.getithIsAttacking(i))//only draw flames if the monster is attacking
							drawFlames(display,monstVec.getithPos(i),monstVec.getithDir(i));
					}
				}

			}
		}
	}
}

void canvas::drawTunnels(ALLEGRO_DISPLAY *display,const tunnels &tunArr)
{
	int x=0;
	int y=0;
	for(int i=0;i<tunArr.getSize();i++){
		x=tunArr.getIthTun(i).x;
		y=tunArr.getIthTun(i).y;
		al_draw_filled_rectangle(x,y,x+_bSize,y+_bSize,al_map_rgb(0,0,0));
	}
}

void canvas::drawHarpoon(ALLEGRO_DISPLAY *display,const harpoon& Harpoon,const int playerDir,const int stepSize)
{
	int cordLen=0;
	cordLen=Harpoon.getLength()*4;
	if (Harpoon.isActive())
	{
		switch(playerDir){
		case UP:
			drawHarpoonTipUp(display,Harpoon.pos());
			drawHarpoonCordUp(display,Harpoon.pos(),cordLen);
			break;
		case DOWN:
			drawHarpoonTipDown(display,Harpoon.pos());
			drawHarpoonCordDown(display,Harpoon.pos(),cordLen);
			break;
		case LEFT:
			drawHarpoonTipLeft(display,Harpoon.pos());
			drawHarpoonCordLeft(display,Harpoon.pos(),cordLen);
			break;
		case RIGHT:
			drawHarpoonTipRight(display,Harpoon.pos());
			drawHarpoonCordRight(display,Harpoon.pos(),cordLen);
			break;
		case STOP:
			drawHarpoonTipDown(display,Harpoon.pos());
			drawHarpoonCordDown(display,Harpoon.pos(),cordLen);
			break;
		default:
			break;
		}
	}
}

void canvas::drawRocks(ALLEGRO_DISPLAY *display,const vector<rock_ptr>& Rocks)
{
	for (int i=0;i<Rocks.size();i++){
		if (Rocks[i]->isActive() ){
			if (Rocks[i]->getLeftRight()) //right
				if (Rocks[i]->isOpen())//is at bottom
					drawRockOpenRight(display,Rocks[i]->pos());
				else
					drawRockClosedRight(display,Rocks[i]->pos());
			else
				if (Rocks[i]->isOpen()) //is left and at bottom
					drawRockOpenLeft(display,Rocks[i]->pos());
				else
					drawRockClosedLeft(display,Rocks[i]->pos());
		}
	}
}

void canvas::drawFood(ALLEGRO_DISPLAY *display,fooditem& Food)
{
	if (Food.isActive())
		switch(Food.getFoodType())
		{
		case DRUMSTICK:
			drawDrumStick(display,Food.pos());
			break;
		case DOUBLEDEW:
			drawDoubleDew(display,Food.pos());
			break;
		case POTPIE:
			drawPotPie(display,Food.pos());
			break;
		case CITYWOK:
			drawCityWok(display,Food.pos());
			break;
		default: //should never get here
			drawPotPie(display,Food.pos());
			break;

		}
}

////////////private..............................

/////////////////////////////////////////////
///////////////////Cartman//////////////////

void canvas::drawDigDugDown(ALLEGRO_DISPLAY *display,const xy& pos)
{
	//DRAW CHARACTER
		//al_draw_filled_rectangle(pos.x, pos.y, pos.x + 40, pos.y + 40, al_map_rgb(0,0,0));  //background

		al_draw_filled_rectangle(pos.x+5, pos.y + 30, pos.x + 35, pos.y + 38,al_map_rgb(104,67,58)); // legs

		//basic ellipses
		al_draw_filled_ellipse(pos.x + 20, pos.y + 28, 18, 10, al_map_rgb(178,21,68)); // body
		al_draw_filled_ellipse(pos.x + 20, pos.y + 14, 15, 12, al_map_rgb(80,169,164)); // hat - is base for whole head
		al_draw_filled_ellipse(pos.x + 20, pos.y + 18, 15, 10, al_map_rgb(209,183,155)); // face

		
		//hat baubles
		al_draw_filled_circle(pos.x + 19, pos.y + 3, 1, al_map_rgb(208,198,14));
		al_draw_filled_circle(pos.x + 20, pos.y + 3, 2, al_map_rgb(208,198,14));
		al_draw_filled_circle(pos.x + 21, pos.y + 3, 1, al_map_rgb(208,198,14));
		al_draw_filled_circle(pos.x + 17, pos.y + 3, 1, al_map_rgb(208,198,14));
		al_draw_filled_circle(pos.x + 23, pos.y + 3, 1, al_map_rgb(208,198,14));

		//hat splines
		float pointsBlue[] = {pos.x + 5, pos.y + 15, pos.x + 10, pos.y + 7, pos.x + 30, pos.y + 7, pos.x + 35, pos.y + 15}; //blue spline
		al_draw_spline(pointsBlue, al_map_rgb(80,169,164), 2); 
		float pointsYellow[] = {pos.x + 5, pos.y + 16, pos.x + 10, pos.y + 8, pos.x + 30, pos.y + 8, pos.x + 35, pos.y + 16}; //yellow spline
		al_draw_spline(pointsYellow, al_map_rgb(208,198,14), 2); 

		
		
		//eyes
		al_draw_filled_circle(pos.x + 15, pos.y + 16, 5, al_map_rgb(208,208,208));
		al_draw_filled_circle(pos.x + 25, pos.y + 16, 5, al_map_rgb(208,208,208));
		al_draw_filled_circle(pos.x + 16, pos.y + 17, 1, al_map_rgb(59,50,17));
		al_draw_filled_circle(pos.x + 24, pos.y + 17, 1, al_map_rgb(59,50,17));

		//eyebrows
		al_draw_line(pos.x + 19, pos.y + 13, pos.x + 12, pos.y + 8, al_map_rgb(59,50,17),1);
		al_draw_line(pos.x + 21, pos.y + 13, pos.x + 28, pos.y + 8, al_map_rgb(59,50,17),1);
				
		al_draw_filled_circle(pos.x + 12, pos.y + 32, 3, al_map_rgb(208,198,14)); // hands
		al_draw_filled_circle(pos.x + 28, pos.y + 32, 3, al_map_rgb(208,198,14));
		al_draw_filled_circle(pos.x + 12, pos.y + 29, 1, al_map_rgb(208,198,14)); //thumbs
		al_draw_filled_circle(pos.x + 28, pos.y + 29, 1, al_map_rgb(208,198,14));

		//mouth
		al_draw_filled_triangle(pos.x + 15, pos.y + 23, pos.x + 25, pos.y + 23, pos.x + 20, pos.y + 26, al_map_rgb(59,50,17));

		//buttons
		al_draw_filled_circle(pos.x + 20, pos.y + 30, 1, al_map_rgb(59,50,17));
		al_draw_filled_circle(pos.x + 20, pos.y + 33, 1, al_map_rgb(59,50,17));
		al_draw_filled_circle(pos.x + 20, pos.y + 36, 1, al_map_rgb(59,50,17));

}
void canvas::drawDigDugUp(ALLEGRO_DISPLAY *display,const xy& pos)
{
	//DRAW CHARACTER
		//al_draw_filled_rectangle(pos.x, pos.y, pos.x + 40, pos.y + 40, al_map_rgb(0,0,0));  //background

		al_draw_filled_rectangle(pos.x+5, pos.y + 30, pos.x + 35, pos.y + 38,al_map_rgb(104,67,58)); // legs

		//basic ellipses
		al_draw_filled_ellipse(pos.x + 20, pos.y + 14, 15, 12, al_map_rgb(80,169,164)); // hat - is base for whole head
		al_draw_filled_ellipse(pos.x + 20, pos.y + 18, 15, 10, al_map_rgb(209,183,155)); // face - back of head sides
		al_draw_filled_ellipse(pos.x + 20, pos.y + 12, 15, 5, al_map_rgb(80,169,164)); // hat extender

		//hat splines - inverted
		float pointsYellowBack[] = {pos.x + 5, pos.y + 13, pos.x + 10, pos.y + 19, pos.x + 30, pos.y + 19, pos.x + 35, pos.y + 13}; //yellow spline
		al_draw_spline(pointsYellowBack, al_map_rgb(208,198,14), 2); 

		//body - drawn over head objects
		al_draw_filled_ellipse(pos.x + 20, pos.y + 28, 18, 10, al_map_rgb(178,21,68)); // body
	
		//hat baubles
		al_draw_filled_circle(pos.x + 19, pos.y + 6, 1, al_map_rgb(208,198,14));
		al_draw_filled_circle(pos.x + 20, pos.y + 6, 2, al_map_rgb(208,198,14));
		al_draw_filled_circle(pos.x + 21, pos.y + 6, 1, al_map_rgb(208,198,14));
		al_draw_filled_circle(pos.x + 17, pos.y + 6, 1, al_map_rgb(208,198,14));
		al_draw_filled_circle(pos.x + 23, pos.y + 6, 1, al_map_rgb(208,198,14));
}
void canvas::drawDigDugLeft(ALLEGRO_DISPLAY *display,const xy& pos)
{
	//DRAW CHARACTER
		//al_draw_filled_rectangle(pos.x, pos.y, pos.x + 40, pos.y + 40, al_map_rgb(0,0,0));  //background

		//legs
		al_draw_filled_rectangle(pos.x+10, pos.y + 30, pos.x + 33, pos.y + 38,al_map_rgb(104,67,58));

		//body
		al_draw_filled_rounded_rectangle(pos.x + 5, pos.y + 23, pos.x + 37, pos.y + 36, 5, 5, al_map_rgb(178,21,68)); // body
		al_draw_filled_circle(pos.x + 31, pos.y + 25, 6, al_map_rgb(178,21,68)); // neck area circle 1
		al_draw_filled_circle(pos.x + 31, pos.y + 26, 6, al_map_rgb(178,21,68)); // neck area circle 2

		//head
		al_draw_filled_ellipse(pos.x + 20, pos.y + 15, 15, 12, al_map_rgb(209,183,155)); // face - flesh tone

		//eye
		al_draw_filled_circle(pos.x + 10, pos.y + 15, 5, al_map_rgb(208,208,208));
		al_draw_filled_circle(pos.x + 7, pos.y + 15, 1, al_map_rgb(59,50,17));
	
		//hat splines
		float pointsBlueLeft1[] = {pos.x + 7, pos.y + 10, pos.x + 10, pos.y + 2, pos.x + 30, pos.y + 2, pos.x + 33, pos.y + 11}; //blue spline
		al_draw_spline(pointsBlueLeft1, al_map_rgb(80,169,164), 3); 
		float pointsBlueLeft2[] = {pos.x + 9, pos.y + 10, pos.x + 12, pos.y + 4, pos.x + 28, pos.y + 4, pos.x + 33, pos.y + 13}; //blue spline
		al_draw_spline(pointsBlueLeft2, al_map_rgb(80,169,164), 3); 
		float pointsBlueLeft3[] = {pos.x + 11, pos.y + 10, pos.x + 14, pos.y + 6, pos.x + 26, pos.y + 6, pos.x + 35, pos.y + 14}; //blue spline
		al_draw_spline(pointsBlueLeft3, al_map_rgb(80,169,164), 3); 
		float pointsBlueLeft4[] = {pos.x + 11, pos.y + 10, pos.x + 16, pos.y + 8, pos.x + 24, pos.y + 8, pos.x + 35, pos.y + 16}; //blue spline
		al_draw_spline(pointsBlueLeft4, al_map_rgb(80,169,164), 3); 
		float pointsBlueLeft5[] = {pos.x + 6, pos.y + 10, pos.x + 18, pos.y + 11, pos.x + 26, pos.y + 11, pos.x + 35, pos.y + 18}; //yellow spline
		al_draw_spline(pointsBlueLeft5, al_map_rgb(80,169,164), 2);
		float pointsYellowLeft[] = {pos.x + 6, pos.y + 10, pos.x + 16, pos.y + 12, pos.x + 24, pos.y + 13, pos.x + 35, pos.y + 18}; //yellow spline
		al_draw_spline(pointsYellowLeft, al_map_rgb(208,198,14), 2); 

		//hat baubles
		al_draw_filled_circle(pos.x + 21, pos.y + 3, 1, al_map_rgb(208,198,14));
		al_draw_filled_circle(pos.x + 23, pos.y + 3, 1, al_map_rgb(208,198,14));
		al_draw_filled_circle(pos.x + 24, pos.y + 4, 2, al_map_rgb(208,198,14));
		al_draw_filled_circle(pos.x + 24, pos.y + 2, 1, al_map_rgb(208,198,14));
		al_draw_filled_circle(pos.x + 25, pos.y + 4, 1, al_map_rgb(208,198,14));
		al_draw_filled_circle(pos.x + 26, pos.y + 4, 1, al_map_rgb(208,198,14));

		
		////eyebrow
		al_draw_line(pos.x + 6, pos.y + 11, pos.x + 12, pos.y + 8, al_map_rgb(59,50,17),1);
					

		//hand
		al_draw_filled_circle(pos.x + 5, pos.y + 28, 3, al_map_rgb(208,198,14));
		al_draw_filled_circle(pos.x + 6, pos.y + 25, 1, al_map_rgb(208,198,14)); //thumb
		

		////mouth
		al_draw_filled_triangle(pos.x + 9, pos.y + 24, pos.x + 14, pos.y + 22, pos.x + 17, pos.y + 24, al_map_rgb(59,50,17));

}
void canvas::drawDigDugRight(ALLEGRO_DISPLAY *display,const xy& pos)
{
	//DRAW CHARACTER
		//al_draw_filled_rectangle(pos.x, pos.y, pos.x + 40, pos.y + 40, al_map_rgb(0,0,0));  //background

		//legs
		al_draw_filled_rectangle(pos.x+7, pos.y + 30, pos.x + 30, pos.y + 38,al_map_rgb(104,67,58));

		//body
		al_draw_filled_rounded_rectangle(pos.x + 3, pos.y + 23, pos.x + 35, pos.y + 36, 5, 5, al_map_rgb(178,21,68)); // body
		al_draw_filled_circle(pos.x + 9, pos.y + 25, 6, al_map_rgb(178,21,68)); // neck area circle 1
		al_draw_filled_circle(pos.x + 9, pos.y + 26, 6, al_map_rgb(178,21,68)); // neck area circle 2

		//head
		al_draw_filled_ellipse(pos.x + 20, pos.y + 15, 15, 12, al_map_rgb(209,183,155)); // face - flesh tone

		//eye
		al_draw_filled_circle(pos.x + 30, pos.y + 15, 5, al_map_rgb(208,208,208));
		al_draw_filled_circle(pos.x + 33, pos.y + 15, 1, al_map_rgb(59,50,17));
	
		//hat splines
		float pointsBlueRight1[] = {pos.x + 33, pos.y + 10, pos.x + 30, pos.y + 2, pos.x + 10, pos.y + 2, pos.x + 7, pos.y + 11}; //blue spline
		al_draw_spline(pointsBlueRight1, al_map_rgb(80,169,164), 3); 
		float pointsBlueRight2[] = {pos.x + 31, pos.y + 10, pos.x + 28, pos.y + 4, pos.x + 12, pos.y + 4, pos.x + 7, pos.y + 13}; //blue spline
		al_draw_spline(pointsBlueRight2, al_map_rgb(80,169,164), 3); 
		float pointsBlueRight3[] = {pos.x + 29, pos.y + 10, pos.x + 26, pos.y + 6, pos.x + 14, pos.y + 6, pos.x + 5, pos.y + 14}; //blue spline
		al_draw_spline(pointsBlueRight3, al_map_rgb(80,169,164), 3); 
		float pointsBlueRight4[] = {pos.x + 29, pos.y + 10, pos.x + 24, pos.y + 8, pos.x + 16, pos.y + 8, pos.x + 5, pos.y + 16}; //blue spline
		al_draw_spline(pointsBlueRight4, al_map_rgb(80,169,164), 3); 
		float pointsBlueRight5[] = {pos.x + 34, pos.y + 10, pos.x + 22, pos.y + 11, pos.x + 14, pos.y + 11, pos.x + 5, pos.y + 18}; //yellow spline
		al_draw_spline(pointsBlueRight5, al_map_rgb(80,169,164), 2);
		float pointsYellowRight[] = {pos.x + 34, pos.y + 10, pos.x + 24, pos.y + 12, pos.x + 16, pos.y + 13, pos.x + 5, pos.y + 18}; //yellow spline
		al_draw_spline(pointsYellowRight, al_map_rgb(208,198,14), 2); 

		//hat baubles
		al_draw_filled_circle(pos.x + 19, pos.y + 3, 1, al_map_rgb(208,198,14));
		al_draw_filled_circle(pos.x + 17, pos.y + 3, 1, al_map_rgb(208,198,14));
		al_draw_filled_circle(pos.x + 16, pos.y + 4, 2, al_map_rgb(208,198,14));
		al_draw_filled_circle(pos.x + 16, pos.y + 2, 1, al_map_rgb(208,198,14));
		al_draw_filled_circle(pos.x + 15, pos.y + 4, 1, al_map_rgb(208,198,14));
		al_draw_filled_circle(pos.x + 14, pos.y + 4, 1, al_map_rgb(208,198,14));

		
		////eyebrow
		al_draw_line(pos.x + 34, pos.y + 11, pos.x + 28, pos.y + 8, al_map_rgb(59,50,17),1);
		
					

		//hand
		al_draw_filled_circle(pos.x + 35, pos.y + 28, 3, al_map_rgb(208,198,14));
		al_draw_filled_circle(pos.x + 34, pos.y + 25, 1, al_map_rgb(208,198,14)); //thumb
		

		////mouth
		al_draw_filled_triangle(pos.x + 31, pos.y + 24, pos.x + 26, pos.y + 22, pos.x + 23, pos.y + 24, al_map_rgb(59,50,17));

}
void canvas::drawDigDugResting(ALLEGRO_DISPLAY *display,const xy& pos)
{
	//DRAW CHARACTER
	al_draw_filled_rectangle(pos.x, pos.y, pos.x + 40, pos.y + 40, al_map_rgb(0,0,0));  //background

	al_draw_filled_rectangle(pos.x+5, pos.y + 30, pos.x + 35, pos.y + 38,al_map_rgb(104,67,58)); // legs

	//basic ellipses
	al_draw_filled_ellipse(pos.x + 20, pos.y + 28, 18, 10, al_map_rgb(178,21,68)); // body
	al_draw_filled_ellipse(pos.x + 20, pos.y + 14, 15, 12, al_map_rgb(80,169,164)); // hat - is base for whole head
	al_draw_filled_ellipse(pos.x + 20, pos.y + 18, 15, 10, al_map_rgb(209,183,155)); // face

		

	//hat baubles
	al_draw_filled_circle(pos.x + 19, pos.y + 3, 1, al_map_rgb(208,198,14));
	al_draw_filled_circle(pos.x + 20, pos.y + 3, 2, al_map_rgb(208,198,14));
	al_draw_filled_circle(pos.x + 21, pos.y + 3, 1, al_map_rgb(208,198,14));
	al_draw_filled_circle(pos.x + 17, pos.y + 3, 1, al_map_rgb(208,198,14));
	al_draw_filled_circle(pos.x + 23, pos.y + 3, 1, al_map_rgb(208,198,14));

	//hat splines
	float pointsBlueStill[] = {pos.x + 5, pos.y + 15, pos.x + 10, pos.y + 7, pos.x + 30, pos.y + 7, pos.x + 35, pos.y + 15}; //blue spline
	al_draw_spline(pointsBlueStill, al_map_rgb(80,169,164), 2); 
	float pointsYellowStill[] = {pos.x + 5, pos.y + 16, pos.x + 10, pos.y + 8, pos.x + 30, pos.y + 8, pos.x + 35, pos.y + 16}; //yellow spline
	al_draw_spline(pointsYellowStill, al_map_rgb(208,198,14), 2); 

		
		
	//eyes
	al_draw_filled_circle(pos.x + 15, pos.y + 16, 5, al_map_rgb(208,208,208));
	al_draw_filled_circle(pos.x + 25, pos.y + 16, 5, al_map_rgb(208,208,208));
	al_draw_filled_circle(pos.x + 16, pos.y + 16, 1, al_map_rgb(59,50,17));
	al_draw_filled_circle(pos.x + 24, pos.y + 16, 1, al_map_rgb(59,50,17));

	//eyebrows
	al_draw_line(pos.x + 19, pos.y + 10, pos.x + 12, pos.y + 8, al_map_rgb(59,50,17),1);
	al_draw_line(pos.x + 21, pos.y + 10, pos.x + 28, pos.y + 8, al_map_rgb(59,50,17),1);
		
	//hands
	al_draw_filled_circle(pos.x + 7, pos.y + 34, 3, al_map_rgb(208,198,14)); // hands
	al_draw_filled_circle(pos.x + 33, pos.y + 34, 3, al_map_rgb(208,198,14));
	al_draw_filled_circle(pos.x + 9, pos.y + 31, 1, al_map_rgb(208,198,14)); //thumbs
	al_draw_filled_circle(pos.x + 31, pos.y + 31, 1, al_map_rgb(208,198,14));

	//mouth
	al_draw_line(pos.x + 17, pos.y + 25, pos.x + 23, pos.y + 25, al_map_rgb(59,50,17),1);

	//buttons
	al_draw_filled_circle(pos.x + 20, pos.y + 30, 1, al_map_rgb(59,50,17));
	al_draw_filled_circle(pos.x + 20, pos.y + 33, 1, al_map_rgb(59,50,17));
	al_draw_filled_circle(pos.x + 20, pos.y + 36, 1, al_map_rgb(59,50,17));

}

/////////////////////////////////////////////
/////////////////Clyde frog/////////////////

void canvas::drawClydeUp(ALLEGRO_DISPLAY *display,xy pos)
{
	//background
	//al_draw_filled_rectangle(pos.x, pos.y, pos.x + 40, pos.y + 40, al_map_rgb(0,0,0));
	//body
	al_draw_filled_ellipse(pos.x + 20, pos.y + 21, 6, 9, al_map_rgb(38,92,54));
		
	//legs
	float leftLegU[] = {pos.x + 17, pos.y + 23, pos.x + 15, pos.y + 42, pos.x + 15, pos.y + 42, pos.x + 20, pos.y + 23};
	al_draw_spline(leftLegU, al_map_rgb(38,92,54), 2);
	float rightLegU[] = {pos.x + 23, pos.y + 23, pos.x + 25, pos.y + 42, pos.x + 25, pos.y + 42, pos.x + 20, pos.y + 23};
	al_draw_spline(rightLegU, al_map_rgb(38,92,54), 2);

	//arms
	float leftArmU[] = {pos.x + 14, pos.y + 15, pos.x + 9, pos.y + 35, pos.x + 9, pos.y + 35, pos.x + 17, pos.y + 15};
	al_draw_spline(leftArmU, al_map_rgb(38,92,54), 2);
	float rightArmU[] = {pos.x + 26, pos.y + 15, pos.x + 31, pos.y + 35, pos.x + 31, pos.y + 35, pos.x + 23, pos.y + 15};
	al_draw_spline(rightArmU, al_map_rgb(38,92,54), 2);

	//head
	al_draw_filled_ellipse(pos.x + 20, pos.y + 11, 17, 9, al_map_rgb(38,92,54));
	al_draw_ellipse(pos.x + 20, pos.y + 11, 17, 9, al_map_rgb(10,59,25),1);

}
void canvas::drawClydeLeft(ALLEGRO_DISPLAY *display,xy pos)
{
	//background
	//al_draw_filled_rectangle(pos.x, pos.y, pos.x + 40, pos.y + 40, al_map_rgb(0,0,0));

	//body
	al_draw_filled_ellipse(pos.x + 20, pos.y + 21, 6, 9, al_map_rgb(38,92,54));
		
	
	//legs
	float leftLegL[] = {pos.x + 17, pos.y + 23, pos.x + 15, pos.y + 42, pos.x + 15, pos.y + 42, pos.x + 20, pos.y + 23};
	al_draw_spline(leftLegL, al_map_rgb(38,92,54), 2);
	float rightLegL[] = {pos.x + 23, pos.y + 23, pos.x + 25, pos.y + 42, pos.x + 25, pos.y + 42, pos.x + 20, pos.y + 23};
	al_draw_spline(rightLegL, al_map_rgb(38,92,54), 2);

	//arms
	float leftArmL[] = {pos.x + 14, pos.y + 15, pos.x + 9, pos.y + 35, pos.x + 9, pos.y + 35, pos.x + 17, pos.y + 15};
	al_draw_spline(leftArmL, al_map_rgb(38,92,54), 2);

	float rightArmL[] = {pos.x + 26, pos.y + 15, pos.x + 31, pos.y + 35, pos.x + 31, pos.y + 35, pos.x + 23, pos.y + 15};
	al_draw_spline(rightArmL, al_map_rgb(38,92,54), 2);

	//head
	al_draw_filled_ellipse(pos.x + 17, pos.y + 11, 13, 9,  al_map_rgb(38,92,54));
	al_draw_ellipse(pos.x + 17, pos.y + 11, 13, 9,  al_map_rgb(10,59,25),1);

	//eyes
	al_draw_filled_circle(pos.x + 9, pos.y + 8, 3, al_map_rgb(183,183,187));
	al_draw_filled_circle(pos.x + 8, pos.y + 8, 1, al_map_rgb(27,28,26)); // pupils

	//mouth
	al_draw_filled_triangle(pos.x + 3, pos.y + 12, pos.x + 15, pos.y + 14, pos.x + 3, pos.y + 18, al_map_rgb(0,0,0));


	//chest lines
	al_draw_line(pos.x + 20, pos.y + 20, pos.x + 20, pos.y + 29, al_map_rgb(10,59,25),2); //vertical
	al_draw_line(pos.x + 17, pos.y + 23, pos.x + 23, pos.y + 23, al_map_rgb(10,59,25),1); //horizontal
	al_draw_line(pos.x + 17, pos.y + 26, pos.x + 23, pos.y + 26, al_map_rgb(10,59,25),1);

}
void canvas::drawClydeRight(ALLEGRO_DISPLAY *display,xy pos)
{
	//background
	//al_draw_filled_rectangle(pos.x, pos.y, pos.x + 40, pos.y + 40, al_map_rgb(0,0,0));

	//body
	al_draw_filled_ellipse(pos.x + 20, pos.y + 21, 6, 9, al_map_rgb(38,92,54));
		
	
	//legs
	float leftLegR[] = {pos.x + 17, pos.y + 23, pos.x + 15, pos.y + 42, pos.x + 15, pos.y + 42, pos.x + 20, pos.y + 23};
	al_draw_spline(leftLegR, al_map_rgb(38,92,54), 2);
	float rightLegR[] = {pos.x + 23, pos.y + 23, pos.x + 25, pos.y + 42, pos.x + 25, pos.y + 42, pos.x + 20, pos.y + 23};
	al_draw_spline(rightLegR, al_map_rgb(38,92,54), 2);

	//arms
	float leftArmR[] = {pos.x + 14, pos.y + 15, pos.x + 9, pos.y + 35, pos.x + 9, pos.y + 35, pos.x + 17, pos.y + 15};
	al_draw_spline(leftArmR, al_map_rgb(38,92,54), 2);

	float rightArmR[] = {pos.x + 26, pos.y + 15, pos.x + 31, pos.y + 35, pos.x + 31, pos.y + 35, pos.x + 23, pos.y + 15};
	al_draw_spline(rightArmR, al_map_rgb(38,92,54), 2);


	//head
	al_draw_filled_ellipse(pos.x + 23, pos.y + 11, 13, 9,  al_map_rgb(38,92,54));
	al_draw_ellipse(pos.x + 23, pos.y + 11, 13, 9,  al_map_rgb(10,59,25),1);

	//eyes
	al_draw_filled_circle(pos.x + 31, pos.y + 8, 3, al_map_rgb(183,183,187));
	al_draw_filled_circle(pos.x + 32, pos.y + 8, 1, al_map_rgb(27,28,26)); // pupils

	//mouth
	al_draw_filled_triangle(pos.x + 37, pos.y + 12, pos.x + 25, pos.y + 14, pos.x + 37, pos.y + 18, al_map_rgb(0,0,0));


	//chest lines
	al_draw_line(pos.x + 20, pos.y + 20, pos.x + 20, pos.y + 29, al_map_rgb(10,59,25),2); //vertical
	al_draw_line(pos.x + 17, pos.y + 23, pos.x + 23, pos.y + 23, al_map_rgb(10,59,25),1); //horizontal
	al_draw_line(pos.x + 17, pos.y + 26, pos.x + 23, pos.y + 26, al_map_rgb(10,59,25),1);
}

void canvas::drawClydeDown1(ALLEGRO_DISPLAY *display,xy pos)
{
//background
		//al_draw_filled_rectangle(pos.x, pos.y, pos.x + 40, pos.y + 40, al_map_rgb(0,0,0));

		//body
		al_draw_filled_ellipse(pos.x + 20, pos.y + 21, 6, 9, al_map_rgb(38,92,54));
		
	
		//legs
		float leftLeg[] = {pos.x + 17, pos.y + 23, pos.x + 15, pos.y + 42, pos.x + 15, pos.y + 42, pos.x + 20, pos.y + 23};
		al_draw_spline(leftLeg, al_map_rgb(38,92,54), 2);
		float rightLeg[] = {pos.x + 23, pos.y + 23, pos.x + 25, pos.y + 42, pos.x + 25, pos.y + 42, pos.x + 20, pos.y + 23};
		al_draw_spline(rightLeg, al_map_rgb(38,92,54), 2);

		//arms
		float leftArm[] = {pos.x + 14, pos.y + 15, pos.x + 9, pos.y + 35, pos.x + 9, pos.y + 35, pos.x + 17, pos.y + 15};
		al_draw_spline(leftArm, al_map_rgb(38,92,54), 2);

		float rightArm[] = {pos.x + 26, pos.y + 15, pos.x + 31, pos.y + 35, pos.x + 31, pos.y + 35, pos.x + 23, pos.y + 15};
		al_draw_spline(rightArm, al_map_rgb(38,92,54), 2);

		//head
		al_draw_filled_ellipse(pos.x + 20, pos.y + 11, 17, 9, al_map_rgb(38,92,54));
		al_draw_ellipse(pos.x + 20, pos.y + 11, 17, 9, al_map_rgb(10,59,25),1);
		al_draw_filled_ellipse(pos.x + 20, pos.y + 11, 13, 6, al_map_rgb(183,183,187)); //white mouth area
		al_draw_filled_ellipse(pos.x + 20, pos.y + 11, 8, 4, al_map_rgb(188,0,102));	//pink mouth area
		al_draw_filled_ellipse(pos.x + 20, pos.y + 9, 15, 4, al_map_rgb(38,92,54));	//green top head area

		//eyes
		al_draw_filled_ellipse(pos.x + 14, pos.y + 7, 5, 2, al_map_rgb(183,183,187));
		al_draw_filled_ellipse(pos.x + 26, pos.y + 7, 5, 2, al_map_rgb(183,183,187));
		al_draw_filled_circle(pos.x + 15, pos.y + 7, 1, al_map_rgb(27,28,26)); // pupils
		al_draw_filled_circle(pos.x + 25, pos.y + 7, 1, al_map_rgb(27,28,26));

		//chest lines
		al_draw_line(pos.x + 20, pos.y + 20, pos.x + 20, pos.y + 29, al_map_rgb(10,59,25),2); //vertical
		al_draw_line(pos.x + 17, pos.y + 23, pos.x + 23, pos.y + 23, al_map_rgb(10,59,25),1); //horizontal
		al_draw_line(pos.x + 17, pos.y + 26, pos.x + 23, pos.y + 26, al_map_rgb(10,59,25),1);

		//////////////////////////////////////////
}
void canvas::drawClydeDown2(ALLEGRO_DISPLAY *display,xy pos)
{
	al_draw_filled_ellipse(pos.x + 20, pos.y + 21, 6, 9, al_map_rgb(38,92,54));

	//legs
	float leftLeg1[] = {pos.x + 17, pos.y + 23, pos.x + 15, pos.y + 42, pos.x + 15, pos.y + 42, pos.x + 20, pos.y + 23};
	al_draw_spline(leftLeg1, al_map_rgb(38,92,54), 2);
	float rightLeg1[] = {pos.x + 23, pos.y + 23, pos.x + 25, pos.y + 42, pos.x + 25, pos.y + 42, pos.x + 20, pos.y + 23};
	al_draw_spline(rightLeg1, al_map_rgb(38,92,54), 2);

	//arms
	float leftArm1[] = {pos.x + 14, pos.y + 15, pos.x + 9, pos.y + 35, pos.x + 9, pos.y + 35, pos.x + 17, pos.y + 15};
	al_draw_spline(leftArm1, al_map_rgb(38,92,54), 2);

	float rightArm1[] = {pos.x + 26, pos.y + 15, pos.x + 31, pos.y + 35, pos.x + 31, pos.y + 35, pos.x + 23, pos.y + 15};
	al_draw_spline(rightArm1, al_map_rgb(38,92,54), 2);

	//chest lines
	al_draw_line(pos.x + 20, pos.y + 20, pos.x + 20, pos.y + 29, al_map_rgb(10,59,25),2); //vertical
	al_draw_line(pos.x + 17, pos.y + 23, pos.x + 23, pos.y + 23, al_map_rgb(10,59,25),1); //horizontal
	al_draw_line(pos.x + 17, pos.y + 26, pos.x + 23, pos.y + 26, al_map_rgb(10,59,25),1);

	//head
	al_draw_filled_ellipse(pos.x + 20, pos.y + 11, 17, 9, al_map_rgb(38,92,54));
	al_draw_ellipse(pos.x + 20, pos.y + 11, 17, 9, al_map_rgb(10,59,25),1);
	al_draw_filled_ellipse(pos.x + 20, pos.y + 11, 13, 6, al_map_rgb(183,183,187)); //white mouth area
	al_draw_filled_ellipse(pos.x + 20, pos.y + 11, 8, 4, al_map_rgb(188,0,102));	//pink mouth area
	al_draw_filled_ellipse(pos.x + 20, pos.y + 13, 4, 4, al_map_rgb(171,0,49));	//tongue
	al_draw_line(pos.x + 20, pos.y + 10, pos.x + 20, pos.y + 16, al_map_rgb(122,1,31),2); //tongue line
	al_draw_filled_ellipse(pos.x + 20, pos.y + 9, 15, 4, al_map_rgb(38,92,54));	//green top head area

	//eyes
	al_draw_filled_ellipse(pos.x + 14, pos.y + 7, 5, 2, al_map_rgb(183,183,187));
	al_draw_filled_ellipse(pos.x + 26, pos.y + 7, 5, 2, al_map_rgb(183,183,187));
	al_draw_filled_circle(pos.x + 15, pos.y + 7, 1, al_map_rgb(27,28,26)); // pupils
	al_draw_filled_circle(pos.x + 25, pos.y + 7, 1, al_map_rgb(27,28,26));

}
void canvas::drawClydeDown3(ALLEGRO_DISPLAY *display,xy pos)
{
	al_draw_filled_ellipse(pos.x + 20, pos.y + 21, 6, 9, al_map_rgb(38,92,54));

	//legs
	float leftLeg2[] = {pos.x + 17, pos.y + 23, pos.x + 15, pos.y + 42, pos.x + 15, pos.y + 42, pos.x + 20, pos.y + 23};
	al_draw_spline(leftLeg2, al_map_rgb(38,92,54), 2);
	float rightLeg2[] = {pos.x + 23, pos.y + 23, pos.x + 25, pos.y + 42, pos.x + 25, pos.y + 42, pos.x + 20, pos.y + 23};
	al_draw_spline(rightLeg2, al_map_rgb(38,92,54), 2);

	//arms
	float leftArm2[] = {pos.x + 14, pos.y + 15, pos.x + 9, pos.y + 35, pos.x + 9, pos.y + 35, pos.x + 17, pos.y + 15};
	al_draw_spline(leftArm2, al_map_rgb(38,92,54), 2);

	float rightArm2[] = {pos.x + 26, pos.y + 15, pos.x + 31, pos.y + 35, pos.x + 31, pos.y + 35, pos.x + 23, pos.y + 15};
	al_draw_spline(rightArm2, al_map_rgb(38,92,54), 2);

	//chest lines
	al_draw_line(pos.x + 20, pos.y + 20, pos.x + 20, pos.y + 29, al_map_rgb(10,59,25),2); //vertical
	al_draw_line(pos.x + 17, pos.y + 23, pos.x + 23, pos.y + 23, al_map_rgb(10,59,25),1); //horizontal
	al_draw_line(pos.x + 17, pos.y + 26, pos.x + 23, pos.y + 26, al_map_rgb(10,59,25),1);


	//head
	al_draw_filled_ellipse(pos.x + 20, pos.y + 11, 17, 9, al_map_rgb(38,92,54));
	al_draw_ellipse(pos.x + 20, pos.y + 11, 17, 9, al_map_rgb(10,59,25),1);
	al_draw_filled_ellipse(pos.x + 20, pos.y + 11, 13, 6, al_map_rgb(183,183,187)); //white mouth area
	al_draw_filled_ellipse(pos.x + 20, pos.y + 11, 8, 4, al_map_rgb(188,0,102));	//pink mouth area
	al_draw_filled_ellipse(pos.x + 20, pos.y + 13, 4, 7, al_map_rgb(171,0,49));	//tongue
	al_draw_line(pos.x + 20, pos.y + 10, pos.x + 20, pos.y + 17, al_map_rgb(122,1,31),2); //tongue line
	al_draw_filled_ellipse(pos.x + 20, pos.y + 9, 15, 4, al_map_rgb(38,92,54));	//green top head area

	//eyes
	al_draw_filled_ellipse(pos.x + 14, pos.y + 7, 5, 2, al_map_rgb(183,183,187));
	al_draw_filled_ellipse(pos.x + 26, pos.y + 7, 5, 2, al_map_rgb(183,183,187));
	al_draw_filled_circle(pos.x + 15, pos.y + 7, 1, al_map_rgb(27,28,26)); // pupils
	al_draw_filled_circle(pos.x + 25, pos.y + 7, 1, al_map_rgb(27,28,26));


}
void canvas::drawClydeDown4(ALLEGRO_DISPLAY *display,xy pos)
{

	//body
	al_draw_filled_ellipse(pos.x + 20, pos.y + 21, 6, 9, al_map_rgb(38,92,54));

	//legs
	float leftLeg3[] = {pos.x + 17, pos.y + 23, pos.x + 15, pos.y + 42, pos.x + 15, pos.y + 42, pos.x + 20, pos.y + 23};
	al_draw_spline(leftLeg3, al_map_rgb(38,92,54), 2);
	float rightLeg3[] = {pos.x + 23, pos.y + 23, pos.x + 25, pos.y + 42, pos.x + 25, pos.y + 42, pos.x + 20, pos.y + 23};
	al_draw_spline(rightLeg3, al_map_rgb(38,92,54), 2);

	//arms
	float leftArm3[] = {pos.x + 14, pos.y + 15, pos.x + 9, pos.y + 35, pos.x + 9, pos.y + 35, pos.x + 17, pos.y + 15};
	al_draw_spline(leftArm3, al_map_rgb(38,92,54), 2);

	float rightArm3[] = {pos.x + 26, pos.y + 15, pos.x + 31, pos.y + 35, pos.x + 31, pos.y + 35, pos.x + 23, pos.y + 15};
	al_draw_spline(rightArm3, al_map_rgb(38,92,54), 2);

	//chest lines
	al_draw_line(pos.x + 20, pos.y + 20, pos.x + 20, pos.y + 29, al_map_rgb(10,59,25),2); //vertical
	al_draw_line(pos.x + 17, pos.y + 23, pos.x + 23, pos.y + 23, al_map_rgb(10,59,25),1); //horizontal
	al_draw_line(pos.x + 17, pos.y + 26, pos.x + 23, pos.y + 26, al_map_rgb(10,59,25),1);

	//head
	al_draw_filled_ellipse(pos.x + 20, pos.y + 11, 17, 9, al_map_rgb(38,92,54));
	al_draw_ellipse(pos.x + 20, pos.y + 11, 17, 9, al_map_rgb(10,59,25),1);
	al_draw_filled_ellipse(pos.x + 20, pos.y + 11, 13, 6, al_map_rgb(183,183,187)); //white mouth area
	al_draw_filled_ellipse(pos.x + 20, pos.y + 11, 8, 4, al_map_rgb(188,0,102));	//pink mouth area
	al_draw_filled_ellipse(pos.x + 20, pos.y + 15, 4, 9, al_map_rgb(171,0,49));	//tongue
	al_draw_line(pos.x + 20, pos.y + 10, pos.x + 20, pos.y + 21, al_map_rgb(122,1,31),2); //tongue line
	al_draw_filled_ellipse(pos.x + 20, pos.y + 9, 15, 4, al_map_rgb(38,92,54));	//green top head area

	//eyes
	al_draw_filled_ellipse(pos.x + 14, pos.y + 7, 5, 2, al_map_rgb(183,183,187));
	al_draw_filled_ellipse(pos.x + 26, pos.y + 7, 5, 2, al_map_rgb(183,183,187));
	al_draw_filled_circle(pos.x + 15, pos.y + 7, 1, al_map_rgb(27,28,26)); // pupils
	al_draw_filled_circle(pos.x + 25, pos.y + 7, 1, al_map_rgb(27,28,26));

}
void canvas::drawClydeDown5(ALLEGRO_DISPLAY *display,xy pos)
{
	//body
	al_draw_filled_ellipse(pos.x + 20, pos.y + 21, 6, 9, al_map_rgb(38,92,54));

	//legs
	float leftLeg4[] = {pos.x + 17, pos.y + 23, pos.x + 15, pos.y + 42, pos.x + 15, pos.y + 42, pos.x + 20, pos.y + 23};
	al_draw_spline(leftLeg4, al_map_rgb(38,92,54), 2);
	float rightLeg4[] = {pos.x + 23, pos.y + 23, pos.x + 25, pos.y + 42, pos.x + 25, pos.y + 42, pos.x + 20, pos.y + 23};
	al_draw_spline(rightLeg4, al_map_rgb(38,92,54), 2);

	//arms
	float leftArm4[] = {pos.x + 14, pos.y + 15, pos.x + 9, pos.y + 35, pos.x + 9, pos.y + 35, pos.x + 17, pos.y + 15};
	al_draw_spline(leftArm4, al_map_rgb(38,92,54), 2);

	float rightArm4[] = {pos.x + 26, pos.y + 15, pos.x + 31, pos.y + 35, pos.x + 31, pos.y + 35, pos.x + 23, pos.y + 15};
	al_draw_spline(rightArm4, al_map_rgb(38,92,54), 2);

	//chest lines
	al_draw_line(pos.x + 20, pos.y + 20, pos.x + 20, pos.y + 29, al_map_rgb(10,59,25),2); //vertical
	al_draw_line(pos.x + 17, pos.y + 23, pos.x + 23, pos.y + 23, al_map_rgb(10,59,25),1); //horizontal
	al_draw_line(pos.x + 17, pos.y + 26, pos.x + 23, pos.y + 26, al_map_rgb(10,59,25),1);
	
	//head
	al_draw_filled_ellipse(pos.x + 20, pos.y + 11, 17, 9, al_map_rgb(38,92,54));
	al_draw_ellipse(pos.x + 20, pos.y + 11, 17, 9, al_map_rgb(10,59,25),1);
	al_draw_filled_ellipse(pos.x + 20, pos.y + 11, 13, 6, al_map_rgb(183,183,187)); //white mouth area
	al_draw_filled_ellipse(pos.x + 20, pos.y + 11, 8, 4, al_map_rgb(188,0,102));	//pink mouth area
	al_draw_filled_ellipse(pos.x + 20, pos.y + 18, 4, 9, al_map_rgb(171,0,49));	//tongue
	al_draw_line(pos.x + 20, pos.y + 10, pos.x + 20, pos.y + 24, al_map_rgb(122,1,31),2); //tongue line
	al_draw_filled_ellipse(pos.x + 20, pos.y + 9, 15, 4, al_map_rgb(38,92,54));	//green top head area

	//eyes
	al_draw_filled_ellipse(pos.x + 14, pos.y + 7, 5, 2, al_map_rgb(183,183,187));
	al_draw_filled_ellipse(pos.x + 26, pos.y + 7, 5, 2, al_map_rgb(183,183,187));
	al_draw_filled_circle(pos.x + 15, pos.y + 7, 1, al_map_rgb(27,28,26)); // pupils
	al_draw_filled_circle(pos.x + 25, pos.y + 7, 1, al_map_rgb(27,28,26));

}


/////////////////////////////////////////////
//////////////Clyde frog swelling///////////

void canvas::drawClydeSwelling1(ALLEGRO_DISPLAY *display,xy pos)
{
	//background
	//al_draw_filled_rectangle(pos.x, pos.y, pos.x + 40, pos.y + 40, al_map_rgb(0,0,0));

	//body
	al_draw_filled_ellipse(pos.x + 20, pos.y + 21, 6, 9, al_map_rgb(38,92,54));
	

	//legs
	float leftLeg[] = {pos.x + 17, pos.y + 23, pos.x + 15, pos.y + 42, pos.x + 15, pos.y + 42, pos.x + 20, pos.y + 23};
	al_draw_spline(leftLeg, al_map_rgb(38,92,54), 2);
	float rightLeg[] = {pos.x + 23, pos.y + 23, pos.x + 25, pos.y + 42, pos.x + 25, pos.y + 42, pos.x + 20, pos.y + 23};
	al_draw_spline(rightLeg, al_map_rgb(38,92,54), 2);

	//arms
	float leftArm[] = {pos.x + 14, pos.y + 15, pos.x + 9, pos.y + 35, pos.x + 9, pos.y + 35, pos.x + 17, pos.y + 15};
	al_draw_spline(leftArm, al_map_rgb(38,92,54), 2);

	float rightArm[] = {pos.x + 26, pos.y + 15, pos.x + 31, pos.y + 35, pos.x + 31, pos.y + 35, pos.x + 23, pos.y + 15};
	al_draw_spline(rightArm, al_map_rgb(38,92,54), 2);

	//head
	al_draw_filled_ellipse(pos.x + 20, pos.y + 11, 17, 9, al_map_rgb(38,92,54));
	al_draw_ellipse(pos.x + 20, pos.y + 11, 17, 9, al_map_rgb(10,59,25),1);
	al_draw_filled_ellipse(pos.x + 20, pos.y + 11, 13, 6, al_map_rgb(183,183,187)); //white mouth area
	al_draw_filled_ellipse(pos.x + 20, pos.y + 11, 8, 4, al_map_rgb(188,0,102));	//pink mouth area
	al_draw_filled_ellipse(pos.x + 20, pos.y + 9, 15, 4, al_map_rgb(38,92,54));	//green top head area

	//eyes
	al_draw_filled_ellipse(pos.x + 14, pos.y + 7, 5, 2, al_map_rgb(183,183,187));
	al_draw_filled_ellipse(pos.x + 26, pos.y + 7, 5, 2, al_map_rgb(183,183,187));
	al_draw_filled_circle(pos.x + 15, pos.y + 7, 1, al_map_rgb(27,28,26)); // pupils
	al_draw_filled_circle(pos.x + 25, pos.y + 7, 1, al_map_rgb(27,28,26));

	//chest lines
	al_draw_line(pos.x + 20, pos.y + 20, pos.x + 20, pos.y + 29, al_map_rgb(10,59,25),2); //vertical
	al_draw_line(pos.x + 17, pos.y + 23, pos.x + 23, pos.y + 23, al_map_rgb(10,59,25),1); //horizontal
	al_draw_line(pos.x + 17, pos.y + 26, pos.x + 23, pos.y + 26, al_map_rgb(10,59,25),1);

}
void canvas::drawClydeSwelling2(ALLEGRO_DISPLAY *display,xy pos)
{
	//background
	//al_draw_filled_rectangle(pos.x, pos.y, pos.x + 40, pos.y + 40, al_map_rgb(0,0,0));

	//body
	al_draw_filled_ellipse(pos.x + 20, pos.y + 21, 6, 9, al_map_rgb(38,92,54));
	

	//legs
	float leftLeg1[] = {pos.x + 17, pos.y + 23, pos.x + 15, pos.y + 42, pos.x + 15, pos.y + 42, pos.x + 20, pos.y + 23};
	al_draw_spline(leftLeg1, al_map_rgb(38,92,54), 2);
	float rightLeg1[] = {pos.x + 23, pos.y + 23, pos.x + 25, pos.y + 42, pos.x + 25, pos.y + 42, pos.x + 20, pos.y + 23};
	al_draw_spline(rightLeg1, al_map_rgb(38,92,54), 2);

	//arms
	float leftArm1[] = {pos.x + 14, pos.y + 15, pos.x + 9, pos.y + 35, pos.x + 9, pos.y + 35, pos.x + 17, pos.y + 15};
	al_draw_spline(leftArm1, al_map_rgb(38,92,54), 2);

	float rightArm1[] = {pos.x + 26, pos.y + 15, pos.x + 31, pos.y + 35, pos.x + 31, pos.y + 35, pos.x + 23, pos.y + 15};
	al_draw_spline(rightArm1, al_map_rgb(38,92,54), 2);

	//head
	al_draw_filled_ellipse(pos.x + 20, pos.y + 11, 19, 9, al_map_rgb(38,92,54));
	al_draw_ellipse(pos.x + 20, pos.y + 11, 19, 9, al_map_rgb(10,59,25),1);
	al_draw_filled_ellipse(pos.x + 20, pos.y + 11, 13, 6, al_map_rgb(183,183,187)); //white mouth area
	al_draw_filled_ellipse(pos.x + 20, pos.y + 11, 8, 4, al_map_rgb(188,0,102));	//pink mouth area
	al_draw_filled_ellipse(pos.x + 20, pos.y + 9, 15, 4, al_map_rgb(38,92,54));	//green top head area

	//eyes
	al_draw_filled_ellipse(pos.x + 14, pos.y + 7, 5, 2, al_map_rgb(183,183,187));
	al_draw_filled_ellipse(pos.x + 26, pos.y + 7, 5, 2, al_map_rgb(183,183,187));
	al_draw_filled_circle(pos.x + 15, pos.y + 7, 1, al_map_rgb(27,28,26)); // pupils
	al_draw_filled_circle(pos.x + 25, pos.y + 7, 1, al_map_rgb(27,28,26));

	//chest lines
	al_draw_line(pos.x + 20, pos.y + 20, pos.x + 20, pos.y + 29, al_map_rgb(10,59,25),2); //vertical
	al_draw_line(pos.x + 17, pos.y + 23, pos.x + 23, pos.y + 23, al_map_rgb(10,59,25),1); //horizontal
	al_draw_line(pos.x + 17, pos.y + 26, pos.x + 23, pos.y + 26, al_map_rgb(10,59,25),1);

}
void canvas::drawClydeSwelling3(ALLEGRO_DISPLAY *display,xy pos)
{
	//background
	//al_draw_filled_rectangle(pos.x, pos.y, pos.x + 40, pos.y + 40, al_map_rgb(0,0,0));

	//body
	al_draw_filled_ellipse(pos.x + 20, pos.y + 21, 6, 9, al_map_rgb(38,92,54));
	

	//legs
	float leftLeg2[] = {pos.x + 17, pos.y + 23, pos.x + 15, pos.y + 42, pos.x + 15, pos.y + 42, pos.x + 20, pos.y + 23};
	al_draw_spline(leftLeg2, al_map_rgb(38,92,54), 2);
	float rightLeg2[] = {pos.x + 23, pos.y + 23, pos.x + 25, pos.y + 42, pos.x + 25, pos.y + 42, pos.x + 20, pos.y + 23};
	al_draw_spline(rightLeg2, al_map_rgb(38,92,54), 2);

	//arms
	float leftArm2[] = {pos.x + 14, pos.y + 15, pos.x + 9, pos.y + 35, pos.x + 9, pos.y + 35, pos.x + 17, pos.y + 15};
	al_draw_spline(leftArm2, al_map_rgb(38,92,54), 2);

	float rightArm2[] = {pos.x + 26, pos.y + 15, pos.x + 31, pos.y + 35, pos.x + 31, pos.y + 35, pos.x + 23, pos.y + 15};
	al_draw_spline(rightArm2, al_map_rgb(38,92,54), 2);

	//head
	al_draw_filled_ellipse(pos.x + 20, pos.y + 11, 21, 9, al_map_rgb(38,92,54));
	al_draw_ellipse(pos.x + 20, pos.y + 11, 21, 9, al_map_rgb(10,59,25),1);
	al_draw_filled_ellipse(pos.x + 20, pos.y + 11, 13, 6, al_map_rgb(183,183,187)); //white mouth area
	al_draw_filled_ellipse(pos.x + 20, pos.y + 11, 8, 4, al_map_rgb(188,0,102));	//pink mouth area
	al_draw_filled_ellipse(pos.x + 20, pos.y + 9, 15, 4, al_map_rgb(38,92,54));	//green top head area

	//eyes
	al_draw_filled_ellipse(pos.x + 14, pos.y + 7, 5, 2, al_map_rgb(243,196,201));
	al_draw_filled_ellipse(pos.x + 26, pos.y + 7, 5, 2, al_map_rgb(243,196,201));
	al_draw_filled_circle(pos.x + 15, pos.y + 7, 1, al_map_rgb(27,28,26)); // pupils
	al_draw_filled_circle(pos.x + 25, pos.y + 7, 1, al_map_rgb(27,28,26));

	//chest lines
	al_draw_line(pos.x + 20, pos.y + 20, pos.x + 20, pos.y + 29, al_map_rgb(10,59,25),2); //vertical
	al_draw_line(pos.x + 17, pos.y + 23, pos.x + 23, pos.y + 23, al_map_rgb(10,59,25),1); //horizontal
	al_draw_line(pos.x + 17, pos.y + 26, pos.x + 23, pos.y + 26, al_map_rgb(10,59,25),1);

}
void canvas::drawClydeSwelling4(ALLEGRO_DISPLAY *display,xy pos)
{
	//background
	//al_draw_filled_rectangle(pos.x, pos.y, pos.x + 40, pos.y + 40, al_map_rgb(0,0,0));

	//body
	al_draw_filled_ellipse(pos.x + 20, pos.y + 21, 6, 9, al_map_rgb(38,92,54));
	

	//legs
	float leftLeg3[] = {pos.x + 17, pos.y + 23, pos.x + 15, pos.y + 42, pos.x + 15, pos.y + 42, pos.x + 20, pos.y + 23};
	al_draw_spline(leftLeg3, al_map_rgb(38,92,54), 2);
	float rightLeg3[] = {pos.x + 23, pos.y + 23, pos.x + 25, pos.y + 42, pos.x + 25, pos.y + 42, pos.x + 20, pos.y + 23};
	al_draw_spline(rightLeg3, al_map_rgb(38,92,54), 2);

	//arms
	float leftArm3[] = {pos.x + 14, pos.y + 15, pos.x + 9, pos.y + 35, pos.x + 9, pos.y + 35, pos.x + 17, pos.y + 15};
	al_draw_spline(leftArm3, al_map_rgb(38,92,54), 2);

	float rightArm3[] = {pos.x + 26, pos.y + 15, pos.x + 31, pos.y + 35, pos.x + 31, pos.y + 35, pos.x + 23, pos.y + 15};
	al_draw_spline(rightArm3, al_map_rgb(38,92,54), 2);

	//head
	al_draw_filled_ellipse(pos.x + 20, pos.y + 11, 23, 9, al_map_rgb(38,92,54));
	al_draw_ellipse(pos.x + 20, pos.y + 11, 23, 9, al_map_rgb(10,59,25),1);
	al_draw_filled_ellipse(pos.x + 20, pos.y + 11, 13, 6, al_map_rgb(183,183,187)); //white mouth area
	al_draw_filled_ellipse(pos.x + 20, pos.y + 11, 8, 4, al_map_rgb(188,0,102));	//pink mouth area
	al_draw_filled_ellipse(pos.x + 20, pos.y + 9, 15, 4, al_map_rgb(38,92,54));	//green top head area

	//eyes
	al_draw_filled_ellipse(pos.x + 14, pos.y + 7, 5, 2, al_map_rgb(243,133,134));
	al_draw_filled_ellipse(pos.x + 26, pos.y + 7, 5, 2, al_map_rgb(243,133,134));
	al_draw_filled_circle(pos.x + 15, pos.y + 7, 1, al_map_rgb(27,28,26)); // pupils
	al_draw_filled_circle(pos.x + 25, pos.y + 7, 1, al_map_rgb(27,28,26));

	//chest lines
	al_draw_line(pos.x + 20, pos.y + 20, pos.x + 20, pos.y + 29, al_map_rgb(10,59,25),2); //vertical
	al_draw_line(pos.x + 17, pos.y + 23, pos.x + 23, pos.y + 23, al_map_rgb(10,59,25),1); //horizontal
	al_draw_line(pos.x + 17, pos.y + 26, pos.x + 23, pos.y + 26, al_map_rgb(10,59,25),1);

}
void canvas::drawClydeSwelling5(ALLEGRO_DISPLAY *display,xy pos)
{
	//background
	//al_draw_filled_rectangle(pos.x, pos.y, pos.x + 40, pos.y + 40, al_map_rgb(0,0,0));

	//body
	al_draw_filled_ellipse(pos.x + 20, pos.y + 21, 6, 9, al_map_rgb(38,92,54));
		
	
	//legs
	float leftLeg4[] = {pos.x + 17, pos.y + 23, pos.x + 15, pos.y + 42, pos.x + 15, pos.y + 42, pos.x + 20, pos.y + 23};
	al_draw_spline(leftLeg4, al_map_rgb(38,92,54), 2);
	float rightLeg4[] = {pos.x + 23, pos.y + 23, pos.x + 25, pos.y + 42, pos.x + 25, pos.y + 42, pos.x + 20, pos.y + 23};
	al_draw_spline(rightLeg4, al_map_rgb(38,92,54), 2);

	//arms
	float leftArm4[] = {pos.x + 14, pos.y + 15, pos.x + 9, pos.y + 35, pos.x + 9, pos.y + 35, pos.x + 17, pos.y + 15};
	al_draw_spline(leftArm4, al_map_rgb(38,92,54), 2);

	float rightArm4[] = {pos.x + 26, pos.y + 15, pos.x + 31, pos.y + 35, pos.x + 31, pos.y + 35, pos.x + 23, pos.y + 15};
	al_draw_spline(rightArm4, al_map_rgb(38,92,54), 2);

	//head
	al_draw_filled_ellipse(pos.x + 20, pos.y + 11, 25, 9, al_map_rgb(38,92,54));
	al_draw_ellipse(pos.x + 20, pos.y + 11, 25, 9, al_map_rgb(10,59,25),1);
	al_draw_filled_ellipse(pos.x + 20, pos.y + 11, 13, 6, al_map_rgb(183,183,187)); //white mouth area
	al_draw_filled_ellipse(pos.x + 20, pos.y + 11, 8, 4, al_map_rgb(188,0,102));	//pink mouth area
	al_draw_filled_ellipse(pos.x + 20, pos.y + 9, 15, 4, al_map_rgb(38,92,54));	//green top head area

	//eyes
	al_draw_filled_ellipse(pos.x + 14, pos.y + 7, 5, 2, al_map_rgb(211,36,17));
	al_draw_filled_ellipse(pos.x + 26, pos.y + 7, 5, 2, al_map_rgb(211,36,17));
	al_draw_filled_circle(pos.x + 15, pos.y + 7, 1, al_map_rgb(27,28,26)); // pupils
	al_draw_filled_circle(pos.x + 25, pos.y + 7, 1, al_map_rgb(27,28,26));

	//chest lines
	al_draw_line(pos.x + 20, pos.y + 20, pos.x + 20, pos.y + 29, al_map_rgb(10,59,25),2); //vertical
	al_draw_line(pos.x + 17, pos.y + 23, pos.x + 23, pos.y + 23, al_map_rgb(10,59,25),1); //horizontal
	al_draw_line(pos.x + 17, pos.y + 26, pos.x + 23, pos.y + 26, al_map_rgb(10,59,25),1);

}
void canvas::drawClydeSwelling6(ALLEGRO_DISPLAY *display,xy pos)
{
	//background
	//al_draw_filled_rectangle(pos.x, pos.y, pos.x + 40, pos.y + 40, al_map_rgb(0,0,0));

	//body
	al_draw_filled_ellipse(pos.x + 20, pos.y + 21, 6, 9, al_map_rgb(38,92,54));
		
	
	//legs
	float leftLegD[] = {pos.x + 17, pos.y + 23, pos.x + 15, pos.y + 42, pos.x + 15, pos.y + 42, pos.x + 20, pos.y + 23};
	al_draw_spline(leftLegD, al_map_rgb(38,92,54), 2);
	float rightLegD[] = {pos.x + 23, pos.y + 23, pos.x + 25, pos.y + 42, pos.x + 25, pos.y + 42, pos.x + 20, pos.y + 23};
	al_draw_spline(rightLegD, al_map_rgb(38,92,54), 2);

	//arms
	float leftArmD[] = {pos.x + 14, pos.y + 15, pos.x + 9, pos.y + 35, pos.x + 9, pos.y + 35, pos.x + 17, pos.y + 15};
	al_draw_spline(leftArmD, al_map_rgb(38,92,54), 2);

	float rightArmD[] = {pos.x + 26, pos.y + 15, pos.x + 31, pos.y + 35, pos.x + 31, pos.y + 35, pos.x + 23, pos.y + 15};
	al_draw_spline(rightArmD, al_map_rgb(38,92,54), 2);

	//head
	al_draw_filled_ellipse(pos.x + 20, pos.y + 11, 27, 9, al_map_rgb(38,92,54));
	al_draw_ellipse(pos.x + 20, pos.y + 11, 27, 9, al_map_rgb(10,59,25),1);
	al_draw_filled_ellipse(pos.x + 20, pos.y + 11, 13, 6, al_map_rgb(183,183,187)); //white mouth area
	al_draw_filled_ellipse(pos.x + 20, pos.y + 11, 8, 4, al_map_rgb(188,0,102));	//pink mouth area
	al_draw_filled_ellipse(pos.x + 20, pos.y + 9, 15, 4, al_map_rgb(38,92,54));	//green top head area

	//eyes
	al_draw_filled_ellipse(pos.x + 14, pos.y + 7, 5, 2, al_map_rgb(0,0,0));
	al_draw_filled_ellipse(pos.x + 26, pos.y + 7, 5, 2, al_map_rgb(0,0,0));
	al_draw_filled_ellipse(pos.x + 8, pos.y + 10, 5, 2, al_map_rgb(211,36,17));
	al_draw_filled_ellipse(pos.x + 32, pos.y + 4, 5, 2, al_map_rgb(211,36,17));

	al_draw_filled_circle(pos.x + 9, pos.y + 10, 1, al_map_rgb(27,28,26)); // pupils
	al_draw_filled_circle(pos.x + 31, pos.y + 4, 1, al_map_rgb(27,28,26));

	//chest lines
	al_draw_line(pos.x + 20, pos.y + 20, pos.x + 20, pos.y + 29, al_map_rgb(10,59,25),2); //vertical
	al_draw_line(pos.x + 17, pos.y + 23, pos.x + 23, pos.y + 23, al_map_rgb(10,59,25),1); //horizontal
	al_draw_line(pos.x + 17, pos.y + 26, pos.x + 23, pos.y + 26, al_map_rgb(10,59,25),1);
}
void canvas::drawClydeSwellingPop(ALLEGRO_DISPLAY *display,xy pos)
{
	//background
	//al_draw_filled_rectangle(pos.x, pos.y, pos.x + 40, pos.y + 40, al_map_rgb(0,0,0));
	//al_draw_filled_rectangle(pos.x, pos.y - 40, pos.x + 40, pos.y, al_map_rgb(0,0,0));


	//eyes
	al_draw_filled_ellipse(pos.x + 8, pos.y + 10, 5, 2, al_map_rgb(211,36,17)); //main eye sections
	al_draw_filled_ellipse(pos.x + 32, pos.y + 4, 5, 2, al_map_rgb(211,36,17));

	al_draw_filled_circle(pos.x + 9, pos.y + 10, 1, al_map_rgb(27,28,26)); // pupils
	al_draw_filled_circle(pos.x + 31, pos.y + 4, 1, al_map_rgb(27,28,26));

	al_draw_line(pos.x + 5, pos.y - 10, pos.x, pos.y - 20, al_map_rgb(255,255,255),1);  //popping lines - diagonals
	al_draw_line(pos.x + 35, pos.y + 20, pos.x + 40, pos.y + 30, al_map_rgb(255,255,255),1); 
	al_draw_line(pos.x + 5, pos.y + 20, pos.x, pos.y + 30, al_map_rgb(255,255,255),1); 
	al_draw_line(pos.x + 35, pos.y - 10, pos.x + 40, pos.y - 20, al_map_rgb(255,255,255),1); 

	al_draw_line(pos.x - 2, pos.y + 6, pos.x - 17, pos.y + 6, al_map_rgb(255,255,255),1); //popping lines - perpendiculars - length 15
	al_draw_line(pos.x + 42, pos.y + 6, pos.x + 57, pos.y + 6, al_map_rgb(255,255,255),1); 
	al_draw_line(pos.x + 20, pos.y - 9, pos.x + 20, pos.y - 24, al_map_rgb(255,255,255),1); 
	al_draw_line(pos.x + 20, pos.y + 21, pos.x + 20, pos.y + 35, al_map_rgb(255,255,255),1); 

}

/////////////////////////////////////////////
/////////////////Dragon////////////////////

void canvas::drawDragonUp(ALLEGRO_DISPLAY *display,xy pos)
{

		//legs
	al_draw_filled_triangle(pos.x + 20, pos.y + 22, pos.x + 10, pos.y + 38, pos.x + 4, pos.y + 33, al_map_rgb(86,34,111));
	al_draw_filled_triangle(pos.x + 20, pos.y + 22, pos.x + 30, pos.y + 38, pos.x + 36, pos.y + 33, al_map_rgb(86,34,111));

	//arms
	al_draw_filled_triangle(pos.x + 22, pos.y + 26, pos.x + 4, pos.y + 22, pos.x + 6, pos.y + 14, al_map_rgb(86,34,111));
	al_draw_filled_triangle(pos.x + 18, pos.y + 26, pos.x + 36, pos.y + 22, pos.x + 34, pos.y + 14, al_map_rgb(86,34,111));
	al_draw_filled_triangle(pos.x + 2, pos.y + 15, pos.x + 5, pos.y + 20, pos.x + 6, pos.y + 17, al_map_rgb(86,34,111)); //claws
	al_draw_filled_triangle(pos.x + 38, pos.y + 15, pos.x + 35, pos.y + 20, pos.x + 34, pos.y + 17, al_map_rgb(86,34,111)); 

	//tail
	float tailUp[] = {pos.x + 18, pos.y + 20, pos.x + 19, pos.y + 43, pos.x + 21, pos.y + 43,  pos.x + 22, pos.y + 20};
	al_draw_spline(tailUp, al_map_rgb(86,34,111), 2);

	//body
	al_draw_filled_circle(pos.x + 20, pos.y + 24, 11, al_map_rgb(86,34,111));

	//head
	al_draw_filled_circle(pos.x + 20, pos.y + 12, 10, al_map_rgb(86,34,111));
	al_draw_circle(pos.x + 20, pos.y + 12, 10, al_map_rgb(48,26,58), 1); 
	
	//ears
	al_draw_filled_ellipse(pos.x + 9, pos.y + 8, 7, 5, al_map_rgb(86,34,111));
	al_draw_filled_ellipse(pos.x + 31, pos.y + 8, 7, 5, al_map_rgb(86,34,111));
	al_draw_ellipse(pos.x + 9, pos.y + 8, 7, 5, al_map_rgb(48,26,58), 1);   //outlines
	al_draw_ellipse(pos.x + 31, pos.y + 8, 7, 5, al_map_rgb(48,26,58), 1);



}
void canvas::drawDragonLeft(ALLEGRO_DISPLAY *display,xy pos)
{
	//legs
	al_draw_filled_triangle(pos.x + 20, pos.y + 22, pos.x + 10, pos.y + 38, pos.x + 4, pos.y + 33, al_map_rgb(86,34,111));
	al_draw_filled_triangle(pos.x + 20, pos.y + 22, pos.x + 30, pos.y + 38, pos.x + 36, pos.y + 33, al_map_rgb(86,34,111));

	//arms
	al_draw_filled_triangle(pos.x + 22, pos.y + 26, pos.x + 4, pos.y + 22, pos.x + 6, pos.y + 14, al_map_rgb(86,34,111));
	al_draw_filled_triangle(pos.x + 18, pos.y + 26, pos.x + 36, pos.y + 22, pos.x + 34, pos.y + 14, al_map_rgb(86,34,111));
	al_draw_filled_triangle(pos.x + 2, pos.y + 15, pos.x + 5, pos.y + 20, pos.x + 6, pos.y + 17, al_map_rgb(86,34,111)); //claws
	al_draw_filled_triangle(pos.x + 38, pos.y + 15, pos.x + 35, pos.y + 20, pos.x + 34, pos.y + 17, al_map_rgb(86,34,111)); 

	//tail
	float tailL[] = {pos.x + 18, pos.y + 20, pos.x + 19, pos.y + 43, pos.x + 21, pos.y + 43,  pos.x + 22, pos.y + 20};
	al_draw_spline(tailL, al_map_rgb(86,34,111), 2);

	//body
	al_draw_filled_circle(pos.x + 20, pos.y + 24, 11, al_map_rgb(86,34,111));
	al_draw_filled_circle(pos.x + 20, pos.y + 25, 7, al_map_rgb(155,81,110));
	al_draw_line(pos.x + 15, pos.y + 28, pos.x + 25, pos.y + 28, al_map_rgb(99,34,96), 1);  //chest lines
	al_draw_line(pos.x + 15, pos.y + 25, pos.x + 25, pos.y + 25, al_map_rgb(99,34,96), 1);

	//head
	al_draw_filled_ellipse(pos.x + 17, pos.y + 12, 13, 9, al_map_rgb(86,34,111));
	al_draw_ellipse(pos.x + 17, pos.y + 12, 13, 9, al_map_rgb(48,26,58), 1);
	
	//eyes
	al_draw_filled_circle(pos.x + 12, pos.y + 8, 3, al_map_rgb(184,186,189));
	al_draw_filled_circle(pos.x + 11, pos.y + 8, 1 ,al_map_rgb(40,24,49));	//pupils
	
	//nose
	al_draw_filled_circle(pos.x + 7, pos.y + 14, 1, al_map_rgb(40,24,49));

	//cheeks
	al_draw_filled_circle(pos.x + 14, pos.y + 15, 2, al_map_rgb(172,0,94));

	//ears
	al_draw_filled_ellipse(pos.x + 24, pos.y + 11, 3, 2, al_map_rgb(155,81,110));	//inner ear
	float earLeft[] = {pos.x + 20, pos.y + 6, pos.x + 28, pos.y + 9, pos.x + 28, pos.y + 13, pos.x + 22, pos.y + 15};
	al_draw_spline(earLeft, al_map_rgb(48,26,58), 2);

	//mouth
	float mouthL[] = {pos.x + 7, pos.y + 17, pos.x + 9, pos.y + 17, pos.x + 9, pos.y + 17, pos.x + 11, pos.y + 17};
	al_draw_spline(mouthL, al_map_rgb(75,17,68),2);

}
void canvas::drawDragonRight(ALLEGRO_DISPLAY *display,xy pos)
{
	//legs
	al_draw_filled_triangle(pos.x + 20, pos.y + 22, pos.x + 10, pos.y + 38, pos.x + 4, pos.y + 33, al_map_rgb(86,34,111));
	al_draw_filled_triangle(pos.x + 20, pos.y + 22, pos.x + 30, pos.y + 38, pos.x + 36, pos.y + 33, al_map_rgb(86,34,111));

	//arms
	al_draw_filled_triangle(pos.x + 22, pos.y + 26, pos.x + 4, pos.y + 22, pos.x + 6, pos.y + 14, al_map_rgb(86,34,111));
	al_draw_filled_triangle(pos.x + 18, pos.y + 26, pos.x + 36, pos.y + 22, pos.x + 34, pos.y + 14, al_map_rgb(86,34,111));
	al_draw_filled_triangle(pos.x + 2, pos.y + 15, pos.x + 5, pos.y + 20, pos.x + 6, pos.y + 17, al_map_rgb(86,34,111)); //claws
	al_draw_filled_triangle(pos.x + 38, pos.y + 15, pos.x + 35, pos.y + 20, pos.x + 34, pos.y + 17, al_map_rgb(86,34,111)); 

	//tail
	float tailR[] = {pos.x + 18, pos.y + 20, pos.x + 19, pos.y + 43, pos.x + 21, pos.y + 43,  pos.x + 22, pos.y + 20};
	al_draw_spline(tailR, al_map_rgb(86,34,111), 2);

	//body
	al_draw_filled_circle(pos.x + 20, pos.y + 24, 11, al_map_rgb(86,34,111));
	al_draw_filled_circle(pos.x + 20, pos.y + 25, 7, al_map_rgb(155,81,110));
	al_draw_line(pos.x + 15, pos.y + 28, pos.x + 25, pos.y + 28, al_map_rgb(99,34,96), 1);  //chest lines
	al_draw_line(pos.x + 15, pos.y + 25, pos.x + 25, pos.y + 25, al_map_rgb(99,34,96), 1);

	//head
	al_draw_filled_ellipse(pos.x + 23, pos.y + 12, 13, 9, al_map_rgb(86,34,111));
	al_draw_ellipse(pos.x + 23, pos.y + 12, 13, 9, al_map_rgb(48,26,58), 1);
	
	//eyes
	al_draw_filled_circle(pos.x + 28, pos.y + 8, 3, al_map_rgb(184,186,189));
	al_draw_filled_circle(pos.x + 29, pos.y + 8, 1 ,al_map_rgb(40,24,49));	//pupils
	
	//nose
	al_draw_filled_circle(pos.x + 33, pos.y + 14, 1, al_map_rgb(40,24,49));

	//cheeks
	al_draw_filled_circle(pos.x + 26, pos.y + 15, 2, al_map_rgb(172,0,94));

	//ears
	al_draw_filled_ellipse(pos.x + 16, pos.y + 11, 3, 2, al_map_rgb(155,81,110));	//inner ear
	float earRight[] = {pos.x + 20, pos.y + 6, pos.x + 12, pos.y + 9, pos.x + 12, pos.y + 13, pos.x + 18, pos.y + 15};
	al_draw_spline(earRight, al_map_rgb(48,26,58), 2);

	//mouth
	float mouthR[] = {pos.x + 33, pos.y + 17, pos.x + 31, pos.y + 17, pos.x + 31, pos.y + 17, pos.x + 29, pos.y + 17};
	al_draw_spline(mouthR, al_map_rgb(75,17,68),2);

}

void canvas::drawDragonDown1(ALLEGRO_DISPLAY *display,xy pos)
{
	//legs
	al_draw_filled_triangle(pos.x + 20, pos.y + 22, pos.x + 10, pos.y + 38, pos.x + 4, pos.y + 33, al_map_rgb(86,34,111));
	al_draw_filled_triangle(pos.x + 20, pos.y + 22, pos.x + 30, pos.y + 38, pos.x + 36, pos.y + 33, al_map_rgb(86,34,111));

	//arms
	al_draw_filled_triangle(pos.x + 22, pos.y + 26, pos.x + 4, pos.y + 22, pos.x + 6, pos.y + 14, al_map_rgb(86,34,111));
	al_draw_filled_triangle(pos.x + 18, pos.y + 26, pos.x + 36, pos.y + 22, pos.x + 34, pos.y + 14, al_map_rgb(86,34,111));
	al_draw_filled_triangle(pos.x + 2, pos.y + 15, pos.x + 5, pos.y + 20, pos.x + 6, pos.y + 17, al_map_rgb(86,34,111)); //claws
	al_draw_filled_triangle(pos.x + 38, pos.y + 15, pos.x + 35, pos.y + 20, pos.x + 34, pos.y + 17, al_map_rgb(86,34,111)); 

	//tail
	float tail[] = {pos.x + 18, pos.y + 20, pos.x + 19, pos.y + 43, pos.x + 21, pos.y + 43,  pos.x + 22, pos.y + 20};
	al_draw_spline(tail, al_map_rgb(86,34,111), 2);

	//body
	al_draw_filled_circle(pos.x + 20, pos.y + 24, 11, al_map_rgb(86,34,111));
	al_draw_filled_circle(pos.x + 20, pos.y + 25, 7, al_map_rgb(155,81,110));
	al_draw_line(pos.x + 15, pos.y + 28, pos.x + 25, pos.y + 28, al_map_rgb(99,34,96), 1);  //chest lines
	al_draw_line(pos.x + 15, pos.y + 25, pos.x + 25, pos.y + 25, al_map_rgb(99,34,96), 1);

	//ears
	al_draw_filled_ellipse(pos.x + 9, pos.y + 7, 7, 5, al_map_rgb(86,34,111));
	al_draw_filled_ellipse(pos.x + 31, pos.y + 7, 7, 5, al_map_rgb(86,34,111));
	al_draw_filled_ellipse(pos.x + 9, pos.y + 7, 4, 2, al_map_rgb(155,81,110));	//inner ear
	al_draw_filled_ellipse(pos.x + 31, pos.y + 7, 4, 2, al_map_rgb(155,81,110));	

	//head
	al_draw_filled_circle(pos.x + 20, pos.y + 12, 10, al_map_rgb(86,34,111));
	al_draw_circle(pos.x + 20, pos.y + 12, 10, al_map_rgb(48,26,58), 1); 
	
	//eyes
	al_draw_filled_circle(pos.x + 17, pos.y + 8, 3, al_map_rgb(184,186,189));
	al_draw_filled_circle(pos.x + 23, pos.y + 8, 3, al_map_rgb(184,186,189));
	al_draw_filled_circle(pos.x + 18, pos.y + 8, 1 ,al_map_rgb(40,24,49));	//pupils
	al_draw_filled_circle(pos.x + 22, pos.y + 8, 1 ,al_map_rgb(40,24,49));

	//nose
	al_draw_filled_circle(pos.x + 18, pos.y + 14, 1, al_map_rgb(40,24,49));
	al_draw_filled_circle(pos.x + 22, pos.y + 14, 1, al_map_rgb(40,24,49));

	//cheeks
	al_draw_filled_circle(pos.x + 14, pos.y + 14, 2, al_map_rgb(172,0,94));
	al_draw_filled_circle(pos.x + 26, pos.y + 14, 2, al_map_rgb(172,0,94));

	//mouth
	float mouth[] = {pos.x + 15, pos.y + 17, pos.x + 20, pos.y + 19, pos.x + 20, pos.y + 19, pos.x + 25, pos.y + 17};
	al_draw_spline(mouth, al_map_rgb(75,17,68),2);		
}
void canvas::drawDragonDown2(ALLEGRO_DISPLAY *display,xy pos)
{
	//legs
	al_draw_filled_triangle(pos.x + 20, pos.y + 22, pos.x + 10, pos.y + 38, pos.x + 4, pos.y + 33, al_map_rgb(86,34,111));
	al_draw_filled_triangle(pos.x + 20, pos.y + 22, pos.x + 30, pos.y + 38, pos.x + 36, pos.y + 33, al_map_rgb(86,34,111));

	//arms
	al_draw_filled_triangle(pos.x + 22, pos.y + 26, pos.x + 4, pos.y + 22, pos.x + 6, pos.y + 14, al_map_rgb(86,34,111));
	al_draw_filled_triangle(pos.x + 18, pos.y + 26, pos.x + 36, pos.y + 22, pos.x + 34, pos.y + 14, al_map_rgb(86,34,111));
	al_draw_filled_triangle(pos.x + 2, pos.y + 15, pos.x + 5, pos.y + 20, pos.x + 6, pos.y + 17, al_map_rgb(86,34,111)); //claws
	al_draw_filled_triangle(pos.x + 38, pos.y + 15, pos.x + 35, pos.y + 20, pos.x + 34, pos.y + 17, al_map_rgb(86,34,111)); 

	//tail
	float tail1[] = {pos.x + 18, pos.y + 20, pos.x + 19, pos.y + 43, pos.x + 21, pos.y + 43,  pos.x + 22, pos.y + 20};
	al_draw_spline(tail1, al_map_rgb(86,34,111), 2);

	//body
	al_draw_filled_circle(pos.x + 20, pos.y + 24, 11, al_map_rgb(86,34,111));
	al_draw_filled_circle(pos.x + 20, pos.y + 25, 7, al_map_rgb(155,81,110));
	al_draw_line(pos.x + 15, pos.y + 28, pos.x + 25, pos.y + 28, al_map_rgb(99,34,96), 1);  //chest lines
	al_draw_line(pos.x + 15, pos.y + 25, pos.x + 25, pos.y + 25, al_map_rgb(99,34,96), 1);

	////ears
	//al_draw_filled_ellipse(pos.x + 10, pos.y + 7, 6, 5, al_map_rgb(86,34,111));
	//al_draw_filled_ellipse(pos.x + 30, pos.y + 7, 6, 5, al_map_rgb(86,34,111));
	//al_draw_filled_ellipse(pos.x + 10, pos.y + 7, 3, 2, al_map_rgb(155,81,110));	//inner ear
	//al_draw_filled_ellipse(pos.x + 30, pos.y + 7, 3, 2, al_map_rgb(155,81,110));	

	//head
	al_draw_filled_circle(pos.x + 20, pos.y + 12, 10, al_map_rgb(86,34,111));
	al_draw_circle(pos.x + 20, pos.y + 12, 10, al_map_rgb(48,26,58), 1); 
	
	//eyes
	al_draw_filled_circle(pos.x + 17, pos.y + 8, 3, al_map_rgb(184,186,189));
	al_draw_filled_circle(pos.x + 23, pos.y + 8, 3, al_map_rgb(184,186,189));
	al_draw_filled_circle(pos.x + 18, pos.y + 8, 1 ,al_map_rgb(40,24,49));	//pupils
	al_draw_filled_circle(pos.x + 22, pos.y + 8, 1 ,al_map_rgb(40,24,49));

	//nose
	al_draw_filled_circle(pos.x + 18, pos.y + 14, 1, al_map_rgb(40,24,49));
	al_draw_filled_circle(pos.x + 22, pos.y + 14, 1, al_map_rgb(40,24,49));

	//cheeks
	al_draw_filled_circle(pos.x + 14, pos.y + 14, 2, al_map_rgb(172,0,94));
	al_draw_filled_circle(pos.x + 26, pos.y + 14, 2, al_map_rgb(172,0,94));

	//mouth
	float mouth1[] = {pos.x + 15, pos.y + 17, pos.x + 20, pos.y + 19, pos.x + 20, pos.y + 19, pos.x + 25, pos.y + 17};
	al_draw_spline(mouth1, al_map_rgb(75,17,68),2);

}
void canvas::drawDragonDown3(ALLEGRO_DISPLAY *display,xy pos)
{
	//legs
	al_draw_filled_triangle(pos.x + 20, pos.y + 22, pos.x + 10, pos.y + 38, pos.x + 4, pos.y + 33, al_map_rgb(86,34,111));
	al_draw_filled_triangle(pos.x + 20, pos.y + 22, pos.x + 30, pos.y + 38, pos.x + 36, pos.y + 33, al_map_rgb(86,34,111));

	//arms
	al_draw_filled_triangle(pos.x + 22, pos.y + 26, pos.x + 4, pos.y + 22, pos.x + 6, pos.y + 14, al_map_rgb(86,34,111));
	al_draw_filled_triangle(pos.x + 18, pos.y + 26, pos.x + 36, pos.y + 22, pos.x + 34, pos.y + 14, al_map_rgb(86,34,111));
	al_draw_filled_triangle(pos.x + 2, pos.y + 15, pos.x + 5, pos.y + 20, pos.x + 6, pos.y + 17, al_map_rgb(86,34,111)); //claws
	al_draw_filled_triangle(pos.x + 38, pos.y + 15, pos.x + 35, pos.y + 20, pos.x + 34, pos.y + 17, al_map_rgb(86,34,111)); 

	//tail
	float tail2[] = {pos.x + 18, pos.y + 20, pos.x + 19, pos.y + 43, pos.x + 21, pos.y + 43,  pos.x + 22, pos.y + 20};
	al_draw_spline(tail2, al_map_rgb(86,34,111), 2);

	//body
	al_draw_filled_circle(pos.x + 20, pos.y + 24, 11, al_map_rgb(86,34,111));
	al_draw_filled_circle(pos.x + 20, pos.y + 25, 7, al_map_rgb(155,81,110));
	al_draw_line(pos.x + 15, pos.y + 28, pos.x + 25, pos.y + 28, al_map_rgb(99,34,96), 1);  //chest lines
	al_draw_line(pos.x + 15, pos.y + 25, pos.x + 25, pos.y + 25, al_map_rgb(99,34,96), 1);

	//ears
	al_draw_filled_ellipse(pos.x + 15, pos.y + 7, 6, 5, al_map_rgb(86,34,111));
	al_draw_filled_ellipse(pos.x + 25, pos.y + 7, 6, 5, al_map_rgb(86,34,111));


	//head
	al_draw_filled_circle(pos.x + 20, pos.y + 12, 10, al_map_rgb(86,34,111));
	al_draw_circle(pos.x + 20, pos.y + 12, 10, al_map_rgb(48,26,58), 1); 
	
	//eyes
	al_draw_filled_circle(pos.x + 17, pos.y + 8, 3, al_map_rgb(184,186,189));
	al_draw_filled_circle(pos.x + 23, pos.y + 8, 3, al_map_rgb(184,186,189));
	al_draw_filled_circle(pos.x + 18, pos.y + 8, 1 ,al_map_rgb(40,24,49));	//pupils
	al_draw_filled_circle(pos.x + 22, pos.y + 8, 1 ,al_map_rgb(40,24,49));

	//nose
	al_draw_filled_circle(pos.x + 18, pos.y + 14, 1, al_map_rgb(40,24,49));
	al_draw_filled_circle(pos.x + 22, pos.y + 14, 1, al_map_rgb(40,24,49));

	//cheeks
	al_draw_filled_circle(pos.x + 14, pos.y + 14, 2, al_map_rgb(172,0,94));
	al_draw_filled_circle(pos.x + 26, pos.y + 14, 2, al_map_rgb(172,0,94));

	//mouth
	float mouth2[] = {pos.x + 15, pos.y + 17, pos.x + 20, pos.y + 19, pos.x + 20, pos.y + 19, pos.x + 25, pos.y + 17};
	al_draw_spline(mouth2, al_map_rgb(75,17,68),2);

}
void canvas::drawDragonDown4(ALLEGRO_DISPLAY *display,xy pos)
{
	//legs
	al_draw_filled_triangle(pos.x + 20, pos.y + 22, pos.x + 10, pos.y + 38, pos.x + 4, pos.y + 33, al_map_rgb(86,34,111));
	al_draw_filled_triangle(pos.x + 20, pos.y + 22, pos.x + 30, pos.y + 38, pos.x + 36, pos.y + 33, al_map_rgb(86,34,111));

	//arms
	al_draw_filled_triangle(pos.x + 22, pos.y + 26, pos.x + 4, pos.y + 22, pos.x + 6, pos.y + 14, al_map_rgb(86,34,111));
	al_draw_filled_triangle(pos.x + 18, pos.y + 26, pos.x + 36, pos.y + 22, pos.x + 34, pos.y + 14, al_map_rgb(86,34,111));
	al_draw_filled_triangle(pos.x + 2, pos.y + 15, pos.x + 5, pos.y + 20, pos.x + 6, pos.y + 17, al_map_rgb(86,34,111)); //claws
	al_draw_filled_triangle(pos.x + 38, pos.y + 15, pos.x + 35, pos.y + 20, pos.x + 34, pos.y + 17, al_map_rgb(86,34,111)); 

	//tail
	float tail3[] = {pos.x + 18, pos.y + 20, pos.x + 19, pos.y + 43, pos.x + 21, pos.y + 43,  pos.x + 22, pos.y + 20};
	al_draw_spline(tail3, al_map_rgb(86,34,111), 2);

	//body
	al_draw_filled_circle(pos.x + 20, pos.y + 24, 11, al_map_rgb(86,34,111));
	al_draw_filled_circle(pos.x + 20, pos.y + 25, 7, al_map_rgb(155,81,110));
	al_draw_line(pos.x + 15, pos.y + 28, pos.x + 25, pos.y + 28, al_map_rgb(99,34,96), 1);  //chest lines
	al_draw_line(pos.x + 15, pos.y + 25, pos.x + 25, pos.y + 25, al_map_rgb(99,34,96), 1);

	//ears
	al_draw_filled_ellipse(pos.x + 12, pos.y + 7, 6, 5, al_map_rgb(86,34,111));
	al_draw_filled_ellipse(pos.x + 28, pos.y + 7, 6, 5, al_map_rgb(86,34,111));
	al_draw_filled_ellipse(pos.x + 12, pos.y + 7, 3, 2, al_map_rgb(155,81,110));	//inner ear
	al_draw_filled_ellipse(pos.x + 28, pos.y + 7, 3, 2, al_map_rgb(155,81,110));	

	//head
	al_draw_filled_circle(pos.x + 20, pos.y + 12, 10, al_map_rgb(86,34,111));
	al_draw_circle(pos.x + 20, pos.y + 12, 10, al_map_rgb(48,26,58), 1); 
	
	//eyes
	al_draw_filled_circle(pos.x + 17, pos.y + 8, 3, al_map_rgb(184,186,189));
	al_draw_filled_circle(pos.x + 23, pos.y + 8, 3, al_map_rgb(184,186,189));
	al_draw_filled_circle(pos.x + 18, pos.y + 8, 1 ,al_map_rgb(40,24,49));	//pupils
	al_draw_filled_circle(pos.x + 22, pos.y + 8, 1 ,al_map_rgb(40,24,49));

	//nose
	al_draw_filled_circle(pos.x + 18, pos.y + 14, 1, al_map_rgb(40,24,49));
	al_draw_filled_circle(pos.x + 22, pos.y + 14, 1, al_map_rgb(40,24,49));

	//cheeks
	al_draw_filled_circle(pos.x + 14, pos.y + 14, 2, al_map_rgb(172,0,94));
	al_draw_filled_circle(pos.x + 26, pos.y + 14, 2, al_map_rgb(172,0,94));

	//mouth
	float mouth3[] = {pos.x + 15, pos.y + 17, pos.x + 20, pos.y + 19, pos.x + 20, pos.y + 19, pos.x + 25, pos.y + 17};
	al_draw_spline(mouth3, al_map_rgb(75,17,68),2);

}
void canvas::drawDragonDown5(ALLEGRO_DISPLAY *display,xy pos)
{
	//legs
	al_draw_filled_triangle(pos.x + 20, pos.y + 22, pos.x + 10, pos.y + 38, pos.x + 4, pos.y + 33, al_map_rgb(86,34,111));
	al_draw_filled_triangle(pos.x + 20, pos.y + 22, pos.x + 30, pos.y + 38, pos.x + 36, pos.y + 33, al_map_rgb(86,34,111));

	//arms
	al_draw_filled_triangle(pos.x + 22, pos.y + 26, pos.x + 4, pos.y + 22, pos.x + 6, pos.y + 14, al_map_rgb(86,34,111));
	al_draw_filled_triangle(pos.x + 18, pos.y + 26, pos.x + 36, pos.y + 22, pos.x + 34, pos.y + 14, al_map_rgb(86,34,111));
	al_draw_filled_triangle(pos.x + 2, pos.y + 15, pos.x + 5, pos.y + 20, pos.x + 6, pos.y + 17, al_map_rgb(86,34,111)); //claws
	al_draw_filled_triangle(pos.x + 38, pos.y + 15, pos.x + 35, pos.y + 20, pos.x + 34, pos.y + 17, al_map_rgb(86,34,111)); 

	//tail
	float tail4[] = {pos.x + 18, pos.y + 20, pos.x + 19, pos.y + 43, pos.x + 21, pos.y + 43,  pos.x + 22, pos.y + 20};
	al_draw_spline(tail4, al_map_rgb(86,34,111), 2);

	//body
	al_draw_filled_circle(pos.x + 20, pos.y + 24, 11, al_map_rgb(86,34,111));
	al_draw_filled_circle(pos.x + 20, pos.y + 25, 7, al_map_rgb(155,81,110));
	al_draw_line(pos.x + 15, pos.y + 28, pos.x + 25, pos.y + 28, al_map_rgb(99,34,96), 1);  //chest lines
	al_draw_line(pos.x + 15, pos.y + 25, pos.x + 25, pos.y + 25, al_map_rgb(99,34,96), 1);

	//ears
	al_draw_filled_ellipse(pos.x + 10, pos.y + 7, 6, 5, al_map_rgb(86,34,111));
	al_draw_filled_ellipse(pos.x + 30, pos.y + 7, 6, 5, al_map_rgb(86,34,111));
	al_draw_filled_ellipse(pos.x + 10, pos.y + 7, 3, 2, al_map_rgb(155,81,110));	//inner ear
	al_draw_filled_ellipse(pos.x + 30, pos.y + 7, 3, 2, al_map_rgb(155,81,110));	

	//head
	al_draw_filled_circle(pos.x + 20, pos.y + 12, 10, al_map_rgb(86,34,111));
	al_draw_circle(pos.x + 20, pos.y + 12, 10, al_map_rgb(48,26,58), 1); 
	
	//eyes
	al_draw_filled_circle(pos.x + 17, pos.y + 8, 3, al_map_rgb(184,186,189));
	al_draw_filled_circle(pos.x + 23, pos.y + 8, 3, al_map_rgb(184,186,189));
	al_draw_filled_circle(pos.x + 18, pos.y + 8, 1 ,al_map_rgb(40,24,49));	//pupils
	al_draw_filled_circle(pos.x + 22, pos.y + 8, 1 ,al_map_rgb(40,24,49));

	//nose
	al_draw_filled_circle(pos.x + 18, pos.y + 14, 1, al_map_rgb(40,24,49));
	al_draw_filled_circle(pos.x + 22, pos.y + 14, 1, al_map_rgb(40,24,49));

	//cheeks
	al_draw_filled_circle(pos.x + 14, pos.y + 14, 2, al_map_rgb(172,0,94));
	al_draw_filled_circle(pos.x + 26, pos.y + 14, 2, al_map_rgb(172,0,94));

	//mouth
	float mouth4[] = {pos.x + 15, pos.y + 17, pos.x + 20, pos.y + 19, pos.x + 20, pos.y + 19, pos.x + 25, pos.y + 17};
	al_draw_spline(mouth4, al_map_rgb(75,17,68),2);

}

/////////////////////////////////////////////
//////////////Dragon swelling///////////////

void canvas::drawDragonSwelling1(ALLEGRO_DISPLAY *display,xy pos)
{
	//legs
	al_draw_filled_triangle(pos.x + 20, pos.y + 22, pos.x + 10, pos.y + 38, pos.x + 4, pos.y + 33, al_map_rgb(86,34,111));
	al_draw_filled_triangle(pos.x + 20, pos.y + 22, pos.x + 30, pos.y + 38, pos.x + 36, pos.y + 33, al_map_rgb(86,34,111));

	//arms
	al_draw_filled_triangle(pos.x + 22, pos.y + 26, pos.x + 4, pos.y + 22, pos.x + 6, pos.y + 14, al_map_rgb(86,34,111));
	al_draw_filled_triangle(pos.x + 18, pos.y + 26, pos.x + 36, pos.y + 22, pos.x + 34, pos.y + 14, al_map_rgb(86,34,111));
	al_draw_filled_triangle(pos.x + 2, pos.y + 15, pos.x + 5, pos.y + 20, pos.x + 6, pos.y + 17, al_map_rgb(86,34,111)); //claws
	al_draw_filled_triangle(pos.x + 38, pos.y + 15, pos.x + 35, pos.y + 20, pos.x + 34, pos.y + 17, al_map_rgb(86,34,111)); 

	//tail
	float tail[] = {pos.x + 18, pos.y + 20, pos.x + 19, pos.y + 43, pos.x + 21, pos.y + 43,  pos.x + 22, pos.y + 20};
	al_draw_spline(tail, al_map_rgb(86,34,111), 2);

	//body
	al_draw_filled_circle(pos.x + 20, pos.y + 24, 11, al_map_rgb(86,34,111));
	al_draw_filled_circle(pos.x + 20, pos.y + 25, 7, al_map_rgb(155,81,110));
	al_draw_line(pos.x + 15, pos.y + 28, pos.x + 25, pos.y + 28, al_map_rgb(99,34,96), 1);  //chest lines
	al_draw_line(pos.x + 15, pos.y + 25, pos.x + 25, pos.y + 25, al_map_rgb(99,34,96), 1);

	//ears
	al_draw_filled_ellipse(pos.x + 9, pos.y + 7, 7, 5, al_map_rgb(86,34,111));
	al_draw_filled_ellipse(pos.x + 31, pos.y + 7, 7, 5, al_map_rgb(86,34,111));
	al_draw_filled_ellipse(pos.x + 9, pos.y + 7, 4, 2, al_map_rgb(155,81,110));	//inner ear
	al_draw_filled_ellipse(pos.x + 31, pos.y + 7, 4, 2, al_map_rgb(155,81,110));	

	//head
	al_draw_filled_circle(pos.x + 20, pos.y + 12, 10, al_map_rgb(86,34,111));
	al_draw_circle(pos.x + 20, pos.y + 12, 10, al_map_rgb(48,26,58), 1); 
	
	//eyes
	al_draw_filled_circle(pos.x + 17, pos.y + 8, 3, al_map_rgb(184,186,189));
	al_draw_filled_circle(pos.x + 23, pos.y + 8, 3, al_map_rgb(184,186,189));
	al_draw_filled_circle(pos.x + 18, pos.y + 8, 1 ,al_map_rgb(40,24,49));	//pupils
	al_draw_filled_circle(pos.x + 22, pos.y + 8, 1 ,al_map_rgb(40,24,49));

	//nose
	al_draw_filled_circle(pos.x + 18, pos.y + 14, 1, al_map_rgb(40,24,49));
	al_draw_filled_circle(pos.x + 22, pos.y + 14, 1, al_map_rgb(40,24,49));

	//cheeks
	al_draw_filled_circle(pos.x + 14, pos.y + 14, 2, al_map_rgb(172,0,94));
	al_draw_filled_circle(pos.x + 26, pos.y + 14, 2, al_map_rgb(172,0,94));

	//mouth
	float mouth[] = {pos.x + 15, pos.y + 17, pos.x + 20, pos.y + 19, pos.x + 20, pos.y + 19, pos.x + 25, pos.y + 17};
	al_draw_spline(mouth, al_map_rgb(75,17,68),2);

}
void canvas::drawDragonSwelling2(ALLEGRO_DISPLAY *display,xy pos)
{
	//legs
	al_draw_filled_triangle(pos.x + 20, pos.y + 22, pos.x + 10, pos.y + 38, pos.x + 4, pos.y + 33, al_map_rgb(86,34,111));
	al_draw_filled_triangle(pos.x + 20, pos.y + 22, pos.x + 30, pos.y + 38, pos.x + 36, pos.y + 33, al_map_rgb(86,34,111));

	//arms
	al_draw_filled_triangle(pos.x + 22, pos.y + 26, pos.x + 4, pos.y + 22, pos.x + 6, pos.y + 14, al_map_rgb(86,34,111));
	al_draw_filled_triangle(pos.x + 18, pos.y + 26, pos.x + 36, pos.y + 22, pos.x + 34, pos.y + 14, al_map_rgb(86,34,111));
	al_draw_filled_triangle(pos.x + 2, pos.y + 15, pos.x + 5, pos.y + 20, pos.x + 6, pos.y + 17, al_map_rgb(86,34,111)); //claws
	al_draw_filled_triangle(pos.x + 38, pos.y + 15, pos.x + 35, pos.y + 20, pos.x + 34, pos.y + 17, al_map_rgb(86,34,111)); 

	//tail
	float tail1[] = {pos.x + 18, pos.y + 20, pos.x + 19, pos.y + 43, pos.x + 21, pos.y + 43,  pos.x + 22, pos.y + 20};
	al_draw_spline(tail1, al_map_rgb(86,34,111), 2);

	//body
	al_draw_filled_circle(pos.x + 20, pos.y + 24, 11, al_map_rgb(86,34,111));
	al_draw_filled_circle(pos.x + 20, pos.y + 25, 7, al_map_rgb(155,81,110));
	al_draw_line(pos.x + 15, pos.y + 28, pos.x + 25, pos.y + 28, al_map_rgb(99,34,96), 1);  //chest lines
	al_draw_line(pos.x + 15, pos.y + 25, pos.x + 25, pos.y + 25, al_map_rgb(99,34,96), 1);

	//ears
	al_draw_filled_ellipse(pos.x + 9, pos.y + 7, 7, 5, al_map_rgb(86,34,111));
	al_draw_filled_ellipse(pos.x + 31, pos.y + 7, 7, 5, al_map_rgb(86,34,111));
	al_draw_filled_ellipse(pos.x + 9, pos.y + 7, 4, 2, al_map_rgb(155,81,110));	//inner ear
	al_draw_filled_ellipse(pos.x + 31, pos.y + 7, 4, 2, al_map_rgb(155,81,110));	

	//head
	al_draw_filled_circle(pos.x + 20, pos.y + 12, 12, al_map_rgb(86,34,111));
	al_draw_circle(pos.x + 20, pos.y + 12, 12, al_map_rgb(48,26,58), 1); 
	
	//eyes
	al_draw_filled_circle(pos.x + 17, pos.y + 8, 3, al_map_rgb(184,186,189));
	al_draw_filled_circle(pos.x + 23, pos.y + 8, 3, al_map_rgb(184,186,189));
	al_draw_filled_circle(pos.x + 18, pos.y + 8, 1 ,al_map_rgb(40,24,49));	//pupils
	al_draw_filled_circle(pos.x + 22, pos.y + 8, 1 ,al_map_rgb(40,24,49));

	//nose
	al_draw_filled_circle(pos.x + 18, pos.y + 14, 1, al_map_rgb(40,24,49));
	al_draw_filled_circle(pos.x + 22, pos.y + 14, 1, al_map_rgb(40,24,49));

	//cheeks
	al_draw_filled_circle(pos.x + 14, pos.y + 14, 2, al_map_rgb(172,0,94));
	al_draw_filled_circle(pos.x + 26, pos.y + 14, 2, al_map_rgb(172,0,94));

	//mouth
	float mouth1[] = {pos.x + 15, pos.y + 17, pos.x + 20, pos.y + 19, pos.x + 20, pos.y + 19, pos.x + 25, pos.y + 17};
	al_draw_spline(mouth1, al_map_rgb(75,17,68),2);

}
void canvas::drawDragonSwelling3(ALLEGRO_DISPLAY *display,xy pos)
{
	//legs
	al_draw_filled_triangle(pos.x + 20, pos.y + 22, pos.x + 10, pos.y + 38, pos.x + 4, pos.y + 33, al_map_rgb(86,34,111));
	al_draw_filled_triangle(pos.x + 20, pos.y + 22, pos.x + 30, pos.y + 38, pos.x + 36, pos.y + 33, al_map_rgb(86,34,111));

	//arms
	al_draw_filled_triangle(pos.x + 22, pos.y + 26, pos.x + 4, pos.y + 22, pos.x + 6, pos.y + 14, al_map_rgb(86,34,111));
	al_draw_filled_triangle(pos.x + 18, pos.y + 26, pos.x + 36, pos.y + 22, pos.x + 34, pos.y + 14, al_map_rgb(86,34,111));
	al_draw_filled_triangle(pos.x + 2, pos.y + 15, pos.x + 5, pos.y + 20, pos.x + 6, pos.y + 17, al_map_rgb(86,34,111)); //claws
	al_draw_filled_triangle(pos.x + 38, pos.y + 15, pos.x + 35, pos.y + 20, pos.x + 34, pos.y + 17, al_map_rgb(86,34,111)); 

	//tail
	float tail2[] = {pos.x + 18, pos.y + 20, pos.x + 19, pos.y + 43, pos.x + 21, pos.y + 43,  pos.x + 22, pos.y + 20};
	al_draw_spline(tail2, al_map_rgb(86,34,111), 2);

	//body
	al_draw_filled_circle(pos.x + 20, pos.y + 24, 11, al_map_rgb(86,34,111));
	al_draw_filled_circle(pos.x + 20, pos.y + 25, 7, al_map_rgb(155,81,110));
	al_draw_line(pos.x + 15, pos.y + 28, pos.x + 25, pos.y + 28, al_map_rgb(99,34,96), 1);  //chest lines
	al_draw_line(pos.x + 15, pos.y + 25, pos.x + 25, pos.y + 25, al_map_rgb(99,34,96), 1);

	//ears
	al_draw_filled_ellipse(pos.x + 9, pos.y + 7, 7, 5, al_map_rgb(86,34,111));
	al_draw_filled_ellipse(pos.x + 31, pos.y + 7, 7, 5, al_map_rgb(86,34,111));
	al_draw_filled_ellipse(pos.x + 9, pos.y + 7, 4, 2, al_map_rgb(155,81,110));	//inner ear
	al_draw_filled_ellipse(pos.x + 31, pos.y + 7, 4, 2, al_map_rgb(155,81,110));	

	//head
	al_draw_filled_circle(pos.x + 20, pos.y + 12, 14, al_map_rgb(86,34,111));
	al_draw_circle(pos.x + 20, pos.y + 12, 14, al_map_rgb(48,26,58), 1); 
	
	//eyes
	al_draw_filled_circle(pos.x + 17, pos.y + 8, 3, al_map_rgb(243,196,201));
	al_draw_filled_circle(pos.x + 23, pos.y + 8, 3, al_map_rgb(243,196,201));
	al_draw_filled_circle(pos.x + 18, pos.y + 8, 1 ,al_map_rgb(40,24,49));	//pupils
	al_draw_filled_circle(pos.x + 22, pos.y + 8, 1 ,al_map_rgb(40,24,49));

	//nose
	al_draw_filled_circle(pos.x + 18, pos.y + 14, 1, al_map_rgb(40,24,49));
	al_draw_filled_circle(pos.x + 22, pos.y + 14, 1, al_map_rgb(40,24,49));

	//cheeks
	al_draw_filled_circle(pos.x + 14, pos.y + 14, 2, al_map_rgb(172,0,94));
	al_draw_filled_circle(pos.x + 26, pos.y + 14, 2, al_map_rgb(172,0,94));

	//mouth
	float mouth2[] = {pos.x + 15, pos.y + 17, pos.x + 20, pos.y + 19, pos.x + 20, pos.y + 19, pos.x + 25, pos.y + 17};
	al_draw_spline(mouth2, al_map_rgb(75,17,68),2);
	
}
void canvas::drawDragonSwelling4(ALLEGRO_DISPLAY *display,xy pos)
{
	//legs
	al_draw_filled_triangle(pos.x + 20, pos.y + 22, pos.x + 10, pos.y + 38, pos.x + 4, pos.y + 33, al_map_rgb(86,34,111));
	al_draw_filled_triangle(pos.x + 20, pos.y + 22, pos.x + 30, pos.y + 38, pos.x + 36, pos.y + 33, al_map_rgb(86,34,111));

	//arms
	al_draw_filled_triangle(pos.x + 22, pos.y + 26, pos.x + 4, pos.y + 22, pos.x + 6, pos.y + 14, al_map_rgb(86,34,111));
	al_draw_filled_triangle(pos.x + 18, pos.y + 26, pos.x + 36, pos.y + 22, pos.x + 34, pos.y + 14, al_map_rgb(86,34,111));
	al_draw_filled_triangle(pos.x + 2, pos.y + 15, pos.x + 5, pos.y + 20, pos.x + 6, pos.y + 17, al_map_rgb(86,34,111)); //claws
	al_draw_filled_triangle(pos.x + 38, pos.y + 15, pos.x + 35, pos.y + 20, pos.x + 34, pos.y + 17, al_map_rgb(86,34,111)); 

	//tail
	float tail3[] = {pos.x + 18, pos.y + 20, pos.x + 19, pos.y + 43, pos.x + 21, pos.y + 43,  pos.x + 22, pos.y + 20};
	al_draw_spline(tail3, al_map_rgb(86,34,111), 2);

	//body
	al_draw_filled_circle(pos.x + 20, pos.y + 24, 11, al_map_rgb(86,34,111));
	al_draw_filled_circle(pos.x + 20, pos.y + 25, 7, al_map_rgb(155,81,110));
	al_draw_line(pos.x + 15, pos.y + 28, pos.x + 25, pos.y + 28, al_map_rgb(99,34,96), 1);  //chest lines
	al_draw_line(pos.x + 15, pos.y + 25, pos.x + 25, pos.y + 25, al_map_rgb(99,34,96), 1);

	//ears
	al_draw_filled_ellipse(pos.x + 9, pos.y + 7, 7, 5, al_map_rgb(86,34,111));
	al_draw_filled_ellipse(pos.x + 31, pos.y + 7, 7, 5, al_map_rgb(86,34,111));
	al_draw_filled_ellipse(pos.x + 9, pos.y + 7, 4, 2, al_map_rgb(155,81,110));	//inner ear
	al_draw_filled_ellipse(pos.x + 31, pos.y + 7, 4, 2, al_map_rgb(155,81,110));	

	//head
	al_draw_filled_circle(pos.x + 20, pos.y + 12, 16, al_map_rgb(86,34,111));
	al_draw_circle(pos.x + 20, pos.y + 12, 16, al_map_rgb(48,26,58), 1); 
	
	//eyes
	al_draw_filled_circle(pos.x + 17, pos.y + 8, 3, al_map_rgb(243,133,134));
	al_draw_filled_circle(pos.x + 23, pos.y + 8, 3, al_map_rgb(243,133,134));
	al_draw_filled_circle(pos.x + 18, pos.y + 8, 1 ,al_map_rgb(40,24,49));	//pupils
	al_draw_filled_circle(pos.x + 22, pos.y + 8, 1 ,al_map_rgb(40,24,49));

	//nose
	al_draw_filled_circle(pos.x + 18, pos.y + 14, 1, al_map_rgb(40,24,49));
	al_draw_filled_circle(pos.x + 22, pos.y + 14, 1, al_map_rgb(40,24,49));

	//cheeks
	al_draw_filled_circle(pos.x + 14, pos.y + 14, 2, al_map_rgb(172,0,94));
	al_draw_filled_circle(pos.x + 26, pos.y + 14, 2, al_map_rgb(172,0,94));

	//mouth
	float mouth3[] = {pos.x + 15, pos.y + 17, pos.x + 20, pos.y + 19, pos.x + 20, pos.y + 19, pos.x + 25, pos.y + 17};
	al_draw_spline(mouth3, al_map_rgb(75,17,68),2);
	
}
void canvas::drawDragonSwelling5(ALLEGRO_DISPLAY *display,xy pos)
{
	//legs
	al_draw_filled_triangle(pos.x + 20, pos.y + 22, pos.x + 10, pos.y + 38, pos.x + 4, pos.y + 33, al_map_rgb(86,34,111));
	al_draw_filled_triangle(pos.x + 20, pos.y + 22, pos.x + 30, pos.y + 38, pos.x + 36, pos.y + 33, al_map_rgb(86,34,111));

	//arms
	al_draw_filled_triangle(pos.x + 22, pos.y + 26, pos.x + 4, pos.y + 22, pos.x + 6, pos.y + 14, al_map_rgb(86,34,111));
	al_draw_filled_triangle(pos.x + 18, pos.y + 26, pos.x + 36, pos.y + 22, pos.x + 34, pos.y + 14, al_map_rgb(86,34,111));
	al_draw_filled_triangle(pos.x + 2, pos.y + 15, pos.x + 5, pos.y + 20, pos.x + 6, pos.y + 17, al_map_rgb(86,34,111)); //claws
	al_draw_filled_triangle(pos.x + 38, pos.y + 15, pos.x + 35, pos.y + 20, pos.x + 34, pos.y + 17, al_map_rgb(86,34,111)); 

	//tail
	float tail4[] = {pos.x + 18, pos.y + 20, pos.x + 19, pos.y + 43, pos.x + 21, pos.y + 43,  pos.x + 22, pos.y + 20};
	al_draw_spline(tail4, al_map_rgb(86,34,111), 2);

	//body
	al_draw_filled_circle(pos.x + 20, pos.y + 24, 11, al_map_rgb(86,34,111));
	al_draw_filled_circle(pos.x + 20, pos.y + 25, 7, al_map_rgb(155,81,110));
	al_draw_line(pos.x + 15, pos.y + 28, pos.x + 25, pos.y + 28, al_map_rgb(99,34,96), 1);  //chest lines
	al_draw_line(pos.x + 15, pos.y + 25, pos.x + 25, pos.y + 25, al_map_rgb(99,34,96), 1);

	//ears
	al_draw_filled_ellipse(pos.x + 9, pos.y + 7, 7, 5, al_map_rgb(86,34,111));
	al_draw_filled_ellipse(pos.x + 31, pos.y + 7, 7, 5, al_map_rgb(86,34,111));
	al_draw_filled_ellipse(pos.x + 9, pos.y + 7, 4, 2, al_map_rgb(155,81,110));	//inner ear
	al_draw_filled_ellipse(pos.x + 31, pos.y + 7, 4, 2, al_map_rgb(155,81,110));	

	//head
	al_draw_filled_circle(pos.x + 20, pos.y + 12, 18, al_map_rgb(86,34,111));
	al_draw_circle(pos.x + 20, pos.y + 12, 18, al_map_rgb(48,26,58), 1); 
	
	//eyes
	al_draw_filled_circle(pos.x + 17, pos.y + 8, 3, al_map_rgb(211,36,17));
	al_draw_filled_circle(pos.x + 23, pos.y + 8, 3, al_map_rgb(211,36,17));
	al_draw_filled_circle(pos.x + 18, pos.y + 8, 1 ,al_map_rgb(40,24,49));	//pupils
	al_draw_filled_circle(pos.x + 22, pos.y + 8, 1 ,al_map_rgb(40,24,49));

	//nose
	al_draw_filled_circle(pos.x + 18, pos.y + 14, 1, al_map_rgb(40,24,49));
	al_draw_filled_circle(pos.x + 22, pos.y + 14, 1, al_map_rgb(40,24,49));

	//cheeks
	al_draw_filled_circle(pos.x + 14, pos.y + 14, 2, al_map_rgb(172,0,94));
	al_draw_filled_circle(pos.x + 26, pos.y + 14, 2, al_map_rgb(172,0,94));

	//mouth
	float mouth4[] = {pos.x + 15, pos.y + 17, pos.x + 20, pos.y + 19, pos.x + 20, pos.y + 19, pos.x + 25, pos.y + 17};
	al_draw_spline(mouth4, al_map_rgb(75,17,68),2);
	
}
void canvas::drawDragonSwelling6(ALLEGRO_DISPLAY *display,xy pos)
{
	//legs
	al_draw_filled_triangle(pos.x + 20, pos.y + 22, pos.x + 10, pos.y + 38, pos.x + 4, pos.y + 33, al_map_rgb(86,34,111));
	al_draw_filled_triangle(pos.x + 20, pos.y + 22, pos.x + 30, pos.y + 38, pos.x + 36, pos.y + 33, al_map_rgb(86,34,111));

	//arms
	al_draw_filled_triangle(pos.x + 22, pos.y + 26, pos.x + 4, pos.y + 22, pos.x + 6, pos.y + 14, al_map_rgb(86,34,111));
	al_draw_filled_triangle(pos.x + 18, pos.y + 26, pos.x + 36, pos.y + 22, pos.x + 34, pos.y + 14, al_map_rgb(86,34,111));
	al_draw_filled_triangle(pos.x + 2, pos.y + 15, pos.x + 5, pos.y + 20, pos.x + 6, pos.y + 17, al_map_rgb(86,34,111)); //claws
	al_draw_filled_triangle(pos.x + 38, pos.y + 15, pos.x + 35, pos.y + 20, pos.x + 34, pos.y + 17, al_map_rgb(86,34,111)); 

	//tail
	float tailD[] = {pos.x + 18, pos.y + 20, pos.x + 19, pos.y + 43, pos.x + 21, pos.y + 43,  pos.x + 22, pos.y + 20};
	al_draw_spline(tailD, al_map_rgb(86,34,111), 2);

	//body
	al_draw_filled_circle(pos.x + 20, pos.y + 24, 11, al_map_rgb(86,34,111));
	al_draw_filled_circle(pos.x + 20, pos.y + 25, 7, al_map_rgb(155,81,110));
	al_draw_line(pos.x + 15, pos.y + 28, pos.x + 25, pos.y + 28, al_map_rgb(99,34,96), 1);  //chest lines
	al_draw_line(pos.x + 15, pos.y + 25, pos.x + 25, pos.y + 25, al_map_rgb(99,34,96), 1);

	//ears
	al_draw_filled_ellipse(pos.x + 9, pos.y + 7, 7, 5, al_map_rgb(86,34,111));
	al_draw_filled_ellipse(pos.x + 31, pos.y + 7, 7, 5, al_map_rgb(86,34,111));
	al_draw_filled_ellipse(pos.x + 9, pos.y + 7, 4, 2, al_map_rgb(155,81,110));	//inner ear
	al_draw_filled_ellipse(pos.x + 31, pos.y + 7, 4, 2, al_map_rgb(155,81,110));	

	//head
	al_draw_filled_circle(pos.x + 20, pos.y + 12, 20, al_map_rgb(86,34,111));
	al_draw_circle(pos.x + 20, pos.y + 12, 20, al_map_rgb(48,26,58), 1); 
	
	//eyes empty sockets
	al_draw_filled_circle(pos.x + 17, pos.y + 8, 3, al_map_rgb(0,0,0));
	al_draw_filled_circle(pos.x + 23, pos.y + 8, 3, al_map_rgb(0,0,0));

	//nose
	al_draw_filled_circle(pos.x + 18, pos.y + 14, 1, al_map_rgb(40,24,49));
	al_draw_filled_circle(pos.x + 22, pos.y + 14, 1, al_map_rgb(40,24,49));

	//cheeks
	al_draw_filled_circle(pos.x + 14, pos.y + 14, 2, al_map_rgb(172,0,94));
	al_draw_filled_circle(pos.x + 26, pos.y + 14, 2, al_map_rgb(172,0,94));

	//mouth
	float mouthD[] = {pos.x + 15, pos.y + 17, pos.x + 20, pos.y + 19, pos.x + 20, pos.y + 19, pos.x + 25, pos.y + 17};
	al_draw_spline(mouthD, al_map_rgb(75,17,68),2);

	//eyes popping
	al_draw_filled_circle(pos.x + 14, pos.y + 12, 3, al_map_rgb(211,36,17));
	al_draw_filled_circle(pos.x + 26, pos.y + 4, 3, al_map_rgb(211,36,17));
	al_draw_filled_circle(pos.x + 15, pos.y + 12, 1 ,al_map_rgb(40,24,49));	//pupils
	al_draw_filled_circle(pos.x + 25, pos.y + 4, 1 ,al_map_rgb(40,24,49));

}
void canvas::drawDragonSwellingPop(ALLEGRO_DISPLAY *display,xy pos)
{
	//draw background
	al_draw_filled_rectangle(pos.x, pos.y, pos.x + 40, pos.y + 40, al_map_rgb(0,0,0));
	al_draw_filled_rectangle(pos.x, pos.y + 40, pos.x + 40, pos.y, al_map_rgb(0,0,0));


	//eyes popping
	al_draw_filled_circle(pos.x + 14, pos.y + 12, 3, al_map_rgb(211,36,17));  //main eyes section
	al_draw_filled_circle(pos.x + 26, pos.y + 4, 3, al_map_rgb(211,36,17));
	al_draw_filled_circle(pos.x + 15, pos.y + 12, 1 ,al_map_rgb(40,24,49));	//pupils
	al_draw_filled_circle(pos.x + 25, pos.y + 4, 1 ,al_map_rgb(40,24,49));


	al_draw_line(pos.x + 5, pos.y - 8, pos.x, pos.y - 18, al_map_rgb(255,255,255),1);  //popping lines - diagonals
	al_draw_line(pos.x + 35, pos.y + 22, pos.x + 40, pos.y + 32, al_map_rgb(255,255,255),1); 
	al_draw_line(pos.x + 5, pos.y + 22, pos.x, pos.y + 32, al_map_rgb(255,255,255),1); 
	al_draw_line(pos.x + 35, pos.y - 8, pos.x + 40, pos.y - 18, al_map_rgb(255,255,255),1); 

	al_draw_line(pos.x - 2, pos.y + 8, pos.x - 17, pos.y + 8, al_map_rgb(255,255,255),1); //popping lines - perpendiculars - length 15
	al_draw_line(pos.x + 42, pos.y + 8, pos.x + 57, pos.y + 8, al_map_rgb(255,255,255),1); 
	al_draw_line(pos.x + 20, pos.y - 8, pos.x + 20, pos.y - 23, al_map_rgb(255,255,255),1); 
	al_draw_line(pos.x + 20, pos.y + 23, pos.x + 20, pos.y + 38, al_map_rgb(255,255,255),1); 

	
}

/////////////////////////////////////////////
//////////////Dragon Flames//////////////////

void canvas::drawFlames(ALLEGRO_DISPLAY *display,xy pos,int curDirofDragon)
{
	xy flamePos;
	switch (curDirofDragon)
	{
	case UP:
		flamePos.setxy(pos.x,pos.y-40);
		drawFlamesUp(display,flamePos);
		break;
	case DOWN:
		flamePos.setxy(pos.x,pos.y);
		drawFlamesDown(display,flamePos);
		break;
	case LEFT:
		flamePos.setxy(pos.x-40,pos.y);
		drawFlamesLeft(display,flamePos);
		break;
	case RIGHT:
		flamePos.setxy(pos.x+40,pos.y);
		drawFlamesRight(display,flamePos);
		break;

	}
}
void canvas::drawFlamesUp(ALLEGRO_DISPLAY *display,xy pos)
{
	float middleUpTop[] = {pos.x + 20, pos.y + 39, pos.x + 17, pos.y + 35, pos.x + 17, pos.y + 30 , pos.x + 20, pos.y + 12}; //yellow
	al_draw_spline(middleUpTop, al_map_rgb(230,255,66),4);
	float middleUpBottom[] = {pos.x + 20, pos.y + 39, pos.x + 23, pos.y + 35, pos.x + 23, pos.y + 30, pos.x + 20, pos.y + 12};
	al_draw_spline(middleUpBottom, al_map_rgb(230,255,66),4);

	
	float outerUpTop[] = {pos.x + 20, pos.y + 40, pos.x + 12, pos.y + 35, pos.x + 12, pos.y + 20 , pos.x + 20, pos.y}; //red
	al_draw_spline(outerUpTop, al_map_rgb(228,68,58),3);
	float outerUpBottom[] = {pos.x + 20, pos.y + 40, pos.x + 28, pos.y + 35, pos.x + 28, pos.y + 20 ,pos.x + 20, pos.y};
	al_draw_spline(outerUpBottom, al_map_rgb(228,68,58),3);

	float outer0UpTop[] = {pos.x + 20, pos.y + 41, pos.x + 10, pos.y + 36, pos.x + 10, pos.y + 19, pos.x + 20, pos.y - 1}; //red
	al_draw_spline(outer0UpTop, al_map_rgb(184,0,0),0);
	float outer0UpBottom[] = {pos.x + 20, pos.y + 41, pos.x + 30, pos.y + 36, pos.x + 30, pos.y + 19, pos.x + 20, pos.y - 1};
	al_draw_spline(outer0UpBottom, al_map_rgb(184,0,0),0);

	float outer1UpTop[] = {pos.x + 20, pos.y + 40, pos.x + 13, pos.y + 35, pos.x + 13, pos.y + 20 ,pos.x + 20, pos.y + 6}; //red
	al_draw_spline(outer1UpTop, al_map_rgb(228,68,58),2);
	float outer1UpBottom[] = {pos.x + 20, pos.y + 40, pos.x + 27, pos.y + 35, pos.x + 27, pos.y + 20 ,pos.x + 20, pos.y + 6};
	al_draw_spline(outer1UpBottom, al_map_rgb(228,68,58),2);
	
	float outer2UpTop[] = {pos.x + 20, pos.y + 40, pos.x + 15, pos.y + 35, pos.x + 15, pos.y + 20 ,pos.x + 20, pos.y + 8};  //orange
	al_draw_spline(outer2UpTop, al_map_rgb(191,208,58),2);
	float outer2UpBottom[] = {pos.x + 20, pos.y + 40, pos.x + 25, pos.y + 35, pos.x + 25, pos.y + 20 ,pos.x + 20, pos.y + 8};
	al_draw_spline(outer2UpBottom, al_map_rgb(191,208,58),2);

	al_draw_line(pos.x + 20, pos.y + 36, pos.x + 20, pos.y + 29, al_map_rgb(255,255,255), 2); //white

	//draw extra outline
	al_draw_spline(outer1UpTop, al_map_rgb(222,0,0),0);
	al_draw_spline(outer1UpBottom, al_map_rgb(222,0,0),0);
}
void canvas::drawFlamesDown(ALLEGRO_DISPLAY *display,xy pos)
{
	float middleDownTop[] = {pos.x + 20, pos.y + 1, pos.x + 17, pos.y + 5, pos.x + 17, pos.y + 10 , pos.x + 20, pos.y + 28}; //yellow
	al_draw_spline(middleDownTop, al_map_rgb(230,255,66),4);
	float middleDownBottom[] = {pos.x + 20, pos.y + 1, pos.x + 23, pos.y + 5, pos.x + 23, pos.y + 10, pos.x + 20, pos.y + 28};
	al_draw_spline(middleDownBottom, al_map_rgb(230,255,66),4);

	
	float outerDownTop[] = {pos.x + 20, pos.y, pos.x + 12, pos.y + 5, pos.x + 12, pos.y + 20 , pos.x + 20, pos.y + 40}; //red
	al_draw_spline(outerDownTop, al_map_rgb(228,68,58),3);
	float outerDownBottom[] = {pos.x + 20, pos.y, pos.x + 28, pos.y + 5, pos.x + 28, pos.y + 20 ,pos.x + 20, pos.y + 40};
	al_draw_spline(outerDownBottom, al_map_rgb(228,68,58),3);

	float outer0DownTop[] = {pos.x + 20, pos.y - 1, pos.x + 10, pos.y + 4, pos.x + 10, pos.y + 21, pos.x + 20, pos.y + 41}; //red
	al_draw_spline(outer0DownTop, al_map_rgb(184,0,0),0);
	float outer0DownBottom[] = {pos.x + 20, pos.y - 1, pos.x + 30, pos.y + 4, pos.x + 30, pos.y + 21, pos.x + 20, pos.y + 41};
	al_draw_spline(outer0DownBottom, al_map_rgb(184,0,0),0);

	float outer1DownTop[] = {pos.x + 20, pos.y, pos.x + 13, pos.y + 5, pos.x + 13, pos.y + 20 ,pos.x + 20, pos.y + 34}; //red
	al_draw_spline(outer1DownTop, al_map_rgb(228,68,58),2);
	float outer1DownBottom[] = {pos.x + 20, pos.y, pos.x + 27, pos.y + 5, pos.x + 27, pos.y + 20 ,pos.x + 20, pos.y + 34};
	al_draw_spline(outer1DownBottom, al_map_rgb(228,68,58),2);
	
	float outer2DownTop[] = {pos.x + 20, pos.y, pos.x + 15, pos.y + 5, pos.x + 15, pos.y + 20 ,pos.x + 20, pos.y + 32};  //orange
	al_draw_spline(outer2DownTop, al_map_rgb(191,208,58),2);
	float outer2DownBottom[] = {pos.x + 20, pos.y, pos.x + 25, pos.y + 5, pos.x + 25, pos.y + 20 ,pos.x + 20, pos.y + 32};
	al_draw_spline(outer2DownBottom, al_map_rgb(191,208,58),2);

	al_draw_line(pos.x + 20, pos.y + 4, pos.x + 20, pos.y + 11, al_map_rgb(255,255,255), 2); //white

	//draw extra outline
	al_draw_spline(outer1DownTop, al_map_rgb(222,0,0),0);
	al_draw_spline(outer1DownBottom, al_map_rgb(222,0,0),0);

}
void canvas::drawFlamesLeft(ALLEGRO_DISPLAY *display,xy pos)
{
	float middleLeftTop[] = {pos.x + 39, pos.y + 14, pos.x + 35, pos.y + 11, pos.x + 30, pos.y + 11 ,pos.x + 12, pos.y + 14}; //yellow
	al_draw_spline(middleLeftTop, al_map_rgb(230,255,66),4);
	float middleLeftBottom[] = {pos.x + 39, pos.y + 14, pos.x + 35, pos.y + 17, pos.x + 30, pos.y + 17 ,pos.x + 12, pos.y + 14};
	al_draw_spline(middleLeftBottom, al_map_rgb(230,255,66),4);

	
	float outerLeftTop[] = {pos.x + 40, pos.y + 14, pos.x + 35, pos.y + 6, pos.x + 20, pos.y + 6 ,pos.x, pos.y + 14}; //red
	al_draw_spline(outerLeftTop, al_map_rgb(228,68,58),3);
	float outerLeftBottom[] = {pos.x + 40, pos.y + 14, pos.x + 35, pos.y + 22, pos.x + 20, pos.y + 22 ,pos.x, pos.y + 14};
	al_draw_spline(outerLeftBottom, al_map_rgb(228,68,58),3);

	float outer0LeftTop[] = {pos.x + 41, pos.y + 14, pos.x + 36, pos.y + 4, pos.x + 19, pos.y + 4 ,pos.x - 1, pos.y + 14}; //red
	al_draw_spline(outer0LeftTop, al_map_rgb(184,0,0),0);
	float outer0LeftBottom[] = {pos.x + 41, pos.y + 14, pos.x + 36, pos.y + 24, pos.x + 19, pos.y + 24 ,pos.x - 1, pos.y + 14};
	al_draw_spline(outer0LeftBottom, al_map_rgb(184,0,0),0);

	float outer1LeftTop[] = {pos.x + 40, pos.y + 14, pos.x + 35, pos.y + 7, pos.x + 20, pos.y + 7 ,pos.x + 6, pos.y + 14}; //red
	al_draw_spline(outer1LeftTop, al_map_rgb(228,68,58),2);
	float outer1LeftBottom[] = {pos.x + 40, pos.y + 14, pos.x + 35, pos.y + 21, pos.x + 20, pos.y + 21 ,pos.x + 6, pos.y + 14};
	al_draw_spline(outer1LeftBottom, al_map_rgb(228,68,58),2);
	
	float outer2LeftTop[] = {pos.x + 40, pos.y + 14, pos.x + 35, pos.y + 9, pos.x + 20, pos.y + 9 ,pos.x + 8, pos.y + 14};  //orange
	al_draw_spline(outer2LeftTop, al_map_rgb(191,208,58),2);
	float outer2LeftBottom[] = {pos.x + 40, pos.y + 14, pos.x + 35, pos.y + 19, pos.x + 20, pos.y + 19 ,pos.x + 8, pos.y + 14};
	al_draw_spline(outer2LeftBottom, al_map_rgb(191,208,58),2);

	al_draw_line(pos.x + 36, pos.y + 14, pos.x + 29, pos.y + 14, al_map_rgb(255,255,255), 2); //white

	//draw extra outline
	al_draw_spline(outer1LeftTop, al_map_rgb(222,0,0),0);
	al_draw_spline(outer1LeftBottom, al_map_rgb(222,0,0),0);

}
void canvas::drawFlamesRight(ALLEGRO_DISPLAY *display,xy pos)
{
	float middleRightTop[] = {pos.x + 1, pos.y + 14, pos.x + 5, pos.y + 11, pos.x + 10, pos.y + 11 ,pos.x + 28, pos.y + 14}; //yellow
	al_draw_spline(middleRightTop, al_map_rgb(230,255,66),4);
	float middleRightBottom[] = {pos.x + 1, pos.y + 14, pos.x + 5, pos.y + 17, pos.x + 10, pos.y + 17 ,pos.x + 28, pos.y + 14};
	al_draw_spline(middleRightBottom, al_map_rgb(230,255,66),4);

	
	float outerRightTop[] = {pos.x, pos.y + 14, pos.x + 5, pos.y + 6, pos.x + 20, pos.y + 6 ,pos.x + 40, pos.y + 14}; //red
	al_draw_spline(outerRightTop, al_map_rgb(228,68,58),3);
	float outerRightBottom[] = {pos.x, pos.y + 14, pos.x + 5, pos.y + 22, pos.x + 20, pos.y + 22 ,pos.x + 40, pos.y + 14};
	al_draw_spline(outerRightBottom, al_map_rgb(228,68,58),3);

	float outer0RightTop[] = {pos.x - 1, pos.y + 14, pos.x + 4, pos.y + 4, pos.x + 21, pos.y + 4,pos.x + 41, pos.y + 14}; //red
	al_draw_spline(outer0RightTop, al_map_rgb(184,0,0),0);
	float outer0RightBottom[] = {pos.x - 1, pos.y + 14, pos.x + 4, pos.y + 24, pos.x + 21, pos.y + 24 ,pos.x + 41, pos.y + 14};
	al_draw_spline(outer0RightBottom, al_map_rgb(184,0,0),0);

	float outer1RightTop[] = {pos.x, pos.y + 14, pos.x + 5, pos.y + 7, pos.x + 20, pos.y + 7 ,pos.x + 34, pos.y + 14}; //red
	al_draw_spline(outer1RightTop, al_map_rgb(228,68,58),2);
	float outer1RightBottom[] = {pos.x, pos.y + 14, pos.x + 5, pos.y + 21, pos.x + 20, pos.y + 21 ,pos.x + 34, pos.y + 14};
	al_draw_spline(outer1RightBottom, al_map_rgb(228,68,58),2);
	
	float outer2RightTop[] = {pos.x, pos.y + 14, pos.x + 5, pos.y + 9, pos.x + 20, pos.y + 9 ,pos.x + 32, pos.y + 14};  //orange
	al_draw_spline(outer2RightTop, al_map_rgb(191,208,58),2);
	float outer2RightBottom[] = {pos.x, pos.y + 14, pos.x + 5, pos.y + 19, pos.x + 20, pos.y + 19 ,pos.x + 32, pos.y + 14};
	al_draw_spline(outer2RightBottom, al_map_rgb(191,208,58),2);

	al_draw_line(pos.x + 4, pos.y + 14, pos.x + 11, pos.y + 14, al_map_rgb(255,255,255), 2); //white

	//draw extra outline
	al_draw_spline(outer1RightTop, al_map_rgb(222,0,0),0);
	al_draw_spline(outer1RightBottom, al_map_rgb(222,0,0),0);

}

/////////////////////////////////////////////
/////////////////Cheesy-poon Cord////////////

void canvas::drawHarpoonCordUp(ALLEGRO_DISPLAY *,xy pos,int cordLen)
{
	al_draw_line(pos.x+20,pos.y+4,pos.x+20,pos.y+cordLen,al_map_rgb(255,255,255),1);
}
void canvas::drawHarpoonCordDown(ALLEGRO_DISPLAY *,xy pos,int cordLen)
{
	al_draw_line(pos.x+20,pos.y+36,pos.x+20,pos.y-cordLen+40,al_map_rgb(255,255,255),1);
}
void canvas::drawHarpoonCordLeft(ALLEGRO_DISPLAY *,xy pos,int cordLen)
{
	al_draw_line(pos.x+4,pos.y+27,pos.x+cordLen,pos.y+27,al_map_rgb(255,255,255),1);
}
void canvas::drawHarpoonCordRight(ALLEGRO_DISPLAY *,xy pos,int cordLen)
{
	al_draw_line(pos.x+36,pos.y+27,pos.x-cordLen+40,pos.y+27,al_map_rgb(255,255,255),1);
}

/////////////////////////////////////////////
/////////////////Cheesy-poon Tip/////////////

void canvas::drawHarpoonTipUp   (ALLEGRO_DISPLAY *,xy pos)
{


	//draw background
	//al_draw_filled_rectangle(pos.x, pos.y, pos.x + 40, pos.y + 20, al_map_rgb(0,0,0));

		
	//start of cord
	al_draw_line(pos.x + 20, pos.y + 8, pos.x + 20, pos.y + 2, al_map_rgb(255,255,255),1);

	//draw cheesy-poof
	float cheesyPoonUp[] = {pos.x + 12, pos.y + 7, pos.x + 12, pos.y + 2, pos.x + 28, pos.y + 2, pos.x + 28, pos.y + 7};
	al_draw_spline(cheesyPoonUp, al_map_rgb(252,200,26),4);


		
}
void canvas::drawHarpoonTipDown (ALLEGRO_DISPLAY *,xy pos)
{

	//draw background
	//al_draw_filled_rectangle(pos.x, pos.y, pos.x + 40, pos.y + 40, al_map_rgb(0,0,0));
		
	//start of cord
	al_draw_line(pos.x + 20, pos.y + 32, pos.x + 20, pos.y + 38, al_map_rgb(255,255,255),1);

	//draw cheesy-poof
	float cheesyPoonDown[] = {pos.x + 12, pos.y + 33, pos.x + 12, pos.y + 38, pos.x + 28, pos.y + 38, pos.x + 28, pos.y + 33};
	al_draw_spline(cheesyPoonDown, al_map_rgb(252,200,26),4);


	////////////////////////////////////////////
}
void canvas::drawHarpoonTipLeft (ALLEGRO_DISPLAY *,xy pos)
{

	//draw background
	//al_draw_filled_rectangle(pos.x, pos.y, pos.x + 40, pos.y + 40, al_map_rgb(0,0,0));

	//start of cord
	al_draw_line(pos.x + 2, pos.y + 27, pos.x + 8, pos.y + 27, al_map_rgb(255,255,255),1);

	//draw cheesy-poof
	float cheesyPoonLeft[] = {pos.x + 7, pos.y + 19, pos.x + 2, pos.y + 19, pos.x + 2, pos.y + 35, pos.x + 7, pos.y + 35};
	al_draw_spline(cheesyPoonLeft, al_map_rgb(252,200,26),4);

	//////////////////////////////////////////
}
void canvas::drawHarpoonTipRight(ALLEGRO_DISPLAY *,xy pos)
{
	//draw background
	//al_draw_filled_rectangle(pos.x, pos.y, pos.x + 40, pos.y + 40, al_map_rgb(0,0,0));

	//start of cord
	al_draw_line(pos.x + 32, pos.y + 27, pos.x + 38, pos.y + 27, al_map_rgb(255,255,255),1);
		
	//draw cheesy-poof
	float cheesyPoonRight[] = {pos.x + 33, pos.y + 19, pos.x + 38, pos.y + 19, pos.x + 38, pos.y + 35, pos.x +33, pos.y + 35};
	al_draw_spline(cheesyPoonRight, al_map_rgb(252,200,26),4);


	//////////////////////////////////////////
}

/////////////////////////////////////////////
/////////////////Rock///////////////////////
void canvas::drawRockClosedLeft(ALLEGRO_DISPLAY *,xy pos)
{
	//coffin triangles
	al_draw_filled_triangle(pos.x + 31, pos.y + 38, pos.x + 7, pos.y + 21, pos.x + 38, pos.y + 31, al_map_rgb(105,43,0));
	al_draw_filled_triangle(pos.x + 7, pos.y + 21, pos.x + 21, pos.y + 6, pos.x + 38, pos.y + 31, al_map_rgb(105,43,0));
	al_draw_filled_triangle(pos.x + 8, pos.y + 2, pos.x + 13, pos.y + 14, pos.x + 2, pos.y + 8, al_map_rgb(105,43,0));
	al_draw_filled_triangle(pos.x + 22, pos.y + 6, pos.x + 13, pos.y + 14, pos.x + 8, pos.y + 2, al_map_rgb(105,43,0));
	al_draw_filled_triangle(pos.x + 13, pos.y + 14, pos.x + 2, pos.y + 8, pos.x + 7, pos.y + 21, al_map_rgb(105,43,0));

	//coffin outside lines
	al_draw_line(pos.x + 31, pos.y + 38, pos.x + 7, pos.y + 21, al_map_rgb(125,125,125),1);
	al_draw_line(pos.x + 7, pos.y + 21, pos.x + 2, pos.y + 8, al_map_rgb(125,125,125),1);
	al_draw_line(pos.x + 2, pos.y + 8, pos.x + 8, pos.y + 2, al_map_rgb(125,125,125),1);
	al_draw_line(pos.x + 8, pos.y + 2, pos.x + 21, pos.y + 6, al_map_rgb(125,125,125),1);
	al_draw_line(pos.x + 21, pos.y + 6, pos.x + 38, pos.y + 31, al_map_rgb(125,125,125),1);
	al_draw_line(pos.x + 38, pos.y + 31, pos.x + 31, pos.y + 38, al_map_rgb(125,125,125),1);

	//coffin cross
	al_draw_line(pos.x + 18, pos.y + 9, pos.x + 10, pos.y + 17, al_map_rgb(230,230,230),1);
	al_draw_line(pos.x + 10, pos.y + 9, pos.x + 23, pos.y + 22, al_map_rgb(230,230,230),1);
}
void canvas::drawRockClosedRight(ALLEGRO_DISPLAY *,xy pos)
{
	//coffin triangles
	al_draw_filled_triangle(pos.x + 9, pos.y + 38, pos.x + 33, pos.y + 21, pos.x + 2, pos.y + 31, al_map_rgb(105,43,0));
	al_draw_filled_triangle(pos.x + 33, pos.y + 21, pos.x + 19, pos.y + 6, pos.x + 2, pos.y + 31, al_map_rgb(105,43,0));
	al_draw_filled_triangle(pos.x + 32, pos.y + 2, pos.x + 27, pos.y + 14, pos.x + 38, pos.y + 8, al_map_rgb(105,43,0));
	al_draw_filled_triangle(pos.x + 19, pos.y + 6, pos.x + 27, pos.y + 14, pos.x + 32, pos.y + 2, al_map_rgb(105,43,0));
	al_draw_filled_triangle(pos.x + 27, pos.y + 14, pos.x + 38, pos.y + 8, pos.x + 33, pos.y + 21, al_map_rgb(105,43,0));

	//coffin outside lines
	al_draw_line(pos.x + 9, pos.y + 38, pos.x + 33, pos.y + 21, al_map_rgb(125,125,125),1);
	al_draw_line(pos.x + 33, pos.y + 21, pos.x + 38, pos.y + 8, al_map_rgb(125,125,125),1);
	al_draw_line(pos.x + 38, pos.y + 8, pos.x + 32, pos.y + 2, al_map_rgb(125,125,125),1);
	al_draw_line(pos.x + 32, pos.y + 2, pos.x + 19, pos.y + 6, al_map_rgb(125,125,125),1);
	al_draw_line(pos.x + 19, pos.y + 6, pos.x + 2, pos.y + 31, al_map_rgb(125,125,125),1);
	al_draw_line(pos.x + 2, pos.y + 31, pos.x + 9, pos.y + 38, al_map_rgb(125,125,125),1);

	//coffin cross
	al_draw_line(pos.x + 22, pos.y + 9, pos.x + 30, pos.y + 17, al_map_rgb(230,230,230),1);
	al_draw_line(pos.x + 30, pos.y + 9, pos.x + 17, pos.y + 22, al_map_rgb(230,230,230),1);

}
void canvas::drawRockOpenLeft(ALLEGRO_DISPLAY *,xy pos)
{
	//draw background
	//al_draw_filled_rectangle(pos.x, pos.y, pos.x + 40, pos.y + 40, al_map_rgb(0,0,0));

	//coffin outside lines


	//coffin triangles
	al_draw_filled_triangle(pos.x + 31, pos.y + 38, pos.x + 7, pos.y + 21, pos.x + 38, pos.y + 31, al_map_rgb(105,43,0));
	al_draw_filled_triangle(pos.x + 7, pos.y + 21, pos.x + 21, pos.y + 6, pos.x + 38, pos.y + 31, al_map_rgb(105,43,0));
	al_draw_filled_triangle(pos.x + 8, pos.y + 2, pos.x + 13, pos.y + 14, pos.x + 2, pos.y + 8, al_map_rgb(105,43,0));
	al_draw_filled_triangle(pos.x + 22, pos.y + 6, pos.x + 13, pos.y + 14, pos.x + 8, pos.y + 2, al_map_rgb(105,43,0));
	al_draw_filled_triangle(pos.x + 13, pos.y + 14, pos.x + 2, pos.y + 8, pos.x + 7, pos.y + 21, al_map_rgb(105,43,0));

	//coffin outside lines
	al_draw_line(pos.x + 31, pos.y + 38, pos.x + 7, pos.y + 21, al_map_rgb(125,125,125),1);
	al_draw_line(pos.x + 7, pos.y + 21, pos.x + 2, pos.y + 8, al_map_rgb(125,125,125),1);
	al_draw_line(pos.x + 2, pos.y + 8, pos.x + 8, pos.y + 2, al_map_rgb(125,125,125),1);
	al_draw_line(pos.x + 8, pos.y + 2, pos.x + 21, pos.y + 6, al_map_rgb(125,125,125),1);
	al_draw_line(pos.x + 21, pos.y + 6, pos.x + 38, pos.y + 31, al_map_rgb(125,125,125),1);
	al_draw_line(pos.x + 38, pos.y + 31, pos.x + 31, pos.y + 38, al_map_rgb(125,125,125),1);


	//draw coffin inside triangles
	al_draw_filled_triangle(pos.x + 31, pos.y + 35, pos.x + 8, pos.y + 18, pos.x + 35, pos.y + 32, al_map_rgb(219,59,33));  //base bottom	
	al_draw_filled_triangle(pos.x + 9, pos.y + 20, pos.x + 20, pos.y + 10, pos.x + 35, pos.y + 32, al_map_rgb(219,59,33));	//base top

	al_draw_filled_triangle(pos.x + 10, pos.y + 5, pos.x + 15, pos.y + 14, pos.x + 6, pos.y + 10, al_map_rgb(219,59,33)); //head middle
	al_draw_filled_triangle(pos.x + 21, pos.y + 10, pos.x + 15, pos.y + 14, pos.x + 10, pos.y + 5, al_map_rgb(219,59,33)); //head top
	al_draw_filled_triangle(pos.x + 16, pos.y + 15, pos.x + 6, pos.y + 10, pos.x + 9, pos.y + 20, al_map_rgb(219,59,33)); //head bottom
	al_draw_filled_circle(pos.x + 13, pos.y + 13, 4, al_map_rgb(219,59,33));


	//lid on ground and cracks
	al_draw_filled_triangle(pos.x + 22, pos.y + 38, pos.x + 2, pos.y + 38, pos.x + 2, pos.y + 22, al_map_rgb(105,43,0));

	al_draw_line(pos.x + 13, pos.y + 30, pos.x + 4, pos.y + 31, al_map_rgb(0,0,0),2);
	al_draw_line(pos.x + 4, pos.y + 31, pos.x + 10, pos.y + 35, al_map_rgb(0,0,0),2);
	al_draw_line(pos.x + 10, pos.y + 35, pos.x + 4, pos.y + 36, al_map_rgb(0,0,0),2);
	al_draw_line(pos.x + 4, pos.y + 36, pos.x + 2, pos.y + 40, al_map_rgb(0,0,0),2);

	//skeleton skull
	al_draw_filled_circle(pos.x + 15, pos.y + 14, 3, al_map_rgb(255,255,255)); // jaw
	al_draw_filled_circle(pos.x + 12, pos.y + 11, 4, al_map_rgb(255,255,255)); // cranium
	al_draw_filled_circle(pos.x + 13, pos.y + 10, 1, al_map_rgb(0,0,0)); //eyes
	al_draw_filled_circle(pos.x + 11, pos.y + 12, 1, al_map_rgb(0,0,0));
	al_draw_line(pos.x + 16, pos.y + 12, pos.x + 13, pos.y + 15, al_map_rgb(0,0,0),1); //mouth
	
	//skeleton body
	al_draw_line(pos.x + 15, pos.y + 15, pos.x + 26, pos.y + 26, al_map_rgb(255,255,255),1); //backbone
	al_draw_line(pos.x + 22, pos.y + 14, pos.x + 15, pos.y + 22, al_map_rgb(255,255,255),1); //arms
	al_draw_line(pos.x + 22, pos.y + 18, pos.x + 18, pos.y + 22, al_map_rgb(255,255,255),1); //ribs
	al_draw_line(pos.x + 24, pos.y + 20, pos.x + 20, pos.y + 24, al_map_rgb(255,255,255),1);
	al_draw_line(pos.x + 26, pos.y + 22, pos.x + 22, pos.y + 26, al_map_rgb(255,255,255),1);
	al_draw_line(pos.x + 25, pos.y + 25, pos.x + 33, pos.y + 30, al_map_rgb(255,255,255),1);	//legs
	al_draw_line(pos.x + 25, pos.y + 25, pos.x + 30, pos.y + 33, al_map_rgb(255,255,255),1);

	//////////////////////////////////////////
}
void canvas::drawRockOpenRight(ALLEGRO_DISPLAY *,xy pos)
{
	//draw background
	//al_draw_filled_rectangle(pos.x, pos.y, pos.x + 40, pos.y + 40, al_map_rgb(0,0,0));

	//coffin outside lines


	//coffin triangles
	al_draw_filled_triangle(pos.x + 9, pos.y + 38, pos.x + 33, pos.y + 21, pos.x + 2, pos.y + 31, al_map_rgb(105,43,0));
	al_draw_filled_triangle(pos.x + 33, pos.y + 21, pos.x + 19, pos.y + 6, pos.x + 2, pos.y + 31, al_map_rgb(105,43,0));
	al_draw_filled_triangle(pos.x + 32, pos.y + 2, pos.x + 27, pos.y + 14, pos.x + 38, pos.y + 8, al_map_rgb(105,43,0));
	al_draw_filled_triangle(pos.x + 19, pos.y + 6, pos.x + 27, pos.y + 14, pos.x + 32, pos.y + 2, al_map_rgb(105,43,0));
	al_draw_filled_triangle(pos.x + 27, pos.y + 14, pos.x + 38, pos.y + 8, pos.x + 33, pos.y + 21, al_map_rgb(105,43,0));

	//coffin outside lines
	al_draw_line(pos.x + 9, pos.y + 38, pos.x + 33, pos.y + 21, al_map_rgb(125,125,125),1);
	al_draw_line(pos.x + 33, pos.y + 21, pos.x + 38, pos.y + 8, al_map_rgb(125,125,125),1);
	al_draw_line(pos.x + 38, pos.y + 8, pos.x + 32, pos.y + 2, al_map_rgb(125,125,125),1);
	al_draw_line(pos.x + 32, pos.y + 2, pos.x + 19, pos.y + 6, al_map_rgb(125,125,125),1);
	al_draw_line(pos.x + 19, pos.y + 6, pos.x + 2, pos.y + 31, al_map_rgb(125,125,125),1);
	al_draw_line(pos.x + 2, pos.y + 31, pos.x + 9, pos.y + 38, al_map_rgb(125,125,125),1);


	//draw coffin inside triangles
	al_draw_filled_triangle(pos.x + 9, pos.y + 35, pos.x + 32, pos.y + 18, pos.x + 5, pos.y + 32, al_map_rgb(219,59,33));  //base bottom	
	al_draw_filled_triangle(pos.x + 31, pos.y + 20, pos.x + 20, pos.y + 10, pos.x + 5, pos.y + 32, al_map_rgb(219,59,33));	//base top

	al_draw_filled_triangle(pos.x + 30, pos.y + 5, pos.x + 25, pos.y + 14, pos.x + 34, pos.y + 10, al_map_rgb(219,59,33)); //head middle
	al_draw_filled_triangle(pos.x + 19, pos.y + 10, pos.x + 25, pos.y + 14, pos.x + 30, pos.y + 5, al_map_rgb(219,59,33)); //head top
	al_draw_filled_triangle(pos.x + 24, pos.y + 15, pos.x + 34, pos.y + 10, pos.x + 31, pos.y + 20, al_map_rgb(219,59,33)); //head bottom
	al_draw_filled_circle(pos.x + 27, pos.y + 13, 4, al_map_rgb(219,59,33));

	//lid on ground and cracks
	al_draw_filled_triangle(pos.x + 18, pos.y + 38, pos.x + 38, pos.y + 38, pos.x + 38, pos.y + 22, al_map_rgb(105,43,0));

	al_draw_line(pos.x + 27, pos.y + 30, pos.x + 36, pos.y + 31, al_map_rgb(0,0,0),2);
	al_draw_line(pos.x + 36, pos.y + 31, pos.x + 30, pos.y + 35, al_map_rgb(0,0,0),2);
	al_draw_line(pos.x + 30, pos.y + 35, pos.x + 36, pos.y + 36, al_map_rgb(0,0,0),2);
	al_draw_line(pos.x + 36, pos.y + 36, pos.x + 38, pos.y + 40, al_map_rgb(0,0,0),2);

	//skeleton skull
	al_draw_filled_circle(pos.x + 25, pos.y + 14, 3, al_map_rgb(255,255,255)); // jaw
	al_draw_filled_circle(pos.x + 28, pos.y + 11, 4, al_map_rgb(255,255,255)); // cranium
	al_draw_filled_circle(pos.x + 27, pos.y + 10, 1, al_map_rgb(0,0,0)); //eyes
	al_draw_filled_circle(pos.x + 29, pos.y + 12, 1, al_map_rgb(0,0,0));
	al_draw_line(pos.x + 24, pos.y + 12, pos.x + 27, pos.y + 15, al_map_rgb(0,0,0),1); //mouth

	//skeleton body
	al_draw_line(pos.x + 25, pos.y + 15, pos.x + 14, pos.y + 26, al_map_rgb(255,255,255),1); //backbone
	al_draw_line(pos.x + 18, pos.y + 14, pos.x + 25, pos.y + 22, al_map_rgb(255,255,255),1); //arms
	al_draw_line(pos.x + 18, pos.y + 18, pos.x + 22, pos.y + 22, al_map_rgb(255,255,255),1); //ribs
	al_draw_line(pos.x + 16, pos.y + 20, pos.x + 20, pos.y + 24, al_map_rgb(255,255,255),1);
	al_draw_line(pos.x + 14, pos.y + 22, pos.x + 18, pos.y + 26, al_map_rgb(255,255,255),1);
	al_draw_line(pos.x + 15, pos.y + 25, pos.x + 7, pos.y + 30, al_map_rgb(255,255,255),1);	//legs
	al_draw_line(pos.x + 15, pos.y + 25, pos.x + 10, pos.y + 33, al_map_rgb(255,255,255),1);


	//////////////////////////////////////////
}

/////////////////////////////////////////////
/////////////////Disembodied/////////////////

void canvas::drawMonstersDisembodied(ALLEGRO_DISPLAY *display,xy pos)
{
	int x=pos.x;
	int y=pos.y;
	//head
	float disem1[] = {x + 5, y + 15, x, y, x, y, x + 15, y + 5};
	al_draw_spline(disem1, al_map_rgb(10,59,25),1);
	float disem2[] = {x + 25, y + 5, x + 40, y, x + 40, y, x + 35, y + 15};
	al_draw_spline(disem2, al_map_rgb(10,59,25),1);
	float disem3[] = {x + 35, y + 25, x + 40, y + 40, x + 40, y + 40, x + 25, y + 35};
	al_draw_spline(disem3, al_map_rgb(10,59,25),1);
	float disem4[] = {x + 5, y + 25, x, y + 40, x, y + 40, x + 15, y + 35};
	al_draw_spline(disem4, al_map_rgb(10,59,25),1);
	//eyes
	al_draw_filled_ellipse(x + 14, y + 20, 6, 3, al_map_rgb(230,230,230));
	al_draw_filled_ellipse(x + 26, y + 20, 6, 3, al_map_rgb(230,230,230));
	al_draw_ellipse(x + 13, y + 20, 6, 3, al_map_rgb(10,59,25),1);  //outlines
	al_draw_ellipse(x + 27, y + 20, 6, 3, al_map_rgb(10,59,25),1);
	al_draw_filled_circle(x + 15, y + 20, 1, al_map_rgb(27,28,26)); // pupils
	al_draw_filled_circle(x + 25, y + 20, 1, al_map_rgb(27,28,26));
}

/////////////////////////////////////////////
/////////////////Food///////////////////////
void canvas::drawCityWok(ALLEGRO_DISPLAY *,xy pos)
{
	//chopsticks
	al_draw_line(pos.x + 20, pos.y + 25, pos.x + 28, pos.y + 5, al_map_rgb(239,235,181), 2);
	al_draw_line(pos.x + 20, pos.y + 25, pos.x + 32, pos.y + 8, al_map_rgb(239,235,181), 2);
	
	//food
	al_draw_filled_circle(pos.x + 14, pos.y + 17, 3, al_map_rgb(240,196,119)); 
	al_draw_circle(pos.x + 14, pos.y + 17, 4, al_map_rgb(60,60,60),0);
	al_draw_filled_circle(pos.x + 18, pos.y + 15, 3, al_map_rgb(250,0,0));
	al_draw_circle(pos.x + 18, pos.y + 15, 4, al_map_rgb(60,60,60),0);
	al_draw_filled_circle(pos.x + 22, pos.y + 15, 3, al_map_rgb(1,194,1));
	al_draw_circle(pos.x + 22, pos.y + 15, 4, al_map_rgb(60,60,60),0);
	al_draw_filled_circle(pos.x + 26, pos.y + 17, 3, al_map_rgb(240,196,119));
	al_draw_circle(pos.x + 26, pos.y + 17, 4, al_map_rgb(60,60,60),0);

	//basic carton
	al_draw_filled_rectangle(pos.x + 14, pos.y + 20, pos.x + 26, pos.y + 35, al_map_rgb(239,235,181)); 
	al_draw_filled_triangle(pos.x + 14, pos.y + 20, pos.x + 14, pos.y + 35, pos.x + 11, pos.y + 20, al_map_rgb(239,235,181)); 
	al_draw_filled_triangle(pos.x + 26, pos.y + 20, pos.x + 26, pos.y + 35, pos.x + 29, pos.y + 20, al_map_rgb(239,235,181)); 

	//top flaps
	al_draw_line(pos.x + 14, pos.y + 23, pos.x + 7, pos.y + 16, al_map_rgb(239,235,181), 2); 
	al_draw_line(pos.x + 26, pos.y + 23, pos.x + 33, pos.y + 16, al_map_rgb(239,235,181), 2); 

	//side flaps
	al_draw_filled_triangle(pos.x + 17, pos.y + 15, pos.x + 17, pos.y + 20, pos.x + 11, pos.y + 20, al_map_rgb(239,235,181));
	al_draw_filled_triangle(pos.x + 23, pos.y + 15, pos.x + 23, pos.y + 20, pos.x + 29, pos.y + 20, al_map_rgb(239,235,181));
	al_draw_filled_rectangle(pos.x + 17, pos.y + 15, pos.x + 23, pos.y + 20, al_map_rgb(239,235,181));


	//black/grey lines
	al_draw_line(pos.x + 11, pos.y + 23, pos.x + 29, pos.y + 23, al_map_rgb(60,60,60),0);
	al_draw_line(pos.x + 10, pos.y + 21, pos.x + 16, pos.y + 15, al_map_rgb(60,60,60),0);
	al_draw_line(pos.x + 30, pos.y + 21, pos.x + 24, pos.y + 15, al_map_rgb(60,60,60),0);
	al_draw_line(pos.x + 15, pos.y + 16, pos.x + 25, pos.y + 16, al_map_rgb(60,60,60),0);  //top of flap

	//carton drawing
	al_draw_filled_circle(pos.x + 20, pos.y + 29, 3, al_map_rgb(224,41,33));


}
void canvas::drawDrumStick(ALLEGRO_DISPLAY *,xy pos)
{
	al_draw_filled_circle(pos.x + 27, pos.y + 13, 4, al_map_rgb(187,102,19));
	al_draw_filled_circle(pos.x + 30, pos.y + 11, 3, al_map_rgb(187,102,19));
	al_draw_filled_circle(pos.x + 27, pos.y + 13, 3, al_map_rgb(187,102,19));
	al_draw_filled_circle(pos.x + 24, pos.y + 15, 3, al_map_rgb(187,102,19));
	al_draw_filled_circle(pos.x + 21, pos.y + 16, 3, al_map_rgb(187,102,19));

	//drumstick leg balls
	al_draw_filled_circle(pos.x + 6, pos.y + 27, 1, al_map_rgb(252,251,233));
	al_draw_filled_circle(pos.x + 8, pos.y + 29, 1, al_map_rgb(252,251,233));

	//drumstick leg
	al_draw_line(pos.x + 15, pos.y + 22, pos.x + 7, pos.y + 28, al_map_rgb(252,251,233), 2);

	//drumstick body
	float chickenOuterTop[] = {pos.x + 15, pos.y + 22, pos.x + 22, pos.y + 5, pos.x + 32, pos.y + 5, pos.x + 35, pos.y + 10};
	al_draw_spline(chickenOuterTop, al_map_rgb(187,102,19), 2);
	float chickenOuterBottom[] = {pos.x + 15, pos.y + 22, pos.x + 22, pos.y + 20, pos.x + 32, pos.y + 20, pos.x + 35, pos.y + 10};
	al_draw_spline(chickenOuterBottom, al_map_rgb(187,102,19), 2);

	float chickenOuterTop1[] = {pos.x + 17, pos.y + 20, pos.x + 24, pos.y + 7, pos.x + 30, pos.y + 7, pos.x + 33, pos.y + 10};
	al_draw_spline(chickenOuterTop1, al_map_rgb(123,68,14), 2);
	float chickenOuterBottom1[] = {pos.x + 17, pos.y + 20, pos.x + 24, pos.y + 20, pos.x + 30, pos.y + 20, pos.x + 33, pos.y + 10};
	al_draw_spline(chickenOuterBottom1, al_map_rgb(187,102,19), 2);


}
void canvas::drawDoubleDew(ALLEGRO_DISPLAY *,xy pos)
{

	//basic can
	al_draw_filled_ellipse(pos.x + 20, pos.y + 30, 7, 3, al_map_rgb(9,119,80)); 
	al_draw_filled_rounded_rectangle(pos.x + 12, pos.y + 10, pos.x + 28, pos.y + 30, 3, 3, al_map_rgb(9,119,80)); 

	//can top
	al_draw_filled_ellipse(pos.x + 20, pos.y + 10, 7, 4, al_map_rgb(203,210,218)); 
	al_draw_ellipse(pos.x + 20, pos.y + 10, 7, 4, al_map_rgb(0,0,0),1); 

	//top details
	al_draw_filled_ellipse(pos.x + 22, + pos.y + 10, 2, 1, al_map_rgb(0,0,0)); 

	//can graphics
	al_draw_line(pos.x + 12, pos.y + 20, pos.x + 28, pos.y + 16, al_map_rgb(220,200,220), 3); //white
	al_draw_line(pos.x + 12, pos.y + 26, pos.x + 28, pos.y + 22, al_map_rgb(205,57,45), 3); //red
	al_draw_line(pos.x + 12, pos.y + 23, pos.x + 28, pos.y + 19, al_map_rgb(41,189,69), 3);  //light green

}
void canvas::drawPotPie(ALLEGRO_DISPLAY *,xy pos)
{
	//pie top
	al_draw_filled_ellipse(pos.x + 20, pos.y + 18, 14, 8, al_map_rgb(227,230,153));

	//tray
	al_draw_filled_rounded_rectangle(pos.x + 7, pos.y + 20, pos.x + 33, pos.y + 26, 3, 3, al_map_rgb(219,218,226));
	al_draw_filled_ellipse(pos.x + 20, pos.y + 24, 13, 4, al_map_rgb(219,218,226));


	//pie crust		
	al_draw_filled_circle(pos.x + 8, pos.y + 19, 4, al_map_rgb(198,177,84));
	al_draw_filled_circle(pos.x + 14, pos.y + 20, 4, al_map_rgb(198,177,84));
	al_draw_filled_circle(pos.x + 20, pos.y + 21, 4, al_map_rgb(198,177,84));
	al_draw_filled_circle(pos.x + 26, pos.y + 20, 4, al_map_rgb(198,177,84));
	al_draw_filled_circle(pos.x + 32, pos.y + 19, 4, al_map_rgb(198,177,84));
	

	//pie slips
	al_draw_line(pos.x + 17, pos.y + 12, pos.x + 15, pos.y + 14, al_map_rgb(0,0,0),1);
	al_draw_line(pos.x + 24, pos.y + 12, pos.x + 26, pos.y + 14, al_map_rgb(0,0,0),1);
	al_draw_line(pos.x + 20, pos.y + 12, pos.x + 21, pos.y + 14, al_map_rgb(0,0,0),1);

}

////////////////////////////////////////////
///////////////Splash Screen///////////////
void canvas::displaySplashScreen(ALLEGRO_DISPLAY *display)
{
	al_clear_to_color(al_map_rgb(0,0,0));
	al_draw_text(_font24,al_map_rgb(255,255,255),205,10,ALLEGRO_ALIGN_CENTRE,"Cartman's Nightmare");
	al_draw_line(_squareWidth-2,_squareWidth-1,_squareWidth*17 + _score_panel_width+1,_squareWidth-1,al_map_rgb(255,255,255),2);							//top horizontal
	al_draw_line(_squareWidth-2,_squareWidth*17 + _squareWidth+1,_squareWidth*17 + _score_panel_width+1,_squareWidth*17 + _squareWidth+1,al_map_rgb(255,255,255),2);	//bottom horizontal			
	al_draw_line(_squareWidth-1,_squareWidth,_squareWidth-1,_squareWidth*17 + _squareWidth,al_map_rgb(255,255,255),2);										//left vertical
	al_draw_line(_squareWidth*17+1,_squareWidth,_squareWidth*17+1,_squareWidth*17 + _squareWidth,al_map_rgb(255,255,255),2);								//scoreboard left vertical
	al_draw_line(_squareWidth*17 + _score_panel_width,_squareWidth,_squareWidth*17 + _score_panel_width,_squareWidth*17 + _squareWidth,al_map_rgb(255,255,255),2);  //right vertical end
	al_draw_text(_font24,al_map_rgb(255,255,255),110, _scr_height/2,ALLEGRO_ALIGN_LEFT,"Press space to start, q to quit");

	al_flip_display();
}
void canvas::displayDigDugCaught(ALLEGRO_DISPLAY *display, int lives)
{
	al_draw_textf(_font24, al_map_rgb(224,41,33),220, _scr_height/2-20,ALLEGRO_ALIGN_LEFT,"You were captured!",lives);
	al_draw_textf(_font24, al_map_rgb(224,41,33),150, _scr_height/2+30,ALLEGRO_ALIGN_LEFT,"You have %i lives remaining.",lives);
}
void canvas::displayDigDugCrushed(ALLEGRO_DISPLAY *display, const int lives)
{

	al_draw_textf(_font24, al_map_rgb(224,41,33),220, _scr_height/2-20,ALLEGRO_ALIGN_LEFT,"You were crushed!",lives);
	al_draw_textf(_font24, al_map_rgb(224,41,33),150, _scr_height/2+30,ALLEGRO_ALIGN_LEFT,"You have %i lives remaining.",lives);

}
void canvas::displayGamePanel(ALLEGRO_DISPLAY *display,const int score,const int lives,const vector<int> highScores)
{
	al_draw_text(_font24,al_map_rgb(255,255,255),205,10,ALLEGRO_ALIGN_CENTRE,"Cartman's Nightmare");
	al_draw_textf(_font24,al_map_rgb(255,255,255),690,50,ALLEGRO_ALIGN_LEFT,"Score: %i",score);
	al_draw_text(_font24,al_map_rgb(255,255,255),690,90,ALLEGRO_ALIGN_LEFT,"Lives:");
	for(int i=0;i<lives;i++)
		drawDigDugDown(display,xy::makestruct(790+40*i,80));


	al_draw_text(_font24,al_map_rgb(255,255,255),690,200,ALLEGRO_ALIGN_LEFT,"High Scores:");
	for(int i=0;i<highScores.size();i++)
		al_draw_textf(_font24,al_map_rgb(255,255,255),690,240+i*40,ALLEGRO_ALIGN_LEFT,"%i : %i",i+1,highScores[i]);
		
}
void canvas::displayWin(ALLEGRO_DISPLAY *display,const int score)
{
	al_draw_text(_font24,al_map_rgb(255,255,255),290, _scr_height/2-20,ALLEGRO_ALIGN_LEFT,"You win!");
	al_draw_textf(_font24,al_map_rgb(255,255,255),180, _scr_height/2+30,ALLEGRO_ALIGN_LEFT,"You Scored %i points.",score);
	al_flip_display();
	al_rest(5.0);
}
void canvas::displaySplashScreenEmpty(ALLEGRO_DISPLAY *display,const int score,const int lives)
{
	al_clear_to_color(al_map_rgb(0,0,0));
	al_draw_text(_font24,al_map_rgb(255,255,255),205,10,ALLEGRO_ALIGN_CENTRE,"Cartman's Nightmare");
	al_draw_textf(_font24,al_map_rgb(255,255,255),690,50,ALLEGRO_ALIGN_LEFT,"Score: %i",score);
	al_draw_textf(_font24,al_map_rgb(255,255,255),690,90,ALLEGRO_ALIGN_LEFT,"Lives:");
	for(int i=0;i<lives;i++)
		drawDigDugDown(display,xy::makestruct(790+40*i,80));
	al_draw_line(_squareWidth-2,_squareWidth-1,_squareWidth*17 + _score_panel_width+1,_squareWidth-1,al_map_rgb(255,255,255),2);							//top horizontal
	al_draw_line(_squareWidth-2,_squareWidth*17 + _squareWidth+1,_squareWidth*17 + _score_panel_width+1,_squareWidth*17 + _squareWidth+1,al_map_rgb(255,255,255),2);	//bottom horizontal			
	al_draw_line(_squareWidth-1,_squareWidth,_squareWidth-1,_squareWidth*17 + _squareWidth,al_map_rgb(255,255,255),2);										//left vertical
	al_draw_line(_squareWidth*17+1,_squareWidth,_squareWidth*17+1,_squareWidth*17 + _squareWidth,al_map_rgb(255,255,255),2);								//scoreboard left vertical
	al_draw_line(_squareWidth*17 + _score_panel_width,_squareWidth,_squareWidth*17 + _score_panel_width,_squareWidth*17 + _squareWidth,al_map_rgb(255,255,255),2);  //right vertical end
}
void canvas::displayLevel(ALLEGRO_DISPLAY *display,const int levelCount,const int score, const int lives)
{
	al_draw_textf(_font24,al_map_rgb(255,255,255),300, _scr_height/2,ALLEGRO_ALIGN_LEFT,"Level: %i",levelCount);

	al_draw_text(_font24,al_map_rgb(255,255,255),205,10,ALLEGRO_ALIGN_CENTRE,"Cartman's Nightmare");
	al_draw_textf(_font24,al_map_rgb(255,255,255),690,50,ALLEGRO_ALIGN_LEFT,"Score: %i",score);
	al_draw_text(_font24,al_map_rgb(255,255,255),690,90,ALLEGRO_ALIGN_LEFT,"Lives:");
	for(int i=0;i<lives;i++)
		drawDigDugDown(display,xy::makestruct(790+40*i,80));

	al_flip_display();
	al_rest(2.0);
}
void canvas::displayLose(ALLEGRO_DISPLAY *display,const int score)
{
	al_draw_text(_font24,al_map_rgb(255,255,255),270, _scr_height/2-20,ALLEGRO_ALIGN_LEFT,"You Lose!");
	al_draw_textf(_font24,al_map_rgb(255,255,255),180, _scr_height/2+30,ALLEGRO_ALIGN_LEFT,"You Scored %i points.",score);
	al_flip_display();
	al_rest(5.0);
}
void canvas::displayFoodRemaining(ALLEGRO_DISPLAY *display,int& foodLeft,ALLEGRO_FONT *font24)
{
	al_draw_text(font24,al_map_rgb(255,255,255),690,490,ALLEGRO_ALIGN_LEFT,"Bonus food items:");
	drawPotPie(display,xy::makestruct(682,520));
	drawDoubleDew(display,xy::makestruct(682,560));
	drawDrumStick(display,xy::makestruct(682,600));
	drawCityWok(display,xy::makestruct(682,637));
	al_draw_text(font24,al_map_rgb(255,255,255),724,530,ALLEGRO_ALIGN_LEFT,"Pot-Pie");
	al_draw_text(font24,al_map_rgb(255,255,255),724,570,ALLEGRO_ALIGN_LEFT,"Diet Double Dew");
	al_draw_text(font24,al_map_rgb(255,255,255),724,610,ALLEGRO_ALIGN_LEFT,"KFC Chicken");
	al_draw_text(font24,al_map_rgb(255,255,255),724,652,ALLEGRO_ALIGN_LEFT,"City Wok");
	al_draw_textf(font24,al_map_rgb(255,255,255),690,690,ALLEGRO_ALIGN_LEFT,"Remaining items: %i",4-foodLeft);
}
void canvas::displayHighScore(ALLEGRO_DISPLAY *display)
{
	al_draw_text(_font24,al_map_rgb(255,255,255),170, _scr_height/2-20,ALLEGRO_ALIGN_LEFT,"You achieved a high score");
	al_draw_text(_font24,al_map_rgb(255,255,255),220, _scr_height/2+30,ALLEGRO_ALIGN_LEFT,"Congratulations!");
	al_flip_display();
}
