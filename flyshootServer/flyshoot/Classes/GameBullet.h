#pragma once
#include "GameSprite.h"
#include "GamePlayer.h"
#include "cocos2d.h"
using namespace cocos2d;

class GameBullet :
	public GameSprite
{
public:
	CCMotionStreak *mystreak;
	int type;
	float vAngle; //角度向量
	float v; //速度;
public:
	GameBullet(void);
	~GameBullet(void);
	GameBullet(int type);
	virtual void  tick();
	virtual void  setPosition(CCPoint mypoint);
	CCMotionStreak * getstreak();
	void  setType(int mytype);
	int  getType();
	virtual bool  collision(GamePlayer * testsprite);
	virtual CCSize  getMySize();
};
