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

#include <vector>
#include <iostream>

xy makestruct(int xpos,int ypos);


/////////////////////////////////////////////
/////////////////Tunnels/////////////////////
TEST(tunnels,oneTunnelCanBeCreated)
{
    xy testPos;
    testPos.setxy(0,0);
    tunnels tunnelArr;
    tunnelArr.addTunnel(testPos);
    EXPECT_TRUE(tunnelArr.getSize()==1);
}

TEST(tunnels,createdTunnelIsInTunnel)
{
    xy testPos;
    testPos.setxy(0,0);
    tunnels tunnelArr;
    tunnelArr.addTunnel(testPos);
    EXPECT_TRUE(tunnelArr.inTunnel(testPos));
}


/////////////////////////////////////////////
/////////////////DigDug/////////////////////
TEST(digdug,DOWNChoiceGivesCorrectMove)
{
    xy testPos;
    testPos.setxy(0,0);
    digdug dd;
	dd.setpos(testPos);
    bool keys[5]={0};
    keys[DOWN]=1; //set down to true
    dd.move(keys,10);
    xy testPosNew; testPosNew.setxy(0,10);
    EXPECT_EQ(dd.pos(),testPosNew);
}

TEST(digdug,UPChoiceGivesCorrectMove)
{
    xy testPos;
    testPos.setxy(0,10);
    digdug dd;
	dd.setpos(testPos);
    bool keys[5]={0};
    keys[UP]=1; //set down to true
    dd.move(keys,10);
    xy testPosNew; testPosNew.setxy(0,0);
    EXPECT_EQ(dd.pos(),testPosNew);
}

TEST(digdug,LEFTChoiceGivesCorrectMove)
{
    xy testPos;
    testPos.setxy(10,0);
    digdug dd;
	dd.setpos(testPos);
    bool keys[5]={0};
    keys[LEFT]=1; //set down to true
    dd.move(keys,10);
    xy testPosNew; testPosNew.setxy(0,0);
    EXPECT_EQ(dd.pos(),testPosNew);
}

TEST(digdug,RIGHTChoiceGivesCorrectMove)
{
    xy testPos;
    testPos.setxy(0,0);
    digdug dd;
	dd.setpos(testPos);
    bool keys[5]={0};
    keys[RIGHT]=1; //set down to true
    dd.move(keys,10);
    xy testPosNew; testPosNew.setxy(10,0);
    EXPECT_EQ(dd.pos(),testPosNew);
}

/////////////////////////////////////////////
/////////////////Monster/////////////////////
TEST(monster,makesCorrectMovementDecision)
{
    xy testPos;
    testPos.setxy(100,100);
    clydefrog clyde(testPos);
    vector<xy> testVec;
    testVec.push_back(testPos);
    xy testPos1; testPos1.setxy(150,100);
    testVec.push_back(testPos1);
    tunnels tunnelArr(testVec);
    xy testPos2;testPos2.setxy(300,300);
    clyde.moveDecision(tunnelArr,testPos2,50);
    clyde.move(50);
    EXPECT_EQ(clyde.pos(),testPos1);
}

TEST(monster,monstersCanDisembody)
{
	dragon drag(makestruct(1,1));
	EXPECT_FALSE(drag.isdisembodied());//expect monster is created not disembodied
	drag.disembody(makestruct(2,3)); //make him disembodied
	EXPECT_TRUE(drag.isdisembodied());
}

TEST(monster,monsterCanRembody)
{
	dragon drag(makestruct(1,1));
	drag.disembody(makestruct(2,3)); 
	drag.reembody();
	EXPECT_FALSE(drag.isdisembodied());
}

TEST(monster,canMakeVectorOfBothClydeFrogsAndDragons)//testing whether we can create a vecotr of base class monster, which will then be either a clyde frog or a dragon
{
	vector<monster*> monstVec;
	monstVec.push_back(new dragon(makestruct(1,2)));
	monstVec.push_back(new clydefrog(makestruct(1,3)));

	dragon* pDragon = dynamic_cast<dragon*>(monstVec[0]); // Attempt to convert pointer to a dragon
	EXPECT_TRUE(pDragon);

	clydefrog* pClyde = dynamic_cast<clydefrog*>(monstVec[1]);//same expecting a clyde frog now
	EXPECT_TRUE(pClyde);
}

TEST(monster,monsterMoveDecisionCorrectUP)
{
	dragon drag(makestruct(0,80));
	int step=4;
	tunnels tunnelNW;
	for (int i=0;i<=40;i++)tunnelNW.addTunnel(makestruct(0,0+i*step));//makees tunnels
	drag.moveDecision(tunnelNW,makestruct(0,0),40);//simulates dds position
	drag.move(4);
	EXPECT_EQ(drag.getDir(),UP);
}

TEST(monster,monsterMoveDecisionCorrectDOWN)
{
	dragon drag(makestruct(0,0));
	int step=4;
	tunnels tunnelNW;
	for (int i=0;i<=40;i++)tunnelNW.addTunnel(makestruct(0,0+i*step));//makees tunnels
	drag.moveDecision(tunnelNW,makestruct(0,80),40);//simulates dds position
	drag.move(4);
	EXPECT_EQ(drag.getDir(),DOWN);
}

TEST(monster,monsterMoveDecisionCorrectRIGHT)
{
	dragon drag(makestruct(0,0));
	int step=4;
	tunnels tunnelNW;
	for (int i=0;i<=40;i++)tunnelNW.addTunnel(makestruct(i*step,0));//makees tunnels
	drag.moveDecision(tunnelNW,makestruct(80,0),40);//simulates dds position
	drag.move(4);
	EXPECT_EQ(drag.getDir(),RIGHT);

}

TEST(monster,monsterMoveDecisionCorrectLEFT)
{
	dragon drag(makestruct(80,0));
	int step=4;
	tunnels tunnelNW;
	for (int i=0;i<=40;i++)tunnelNW.addTunnel(makestruct(i*step,0));//makees tunnels
	drag.moveDecision(tunnelNW,makestruct(0,0),40);//simulates dds position
	drag.move(4);
	EXPECT_EQ(drag.getDir(),LEFT);
}

TEST(monster,canBothMonstersAttack)//virtual function "attack" is defined differently for clyde frogs and dragons. We want to step through a vecotr and use the attack method.
{
	vector<monster*> monstVec;
	monstVec.push_back(new dragon(makestruct(1,2)));
	monstVec.push_back(new clydefrog(makestruct(1,2)));
	digdug dd;
	dd.setpos(makestruct(1,2));
	EXPECT_TRUE(monstVec[0]->attack(dd.pos())); //dragon attacks
	EXPECT_TRUE(monstVec[1]->attack(dd.pos())); //clyde frog attacks
}

TEST(dragon,dragonsCanKillDDWithFire)
{
	vector<monster*> monstVec;
	monstVec.push_back(new dragon(makestruct(0,2)));
	monstVec.push_back(new dragon(makestruct(40,2)));
	digdug dd;
	dd.setpos(makestruct(80,2));
	EXPECT_FALSE(monstVec[0]->attack(dd.pos())); //monster was too far away and could not reach dig dug with flames
	EXPECT_TRUE(monstVec[1]->attack(dd.pos())); //monster was close enough and is expected to kill dig dug
}

TEST(clydefrog,clydefrogCanNotKillDDWithFire)
{
	clydefrog clyde(makestruct(40,2));
	digdug dd;
	dd.setpos(makestruct(80,0));
	EXPECT_FALSE(clyde.attack(dd.pos()));//clydefrogs can only attack if dig dug is on their current block
}

TEST(monster,disembodiedMonstersCannotKill)
{
	clydefrog clyde(makestruct(40,2));
	digdug dd;
	dd.setpos(makestruct(40,2));//made at same position as clyde frog
	EXPECT_TRUE(clyde.attack(dd.pos()));
	clyde.disembody(makestruct(40,2));
	EXPECT_FALSE(clyde.attack(dd.pos()));
}

TEST(monster,harpoonedMonstersCantMove)
{
	xy startPos=makestruct(1,1);
	dragon drag(startPos);
	drag.harpooned();
	drag.move(40);
	EXPECT_TRUE(drag.pos()==startPos);
}

TEST(monster,harpoonedMonsterCanSurvive)
{
	clydefrog clyde(makestruct(50,50));
	clyde.harpooned();
	clyde.unharpooned();
	EXPECT_TRUE(clyde.is_alive());
}

TEST(monster,resetMonstersAreNoLongerDisembodied)
{
	clydefrog clyde(makestruct(0,0));
	clyde.disembody(makestruct(0,0));
	clyde.resetMons();
	EXPECT_FALSE(clyde.isdisembodied());
}

TEST(monster,monsterAnimationStateIncreasesAndCycles)
{
	dragon drag(makestruct(0,0));
	int initial=drag.getAnimCount();
	tunnels tunVec;
	for(int i=0;i<50;i++)tunVec.addTunnel(makestruct(0,i*4));
	drag.moveDecision(tunVec,makestruct(80,0),40);
	drag.move(40);
	int final = drag.getAnimCount();
	EXPECT_FALSE(final==initial);
}

/////////////////////////////////////////////
/////////////////rock////////////////////////
TEST(rock,isNearRockDetectsDDDOWN) //isNearRock is a function that stops digdug from attempting to move into the rocks position
{
	rock Rock(makestruct(0,40),1);
    digdug dd;
	dd.setpos(makestruct(0,0));
	EXPECT_EQ(Rock.isNearRock(dd.pos()),DOWN);
}

TEST(rock,isNearRockDetectsDDUP) //isNearRock is a function that stops digdug from attempting to move into the rocks position
{
	rock Rock(makestruct(0,0),1);
    digdug dd;
	dd.setpos(makestruct(0,40));
	EXPECT_EQ(Rock.isNearRock(dd.pos()),UP);
}

TEST(rock,isNearRockDetectsDDRIGHT) //isNearRock is a function that stops digdug from attempting to move into the rocks position
{
	rock Rock(makestruct(40,0),1);
    digdug dd;
	dd.setpos(makestruct(0,0));
	EXPECT_EQ(Rock.isNearRock(dd.pos()),RIGHT);
}

TEST(rock,isNearRockDetectsDDLEFT) //isNearRock is a function that stops digdug from attempting to move into the rocks position
{
	rock Rock(makestruct(0,0),1);
    digdug dd;
	dd.setpos(makestruct(40,0));
	EXPECT_EQ(Rock.isNearRock(dd.pos()),LEFT);
}

TEST(rock,rockStopsMovingIfItHitsBottom)
{
	rock Rock(makestruct(0,0),1);
	Rock.startFalling();
	Rock.stopFalling();
	EXPECT_TRUE(Rock.isBottom()); //when rock stops falling it must be at the bottom
}

TEST(rock,rockCanMoveWhenFalling)
{
	xy startPos=makestruct(0,0);
	rock Rock(startPos,1);
	Rock.startFalling();
	Rock.move(40);
	EXPECT_FALSE(Rock.pos()==startPos); //i.e rock has moved 
}

TEST(rock,rockCanNotMoveWhenNotFalling)
{
	xy startPos=makestruct(0,0);
	rock Rock(startPos,1);
	Rock.move(40);
	EXPECT_TRUE(Rock.pos()==startPos); //i.e rock shoudln't have moved	
}

///////////////////////////////////////////////
/////////////////harpoon///////////////////////
TEST(harpoon,activeHarpoonGetsLongerWhenFireUp)
{
	xy startPos=makestruct(0,0);
	harpoon Harpoon;
	Harpoon.activate(startPos);
	Harpoon.move(UP,40);
	EXPECT_EQ(Harpoon.getLength(),1);
}

TEST(harpoon,activeHarpoonGetsLongerWhenFireDOWN)
{
	xy startPos=makestruct(0,0);
	harpoon Harpoon;
	Harpoon.activate(startPos);
	Harpoon.move(DOWN,40);
	EXPECT_EQ(Harpoon.getLength(),1);
}

TEST(harpoon,activeHarpoonGetsLongerWhenFireLeft)
{
	xy startPos=makestruct(0,0);
	harpoon Harpoon;
	Harpoon.activate(startPos);
	Harpoon.move(LEFT,40);
	EXPECT_EQ(Harpoon.getLength(),1);
}

TEST(harpoon,activeHarpoonGetsLongerWhenFireRight)
{
	xy startPos=makestruct(0,0);
	harpoon Harpoon;
	Harpoon.activate(startPos);
	Harpoon.move(RIGHT,40);
	EXPECT_EQ(Harpoon.getLength(),1);
}

TEST(harpoon,canNotMoveWhileHarpooning)
{
	xy startPos=makestruct(0,0);
	harpoon Harpoon;
	Harpoon.activate(startPos);
	Harpoon.harpooning();//starts harpooning a monster
	Harpoon.move(RIGHT,40); //try move it 
	EXPECT_TRUE(Harpoon.pos()==startPos);
}

///////////////////////////////////////////////
/////////////////monsters//////////////////////
TEST(monsters,monstersOfDifferentTypesCanBeAdded)
{
	monsters monstVec;
	monstVec.addMonster(new dragon(makestruct(0,0)));
	monstVec.addMonster(new clydefrog(makestruct(0,40)));
	EXPECT_EQ(monstVec.getSize(),2);
}

TEST(monsters,monstersOfInheritedClassHaveBeenCreated)
{
	monsters monstVec;
	monstVec.addMonster(new dragon(makestruct(0,0)));
	monstVec.addMonster(new clydefrog(makestruct(0,40)));
	dragon* pDragon = dynamic_cast<dragon*>(monstVec.getithMonster(0)); // Attempt to convert pointer to a dragon
	EXPECT_TRUE(pDragon);
	pDragon = dynamic_cast<dragon*>(monstVec.getithMonster(1)); // Attempt to convert pointer to a dragon
	EXPECT_FALSE(pDragon);//second one was a clydefrog, not a dragon
	
}

TEST(monsters,bulkAttackWorksBasicCollisionHit)
{
	monsters monstVec;
	monstVec.addMonster(new dragon(makestruct(0,0)));
	monstVec.addMonster(new clydefrog(makestruct(0,40))); //he should attack dd
	monstVec.addMonster(new dragon(makestruct(100,40)));
	monstVec.addMonster(new clydefrog(makestruct(100,400)));
	digdug dd;
	dd.setpos(makestruct(0,40));
	EXPECT_TRUE(monstVec.attack(dd.pos()));
}

TEST(monsters,bulkAttackWorksBasicCollisionMisses)
{
	monsters monstVec;
	monstVec.addMonster(new dragon(makestruct(0,0)));
	monstVec.addMonster(new clydefrog(makestruct(0,300))); 
	monstVec.addMonster(new dragon(makestruct(100,40)));
	monstVec.addMonster(new clydefrog(makestruct(100,400)));
	//no monsters are near dd
	digdug dd;
	dd.setpos(makestruct(0,40));
	EXPECT_FALSE(monstVec.attack(dd.pos()));
}

TEST(monsters,bulkAttackWorksFlamesMiss)
{
	monsters monstVec;
	monstVec.addMonster(new dragon(makestruct(0,0)));//dragon misses his flames, but starts flaming
	monstVec.addMonster(new clydefrog(makestruct(0,300))); 
	monstVec.addMonster(new dragon(makestruct(100,40)));
	monstVec.addMonster(new clydefrog(makestruct(100,400)));
	digdug dd;
	dd.setpos(makestruct(40,40));
	EXPECT_FALSE(monstVec.attack(dd.pos()));
}

TEST(monsters,bulkAttackWorksFlamesHit)
{
	monsters monstVec;
	monstVec.addMonster(new dragon(makestruct(0,0)));//dragon hits with his flames
	monstVec.addMonster(new clydefrog(makestruct(0,300))); 
	monstVec.addMonster(new dragon(makestruct(100,40)));
	monstVec.addMonster(new clydefrog(makestruct(100,400)));
	digdug dd;
	dd.setpos(makestruct(40,0));
	EXPECT_TRUE(monstVec.attack(dd.pos()));
}

TEST(monsters,killedMonstersAreRemovedFromVector)
{
	monsters monstVec;
	monstVec.addMonster(new dragon(makestruct(0,0)));
	monstVec.addMonster(new clydefrog(makestruct(0,300))); 
	monstVec.addMonster(new dragon(makestruct(100,40)));
	monstVec.killMonster(1);//killed monsters are automatically deleted from the vector
	EXPECT_EQ(monstVec.getSize(),2);
}

TEST(monsters,monstersCanBeResetToStartingPositions)
{
	xy startPos1 = makestruct(160,480);
	xy startPos2 = makestruct(600,160);
	monsters monstVec;
	monstVec.addMonster(new dragon(startPos1));
	monstVec.addMonster(new dragon(startPos2));

	int step=4;
	tunnels tunnelArr;
	vector <xy> initialTunVec;
	for (int i=0;i<29;i++)tunnelArr.addTunnel(makestruct(120,164+i*step));
	for (int i=0;i<29;i++)tunnelArr.addTunnel(makestruct(484+i*step,160));
	for (int i=0;i<29;i++)tunnelArr.addTunnel(makestruct(124+i*step,480));
	for (int i=0;i<49;i++)tunnelArr.addTunnel(makestruct(520,444+i*step));
	for (int i=0;i<40;i++)tunnelArr.addTunnel(makestruct(280+i*step,360));

	digdug dd;
	dd.setpos(makestruct(360,360));
	
	monstVec.moveDecisionMonsters(tunnelArr,dd.pos(),40);
	monstVec.moveMonsters(40); //monsters have now all been moved

	monstVec.resetAllMonsts();

	EXPECT_TRUE(monstVec.getithPos(0)==startPos1);
	EXPECT_TRUE(monstVec.getithPos(1)==startPos2);
}

TEST(monsters,monstersCannotMoveOnTopOfEachOther)
{
	tunnels tunVec;
	monsters monstVec;
	xy startPos=makestruct(0,0);
	monstVec.addMonster(new dragon(startPos)); //make monsters at same positions 
	monstVec.addMonster(new dragon(startPos));
	for(int i=0;i<50;i++)tunVec.addTunnel(makestruct(0,i*4));
	monstVec.moveDecisionMonsters(tunVec,makestruct(50,0),40); //they make their descisions
	monstVec.moveMonsters(40); //they now move
	EXPECT_TRUE( (monstVec.getithPos(0)==startPos)||(monstVec.getithPos(1)==startPos));
	EXPECT_FALSE(monstVec.getithPos(0)==monstVec.getithPos(1));//we checked if either of them hadn't moved, now we need to ensure that at least one moves (else they might be stuck)
}

///////////////////////////////////////////////
/////////////////Score/Lives///////////////////
TEST(digdug,scoreCanBeIncreased)
{
	digdug dd;
	dd.setpos(makestruct(0,0));
	dd.increaseScore(500);
	EXPECT_EQ(dd.getScore(),500);
}

TEST(digdug,livesCanBeDecreased)
{
	digdug dd;
	dd.setpos(makestruct(0,0));
	dd.dead();
	EXPECT_EQ(dd.getLives(),2);//should have 2 lives left
	EXPECT_FALSE(dd.dead());//kill him again, should stil have 1 life
}

TEST(digdug,at0LivesRemainingDDDies)
{
    digdug dd;
	dd.setpos(makestruct(0,0));
	dd.dead();
	dd.dead();
	EXPECT_TRUE(dd.dead());//this should take his last life
}

TEST(food,foodTypeDoesNotRepeateIn4Cycles)
{
	fooditem Food(makestruct(0,0));
	vector<int> type;
	vector<int>::iterator it;
	for(int i=0;i<4;i++)//4 becuase we have 4 food types
	{
		type.push_back(Food.getFoodType());
		Food.changeFoodType(makestruct(0,0));
	}
	
	for(int i=0;i<type.size();i++){ //see if each of the elements is unique using the STL algorithm for searching
		it = search (type.begin()+i, type.end(), type.begin()+i+1, type.end());
		EXPECT_TRUE(it!=type.end());
	}

}

///////////////////////////////////////////////
/////////////////Level Creator/////////////////
TEST(levelCreator,digdugIsCreatedCorrectly)
{
	digdug dd;
	vector<rock_ptr> Rocks;
	monsters monstVec;
	fooditem Food(xy::makestruct(360,360));
	levelCreator Creator(1);
	tunnels tunnelArr;
	Creator.instantiateLevel(dd,monstVec,tunnelArr,Rocks,42); 
	EXPECT_EQ(dd.pos(),makestruct(360,360));
}

TEST(levelCreator,monsterPositionsAreCreatedCorrectly)
{
	digdug dd;
	vector<rock_ptr> Rocks;
	monsters monstVec;
	fooditem Food(xy::makestruct(360,360));
	levelCreator Creator(1);
	tunnels tunnelArr;
	Creator.instantiateLevel(dd,monstVec,tunnelArr,Rocks,42); 
	EXPECT_EQ(monstVec.getithPos(0),makestruct(200,640));
}

TEST(levelCreator,rockIsCreatedCorrectly)
{
	digdug dd;
	vector<rock_ptr> Rocks;
	monsters monstVec;
	fooditem Food(xy::makestruct(360,360));
	levelCreator Creator(1);
	tunnels tunnelArr;
	Creator.instantiateLevel(dd,monstVec,tunnelArr,Rocks,42); 
	EXPECT_EQ(Rocks[0]->pos(),makestruct(80,120));
}

//////////////////////////////////////////////
//////////////////////////////////////////////

xy makestruct(int xpos,int ypos) //used for our convienience in testing.
{
	xy mystruct;
	mystruct.setxy(xpos,ypos);
	return mystruct;
} 