#pragma once
#include "GameSprite.h"
#include "cocos2d.h"
using namespace cocos2d;
#define LIFENUM 40
class GamePlayer :
	public GameSprite
{
public:
	CCMotionStreak *mystreak;
	int state;
	int type;
	float pAngle; 
	int life;//角度向量
	float v; //速度;
public:
	bool isFrozen;
public:
	GamePlayer(void);
	~GamePlayer(void);
	GamePlayer(char * s);
	void setType(int i);
	virtual void   tick();
	virtual void   setPosition(CCPoint mypoint);
	bool   iscollision(GameSprite *testsprite);
	CCMotionStreak *  getstreak();
	virtual bool   collision();
	virtual CCSize   getMySize();
	void freeze();
	void revert();
};
