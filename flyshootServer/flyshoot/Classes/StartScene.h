
#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"

#include "SimpleAudioEngine.h"

extern bool isMusicOn;
extern bool isEffectOn;
class StartScene : public cocos2d::CCLayer
{
public:
	virtual bool init();  

	static cocos2d::CCScene* scene();
	LAYER_NODE_FUNC(StartScene);
	StartScene(void);
	~StartScene(void);

	void menuStartCallBack(cocos2d::CCObject *pSender);
	void menuShopCallBack(cocos2d::CCObject *pSender);
	void menuOptionsCallBack(cocos2d::CCObject *pSender);
	void menuHelpCallBack(cocos2d::CCObject *pSender);
	void menuExitCallBack(cocos2d::CCObject *pSender);
	void optionsBackCallBack(cocos2d::CCObject *pSender);
	void optionsMusicCallBack(cocos2d::CCObject *pSender);
	void optionsSoundCallBack(cocos2d::CCObject *pSender);
	void modePracticeCallBack(cocos2d::CCObject *pSender);
	void modeFightCallBack(cocos2d::CCObject *pSender);
	void modeFreeforallCallBack(cocos2d::CCObject *pSender);
	void modeBackCallBack(cocos2d::CCObject *pSender);
	void exitYesCallBack(cocos2d::CCObject *pSender);
	void exitNoCallBack(cocos2d::CCObject *pSender);
	void createHostCallBack(cocos2d::CCObject *pSender);
	void selectHostCallBack(cocos2d::CCObject *pSender);
	void hostItemCallBack(cocos2d::CCObject *pSender);
	void hostBackCallBack(cocos2d::CCObject *pSender);
	//void createHostOKCallBack(cocos2d::CCObject *pSender);
	//void createHostBackCallBack(cocos2d::CCObject *pSender);
	void prePageCallBack(cocos2d::CCObject *pSender);
	void nextPageCallBack(cocos2d::CCObject *pSender);
	void selectHostBackCallBack(cocos2d::CCObject *pSender);
	void waitBackCallBack(cocos2d::CCObject *pSender);
	void helpBackCallBack(cocos2d::CCObject *pSender);
	//void dialogAboutCallBack(cocos2d::CCObject *pSender);
	//void menuSlidedown();
	//void menuSlideup();
	void  update(cocos2d::ccTime dt);

	virtual void keyBackClicked();

	//virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    //virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	cocos2d::CCMenu * menu;
	cocos2d::CCSprite *optionsBg;
	cocos2d::CCMenu* optionMenu;
	cocos2d::CCSprite *selectBg;
	cocos2d::CCMenu* selectMenu;
	cocos2d::CCSprite *exitBg;
	cocos2d::CCMenu*   exitMenu;
	cocos2d::CCSprite *hostBg;
	cocos2d::CCMenu* hostMenu;
	//cocos2d::CCSprite *createHostBg;
	//cocos2d::CCMenu* createHostMenu;
    cocos2d::CCSprite *selectHostBg;
	cocos2d::CCMenu* selectHostMenu;
	cocos2d::CCSprite *waitBg;
	cocos2d::CCMenu* waitMenu;
	cocos2d::CCSprite *helpBg;
	cocos2d::CCMenu* helpMenu;
	//cocos2d::CCSprite *menuBg;
	//cocos2d::CCPoint menuOrigin;
//	cocos2d::CCPoint menuBgOrigin;
	//cocos2d::CCSprite *aboutBg;
	//cocos2d::CCMenuItemImage *aboutOK;
	//cocos2d::CCMenu * aboutMenu;
	cocos2d::CCSize winSize;
	//cocos2d::CCPoint aboutBgOrigin ;
	//cocos2d::CCPoint aboutMenuOrigin;
	//CCMenu *menu1;

	cocos2d::CCPoint m_tBeginPos;
    cocos2d::CCMenu* m_pItmeMenu;
	int page;
	int allPage;
	//bool flag;
};


#endif  // __HELLOWORLD_SCENE_H__
