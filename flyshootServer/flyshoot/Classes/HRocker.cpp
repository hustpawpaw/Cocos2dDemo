#include "HRocker.h"   
void HRocker::updatePos(ccTime dt){jsSprite->setPosition(ccpAdd(jsSprite->getPosition(),ccpMult(ccpSub(currentPoint, jsSprite->getPosition()),0.5))); } 
//启动摇杆 
void HRocker::Active() 
{     
	if (!active) 
	{         
	active=true;         
	schedule(schedule_selector(HRocker::updatePos));
	//添加刷新函数         
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0,false);//添加触摸委托    
	}
	else {  } 
} //解除摇杆 
void   HRocker::Inactive() 
{     
	if (active) 
	{         
	active=false;        
	 this->unschedule(schedule_selector(HRocker::updatePos));
	//删除刷新         
	CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
	//删除委托     
	}
	else {     } 
} 
//摇杆方位 
CCPoint HRocker::getDirection() 
{     
	return ccpNormalize(ccpSub(centerPoint, currentPoint)); 
} 
//摇杆力度 
float HRocker::getVelocity() 
{     
	return ccpDistance(centerPoint, currentPoint); 
} 
HRocker* HRocker::HRockerWithCenter(CCPoint aPoint ,float aRadius ,CCSprite* aJsSprite,CCSprite* aJsBg,bool _isFollowRole)
{     
	HRocker *jstick=HRocker::node();     
	jstick->initWithCenter(aPoint,aRadius,aJsSprite,aJsBg,_isFollowRole);     
	return jstick; 
} 

bool HRocker::ccTouchBegan(CCTouch* touch, CCEvent* event) 
{       
	if (!active)         
	return false;     
	this->setIsVisible(true);    
	CCPoint touchPoint = touch->locationInView(touch->view());    
	 touchPoint = CCDirector:: sharedDirector()->convertToGL(touchPoint);    
	 if(!isFollowRole)
	 {         
	 if (ccpDistance(touchPoint, centerPoint) > radius)
	 {             
	 return false;         
	 }     
	 }     
	 currentPoint = touchPoint;     
	 if(isFollowRole)
	 {         
	 centerPoint=currentPoint;         
	 jsSprite->setPosition(currentPoint);         
	 this->getChildByTag(88)->setPosition(currentPoint);     
	 }     
	 return true; 
} 
void  HRocker::ccTouchMoved(CCTouch* touch, CCEvent* event) 
{     
	CCPoint touchPoint = touch->locationInView(touch->view());     
	touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);     
if (ccpDistance(touchPoint, centerPoint) > radius)     
{         
	currentPoint =ccpAdd(centerPoint,ccpMult(ccpNormalize(ccpSub(touchPoint, centerPoint)),radius));     
}else 
{         
	currentPoint = touchPoint;     
} 
} 
void  HRocker::ccTouchEnded(CCTouch* touch, CCEvent* event) 
{     
	currentPoint = centerPoint;     
	if(isFollowRole)
	{         
	this->setIsVisible(false);     
	} 
}   
HRocker* HRocker::initWithCenter(CCPoint aPoint ,float aRadius ,CCSprite* aJsSprite,CCSprite* aJsBg,bool _isFollowRole)
{       
	isFollowRole =_isFollowRole;     
	active = false;     
	radius = aRadius;     
	if(!_isFollowRole)
	{         
		centerPoint =aPoint;     
	}
	else{         
		centerPoint =ccp(0,0);     
	}       
	currentPoint = centerPoint;     
	jsSprite = aJsSprite;     
	jsSprite->setPosition(centerPoint);     
	aJsBg->setPosition(centerPoint);     
	aJsBg->setTag(88);    
	this->addChild(aJsBg);    
	this->addChild(jsSprite);    
	if(isFollowRole)
	{         
		this->setIsVisible(false);     
	}     
	this->Active();
	//激活摇杆     
	return this; 
} 