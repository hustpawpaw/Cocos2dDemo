#pragma once
#include "GameSprite.h"
#include "GameSprite.h"
#include "GameBullet.h"
#include "cocos2d.h"
using namespace cocos2d;
class GameEnemy :
	public GameSprite
{
private:
	CCMotionStreak *mystreak;
	CCActionInterval*  bezierTo1;
	CCActionInterval*  actionTo1;
	CCActionInterval*  actionTo2;
	CCActionInterval*  actionTo3;
	ccBezierConfig bezier1;
	ccBezierConfig bezier2;
	short bullettick;
	short type;
public:
	bool isFrozen;
public:
	GameEnemy(void);
	~GameEnemy(void);
	GameEnemy(char * s);
	void setDead();
	void restart();
	virtual void tick();
	virtual void setPosition(CCPoint mypoint);
	bool iscollision(GameSprite *testsprite);
	CCMotionStreak *  getstreak();
	void chooseflytype();
	int getBulletTick();
	virtual bool collision(GamePlayer * testsprite);
	virtual CCSize   getMySize();
	bool collisionwithbullet(GameBullet *testsprite);
	void freeze();
	void revert();
};
