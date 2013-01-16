#include "Bullettype.h"
#include "GameBullet.h"
#include <math.h>
#define pi 3.1415926
GameBullet::GameBullet(void)
{
	
}

GameBullet::~GameBullet(void)
{
}
GameBullet::GameBullet(int type)
{
	v = 3;
	switch(type)
	{
		case NORMAL_BULLET : mysprite = CCSprite::spriteWithFile("bullet.png"); 
								this->type = type;
									break;
		case BOMB_BULLET : mysprite = CCSprite::spriteWithFile("Angry.png"); 
								this->type = type;
								 v = 3.5;
									break;

		case FROZEN_BULLET : mysprite = CCSprite::spriteWithFile("ice.png"); 
								this->type = type;
								  v = 2.5;
									break;	
		default : break;
	}
	//mysprite->setAnchorPoint(ccp(0.5,0)
	vAngle = 0;	
	state = 0;
}
void GameBullet::tick()
{
	switch(type){
	case NORMAL_BULLET:
	case FROZEN_BULLET:
	case BOMB_BULLET:
	   switch(state){
	   case -1:
	      break;
	   case 0 :
	      CCPoint ownp = mysprite->getPosition();
		  float x = ownp.x + v * cos((vAngle)/180 * pi);
		  float y = ownp.y - v * sin((vAngle)/180 * pi);
		  float z = sin(vAngle);
		  float zz = cos(vAngle);
		  mysprite->setPosition(ccp(x,y));
	      break;
	   }
	   break;
	}
}
void GameBullet::setType(int mytype)
{
    type = mytype;
}
int GameBullet::getType()
{
	return type;
}
void GameBullet::setPosition(CCPoint mypoint)
{
	mysprite->setPosition(mypoint);
}
CCMotionStreak *GameBullet::getstreak()
{
	return mystreak;
}
bool GameBullet::collision(GamePlayer *testsprite)
{
	return false;
}
CCSize GameBullet::getMySize()
{
	return mysprite->getContentSize();
}
