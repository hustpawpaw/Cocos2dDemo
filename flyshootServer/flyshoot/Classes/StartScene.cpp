//////////////////////////////////////////////////////////////////////////
//	
//////////////////////////////////////////////////////////////////////////
#include "StartScene.h"
#include "MapScene.h"
//#include "PlayScene.h"
#include "res.h"
//#include "func.h"
#include "FlymeHost.hpp"
using namespace cocos2d;

enum
{
	MAX_COUNT = 15,
	LINE_SPACE = 40,
	kItemTagBasic = 5432,
};

static CCPoint s_tCurPos = CCPointZero;

/*const std::string testsName[total] = 
{
	"Bug-350",
	"Bug-422",
	"Bug-458"
};*/
/*const std::string testsName[total] = 
{
	"Bug-350",
	"Bug-422",
	"Bug-458",
	"Bug-624",
	"Bug-886",
	"Bug-899",
	"Bug-914",
	"Bug-1159",
	"Bug-1174",
	"Bug-350",
	"Bug-422",
	"Bug-458",
	"Bug-624",
	"Bug-886",
	"Bug-899"
};*/

CCScene* StartScene::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::node();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		StartScene *layer = StartScene::node();
		CC_BREAK_IF(! layer);
		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

bool StartScene::init()
{
	bool bRet = false;
	isServer = false;
    isClient = false;
    start  = false;
	//flag = false;
	do 
	{

		//背景
		//数据
		scheduleUpdate();

		this->setIsKeypadEnabled(true);
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCSprite * mainBg = CCSprite::spriteWithFile(menu_main);
		mainBg->setPosition(ccp(winSize.width/2,winSize.height/2));
		this->addChild(mainBg);

		//菜单项
		CCMenuItemImage *start = CCMenuItemImage::itemFromNormalImage(
			menu_start,
			menu_start,
			this,
			menu_selector(StartScene::menuStartCallBack)
			);
		start->setPosition(ccp(winSize.width/2,200));

		CCMenuItemImage *shop = CCMenuItemImage::itemFromNormalImage(
			menu_shop,
			menu_shop,
			this,
			menu_selector(StartScene::menuShopCallBack)
			);
		shop->setPosition(ccp(75,405));

		CCMenuItemImage *options = CCMenuItemImage::itemFromNormalImage(
			menu_options,
			menu_options,
			this,
			menu_selector(StartScene::menuOptionsCallBack)
			);
		options->setPosition(ccp(725,405));

		CCMenuItemImage *help = CCMenuItemImage::itemFromNormalImage(
			menu_help,
			menu_help,
			this,
			menu_selector(StartScene::menuHelpCallBack)
			);
		help->setPosition(ccp(75,75));

		CCMenuItemImage *exit = CCMenuItemImage::itemFromNormalImage(
			menu_exit,
			menu_exit,
			this,
			menu_selector(StartScene::menuExitCallBack)
			);
		exit->setPosition(ccp(725,75));
		menu  = CCMenu::menuWithItems(start,shop,options,help,exit,NULL);
		menu->setPosition(CCPointZero);
		this->addChild(menu);



		//动画
		//雪花
		CCParticleGalaxy* m_emitter = CCParticleGalaxy::node();
		m_emitter->retain();
		m_emitter->setPosition(CCPointMake( winSize.width/2,320 ));
		this->addChild(m_emitter, 10);



		CCPoint p = m_emitter->getPosition();
		m_emitter->setPosition( CCPointMake( p.x, p.y) );

		m_emitter->setLife(4);

		m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage(snow) );
		bRet = true;
	} while (0);
	return bRet;
}
StartScene::StartScene(void)
{

}

StartScene::~StartScene(void)
{
}

void  StartScene::update(cocos2d::ccTime dt)
{
	if(isServer&&start)
	{
		//switch to playScene 
		 CCDirector *pDirector = CCDirector::sharedDirector();
		 pDirector->setOpenGLView(&CCEGLView::sharedOpenGLView());
		 std::string ip = "127.0.0.1";
		 CCScene *pScene = MapScene::scene('S', ip);
	//开始游戏， 'S'为server  'C'为Client  'P' 为practice.都为大写字母。 其中ip只在client时才有作用。 其他类型下可以随意设置。
		 pDirector->replaceScene(pScene);
		 start = false;
	}
	if(isClient&&start)
	{
		//switch to playScene with hostIP
		 CCDirector *pDirector = CCDirector::sharedDirector();
		 pDirector->setOpenGLView(&CCEGLView::sharedOpenGLView());
		 std::string ip = hostIp;
		 CCScene *pScene = MapScene::scene('C', ip);
	//开始游戏， 'S'为server  'C'为Client  'P' 为practice.都为大写字母。 其中ip只在client时才有作用。 其他类型下可以随意设置。
    // run
		pDirector->replaceScene(pScene);
		start = false;
	}
}

void StartScene::menuStartCallBack(cocos2d::CCObject *pSender)
{
	winSize = CCDirector::sharedDirector()->getWinSize();
	menu->setIsVisible(false);
	selectBg = CCSprite::spriteWithFile(selectmode_bg);
	selectBg->setPosition(ccp(400,200));
	this->addChild(selectBg);
	CCMenuItemImage *practice = CCMenuItemImage::itemFromNormalImage(
		button_practice,
		button_practice_,
		this,
		menu_selector(StartScene::modePracticeCallBack)
		);
	practice->setPosition(ccp(400,350));

	CCMenuItemImage *fight = CCMenuItemImage::itemFromNormalImage(
		button_fight,
		button_fight_,
		this,
		menu_selector(StartScene::modeFightCallBack)
		);
	fight->setPosition(ccp(400,300));

	CCMenuItemImage *freeforall = CCMenuItemImage::itemFromNormalImage(
		button_freeforall,
		button_freeforall_,
		this,
		menu_selector(StartScene::modeFreeforallCallBack)
		);
	freeforall->setPosition(ccp(400,240));

	CCMenuItemImage *back = CCMenuItemImage::itemFromNormalImage(
		button_back,
		button_back,
		this,
		menu_selector(StartScene::modeBackCallBack)
		);
	back->setPosition(ccp(400,180));
	selectMenu  = CCMenu::menuWithItems(practice,fight,freeforall,back,NULL);
	selectMenu->setPosition(CCPointZero);
	this->addChild(selectMenu);
	//CCDirector::sharedDirector()->replaceScene(PlayScene::scene());

	selectBg->setPosition(ccp(selectBg->getPosition().x,menu->getPosition().y+winSize.height));
	selectBg->runAction( 
		CCEaseElasticOut::actionWithAction(
		CCMoveTo::actionWithDuration(2, ccp(400,200)), 0.35f
		) 
		);

	selectMenu->setPosition(ccp(selectMenu->getPosition().x,selectMenu->getPosition().y+winSize.height));
	selectMenu->runAction( 
		CCEaseElasticOut::actionWithAction(
		CCMoveTo::actionWithDuration(2, CCPointZero), 0.35f
		)
		);
}

void StartScene::menuShopCallBack(cocos2d::CCObject *pSender)
{

}

void StartScene::menuOptionsCallBack(cocos2d::CCObject *pSender)
{
	winSize = CCDirector::sharedDirector()->getWinSize();
	menu->setIsVisible(false);
	optionsBg = CCSprite::spriteWithFile(options_bg);
	optionsBg->setPosition(ccp(500,240));
	this->addChild(optionsBg);

	CCMenuItemToggle *music;
	if(isMusicOn)
	{
	    music = CCMenuItemToggle::itemWithTarget(	this, 
		menu_selector(StartScene::optionsMusicCallBack),
		CCMenuItemImage::itemFromNormalImage(button_on,button_off),
		CCMenuItemImage::itemFromNormalImage(button_off,button_on),
		NULL);
	}
	else
	{
		music = CCMenuItemToggle::itemWithTarget(	this, 
		menu_selector(StartScene::optionsMusicCallBack),
		CCMenuItemImage::itemFromNormalImage(button_off,button_on),
		CCMenuItemImage::itemFromNormalImage(button_on,button_off),
		NULL);
	}
	//CCMenuItemFont::itemFromString( "On" ),
	//CCMenuItemFont::itemFromString( "Off"),
	//NULL );
	music->setPosition(ccp(500,310));

	CCMenuItemToggle *sound;
	if(isEffectOn)
	{
	   sound = CCMenuItemToggle::itemWithTarget(	this, 
		menu_selector(StartScene::optionsSoundCallBack),
		CCMenuItemImage::itemFromNormalImage(button_on,button_off),
		CCMenuItemImage::itemFromNormalImage(button_off,button_on),
		NULL);
	}
	else
	{
		sound = CCMenuItemToggle::itemWithTarget(	this, 
		menu_selector(StartScene::optionsSoundCallBack),
		CCMenuItemImage::itemFromNormalImage(button_off,button_on),
		CCMenuItemImage::itemFromNormalImage(button_on,button_off),
		NULL);
	}
	sound->setPosition(ccp(500,250));

	CCMenuItemImage *back = CCMenuItemImage::itemFromNormalImage(
		button_back,
		button_back,
		this,
		menu_selector(StartScene::optionsBackCallBack)
		);
	back->setPosition(ccp(400,150));
	optionMenu  = CCMenu::menuWithItems(music,sound,back,NULL);
	optionMenu->setPosition(CCPointZero);
	this->addChild(optionMenu);

	optionsBg->setPosition(ccp(optionsBg->getPosition().x-winSize.width/2,optionsBg->getPosition().y));
	optionsBg->runAction( 
		CCEaseElasticOut::actionWithAction(
		CCMoveTo::actionWithDuration(2, ccp(500,240)), 0.35f
		) 
		);
	optionMenu->setPosition(ccp(optionMenu->getPosition().x-winSize.width/2,0));
	optionMenu->runAction( 
		CCEaseElasticOut::actionWithAction(
		CCMoveTo::actionWithDuration(2, CCPointZero), 0.35f
		) 
		);
}

void StartScene::menuHelpCallBack(cocos2d::CCObject *pSender)
{
	
	winSize = CCDirector::sharedDirector()->getWinSize();
	menu->setIsVisible(false);
	helpBg = CCSprite::spriteWithFile(helpCotent_bg);
	helpBg->setPosition(ccp(winSize.width/2,winSize.height/2));
	this->addChild(helpBg);

	CCMenuItemImage *back = CCMenuItemImage::itemFromNormalImage(
		button_back,
		button_back,
		this,
		menu_selector(StartScene::helpBackCallBack)
		);
	back->setPosition(ccp(700,50));
	helpMenu  = CCMenu::menuWithItems(back,NULL);
	helpMenu->setPosition(CCPointZero);
	this->addChild(helpMenu);
}

void StartScene::helpBackCallBack(cocos2d::CCObject *pSender)
{
	helpBg->setIsVisible(false);
	helpMenu->setIsVisible(false);
	menu->setIsVisible(true);
}

void StartScene::modePracticeCallBack(cocos2d::CCObject *pSender)
{
		 CCDirector *pDirector = CCDirector::sharedDirector();
		 pDirector->setOpenGLView(&CCEGLView::sharedOpenGLView());
		 std::string ip = "127.0.0.1";
		 CCScene *pScene = MapScene::scene('P', ip);
	//开始游戏， 'S'为server  'C'为Client  'P' 为practice.都为大写字母。 其中ip只在client时才有作用。 其他类型下可以随意设置。
		 pDirector->replaceScene(pScene);
		 start = false;
}

void StartScene::modeFightCallBack(cocos2d::CCObject *pSender)
{
	selectBg->setIsVisible(false);
	selectMenu->setIsVisible(false);
	winSize = CCDirector::sharedDirector()->getWinSize();
	hostBg = CCSprite::spriteWithFile(selectmode_bg);
	hostBg->setPosition(ccp(400,200));
	this->addChild(hostBg);
	CCMenuItemImage *createHost = CCMenuItemImage::itemFromNormalImage(
		button_createhost,
		button_createhost,
		this,
		menu_selector(StartScene::createHostCallBack)
		);
	createHost->setPosition(ccp(400,320));

	CCMenuItemImage *selectHost = CCMenuItemImage::itemFromNormalImage(
		button_selecthost,
		button_selecthost,
		this,
		menu_selector(StartScene::selectHostCallBack)
		);
	selectHost->setPosition(ccp(400,250));

	CCMenuItemImage *back = CCMenuItemImage::itemFromNormalImage(
		button_back,
		button_back,
		this,
		menu_selector(StartScene::hostBackCallBack)
		);
	back->setPosition(ccp(400,180));
	hostMenu  = CCMenu::menuWithItems(createHost,selectHost,back,NULL);
	hostMenu->setPosition(CCPointZero);
	this->addChild(hostMenu);
	//CCDirector::sharedDirector()->replaceScene(PlayScene::scene());

	/*selectBg->setPosition(ccp(selectBg->getPosition().x,menu->getPosition().y+winSize.height));
	selectBg->runAction( 
	CCEaseElasticOut::actionWithAction(
	CCMoveTo::actionWithDuration(2, ccp(400,200)), 0.35f
	) 
	);

	selectMenu->setPosition(ccp(selectMenu->getPosition().x,selectMenu->getPosition().y+winSize.height));
	selectMenu->runAction( 
	CCEaseElasticOut::actionWithAction(
	CCMoveTo::actionWithDuration(2, CCPointZero), 0.35f
	)
	);*/
}

void StartScene::createHostCallBack(cocos2d::CCObject *pSender)
{
	startServer();
	hostBg->setIsVisible(false);
	hostMenu->setIsVisible(false);
	winSize = CCDirector::sharedDirector()->getWinSize();
	waitBg = CCSprite::spriteWithFile(wait_bg);
	waitBg->setPosition(ccp(400,200));
	this->addChild(waitBg);

	CCMenuItemImage *back = CCMenuItemImage::itemFromNormalImage(
		button_back,
		button_back,
		this,
		menu_selector(StartScene::waitBackCallBack)
		);
	back->setPosition(ccp(400,160));
	waitMenu  = CCMenu::menuWithItems(back,NULL);
	waitMenu->setPosition(CCPointZero);
	this->addChild(waitMenu);
	/*hostBg->setIsVisible(false);
	hostMenu->setIsVisible(false);
	winSize = CCDirector::sharedDirector()->getWinSize();
	createHostBg = CCSprite::spriteWithFile(inputname_bg);
	createHostBg->setPosition(ccp(400,200));
	this->addChild(createHostBg);


	CCMenuItemImage *OK = CCMenuItemImage::itemFromNormalImage(
	button_OK,
	button_OK,
	this,
	menu_selector(StartScene::createHostOKCallBack)
	);
	OK->setPosition(ccp(320,200));

	CCMenuItemImage *back = CCMenuItemImage::itemFromNormalImage(
	button_back,
	button_back,
	this,
	menu_selector(StartScene::createHostBackCallBack)
	);
	back->setPosition(ccp(450,200));
	createHostMenu  = CCMenu::menuWithItems(OK,back,NULL);
	createHostMenu->setPosition(CCPointZero);
	this->addChild(createHostMenu);*/
}

void StartScene::waitBackCallBack(cocos2d::CCObject *pSender)
{
	isServer = false;
	waitBg->setIsVisible(false);
	waitMenu->setIsVisible(false);
	hostBg->setIsVisible(true);
	hostMenu->setIsVisible(true);
}

/*void StartScene::createHostOKCallBack(cocos2d::CCObject *pSender)
{

}

void StartScene::createHostBackCallBack(cocos2d::CCObject *pSender)
{
createHostBg->setIsVisible(false);
createHostMenu->setIsVisible(false);
hostBg->setIsVisible(true);
hostMenu->setIsVisible(true);
}*/


void StartScene::selectHostCallBack(cocos2d::CCObject *pSender)
{
	//flag = true;
	startClient();
	page = 0;
	allPage = total/3;
	hostBg->setIsVisible(false);
	hostMenu->setIsVisible(false);
	winSize = CCDirector::sharedDirector()->getWinSize();
	selectHostBg = CCSprite::spriteWithFile(selecthostwindow_bg);
	selectHostBg->setPosition(ccp(400,200));
	this->addChild(selectHostBg);

	CCSize s = CCDirector::sharedDirector()->getWinSize();
	m_pItmeMenu = CCMenu::menuWithItems(NULL);
	CCMenuItemFont::setFontName("Arial");
	CCMenuItemFont::setFontSize(24);
	int temp;

	if(total<3)
	{
		temp = total;
	}
	else
	{
		temp = 3;
	}
	for (int i = 0; i < temp; ++i)
	{
		CCMenuItemFont* pItem = CCMenuItemFont::itemFromString(ips[i], this,
			menu_selector(StartScene::hostItemCallBack));
		//menu_selector(BugsTestMainLayer::menuCallback));
		//pItem->setPosition(ccp(s.width / 2, s.height - (i + 1) * LINE_SPACE));
		pItem->setPosition(ccp(s.width / 2, 360 - (i + 1) * LINE_SPACE));
		/*if(pItem->getPosition().y<240)
		{
			pItem->setIsVisible(false);
		}*/
		m_pItmeMenu->addChild(pItem, kItemTagBasic + i, kItemTagBasic + i);
	}

	m_pItmeMenu->setPosition(s_tCurPos);
	addChild(m_pItmeMenu);
	//setIsTouchEnabled(true);
	CCMenuItemImage *prePage = CCMenuItemImage::itemFromNormalImage(
		button_left,
		button_left,
		this,
		menu_selector(StartScene::prePageCallBack)
		);
	prePage->setPosition(ccp(250,280));

	CCMenuItemImage *nextPage = CCMenuItemImage::itemFromNormalImage(
		button_right,
		button_right,
		this,
		menu_selector(StartScene::nextPageCallBack)
		);
	nextPage->setPosition(ccp(570,280));

	CCMenuItemImage *back = CCMenuItemImage::itemFromNormalImage(
		button_back,
		button_back,
		this,
		menu_selector(StartScene::selectHostBackCallBack)
		);
	back->setPosition(ccp(400,200));
	selectHostMenu  = CCMenu::menuWithItems(prePage,nextPage,back,NULL);
	selectHostMenu->setPosition(CCPointZero);
	this->addChild(selectHostMenu);
}
void StartScene::prePageCallBack(cocos2d::CCObject *pSender)
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	page = page--;
	int temp;
	if((page+1)*3 > total)
	{
		temp = total;
	}
	else
	{
		temp = (page+2)*3;
	}
	if(page >= 0)
	{
		for (int i = (page+1)*3; i < temp; ++i)
		{
			int k = i + kItemTagBasic;
		    m_pItmeMenu->getChildByTag(k)->setIsVisible(false);
		}
		for (int i = page*3; i < page*3+3; ++i)
		{
			int k = i + kItemTagBasic;
		    m_pItmeMenu->getChildByTag(k)->setIsVisible(true);
			/*CCMenuItemFont* pItem = CCMenuItemFont::itemFromString(testsName[i].c_str(), this,NULL);
			//menu_selector(BugsTestMainLayer::menuCallback));
			//pItem->setPosition(ccp(s.width / 2, s.height - (i + 1) * LINE_SPACE));
			pItem->setPosition(ccp(s.width / 2, 360 - (4-temp+i) * LINE_SPACE));
			/*if(pItem->getPosition().y<240)
			{
			pItem->setIsVisible(false);
			}
			m_pItmeMenu->addChild(pItem, kItemTagBasic + i, kItemTagBasic + i);*/
		}
	}
	else 
	{
		page = 0;
	}
}
void StartScene::nextPageCallBack(cocos2d::CCObject *pSender)
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	page = page++;
	int temp;
	if(page*3>total)
	{
		temp = total;
	}
	else
	{
		temp = page*3+3;
	}
	if(page >= allPage)
	{
		page = allPage - 1;
	}
	else
	{
		for(int i = (page-1)*3;i<page*3;++i)
		{
			int k = i + kItemTagBasic;
		    m_pItmeMenu->getChildByTag(k)->setIsVisible(false);
		}
		for (int i = page*3; i < temp; ++i)
		{
			int k = i + kItemTagBasic;
			if(m_pItmeMenu->getChildByTag(k)==NULL)
			{
				CCMenuItemFont* pItem = CCMenuItemFont::itemFromString(ips[i], this,
					menu_selector(StartScene::hostItemCallBack));
				//menu_selector(BugsTestMainLayer::menuCallback));
				//pItem->setPosition(ccp(s.width / 2, s.height - (i + 1) * LINE_SPACE));
				pItem->setPosition(ccp(s.width / 2, 360 - (4-temp + i) * LINE_SPACE));
				/*if(pItem->getPosition().y<240)
			{
			pItem->setIsVisible(false);
			}*/
			m_pItmeMenu->addChild(pItem, kItemTagBasic + i, kItemTagBasic + i);
			}
			else
			{
				m_pItmeMenu->getChildByTag(k)->setIsVisible(true);
			}
		}
	}
}

void StartScene::hostItemCallBack(cocos2d::CCObject *pSender)
{
	CCMenuItemFont* pItem = (CCMenuItemFont*)pSender;    
	number = pItem->getZOrder() - kItemTagBasic;
}
/*void StartScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*)(*it);

	m_tBeginPos = touch->locationInView( touch->view() );	
	m_tBeginPos = CCDirector::sharedDirector()->convertToGL( m_tBeginPos );
}*/

/*void StartScene::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*)(*it);

	CCPoint touchLocation = touch->locationInView( touch->view() );	
	touchLocation = CCDirector::sharedDirector()->convertToGL( touchLocation );
	float nMoveY = touchLocation.y - m_tBeginPos.y;

	CCPoint curPos  = m_pItmeMenu->getPosition();
	CCPoint nextPos = ccp(curPos.x, curPos.y + nMoveY);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	if (nextPos.y < 0.0f)
	{
		m_pItmeMenu->setPosition(CCPointZero);
		return;
	}

	if (nextPos.y > ((total + 1)* LINE_SPACE - winSize.height))
	{
		m_pItmeMenu->setPosition(ccp(0, ((total + 1)* LINE_SPACE - winSize.height)));
		return;
	}

	m_pItmeMenu->setPosition(nextPos);
	m_tBeginPos = touchLocation;
	s_tCurPos   = nextPos;

}*/

void StartScene::selectHostBackCallBack(cocos2d::CCObject *pSender)
{
	isClient = false;
	selectHostBg->setIsVisible(false);
	selectHostMenu->setIsVisible(false);
	m_pItmeMenu->setIsVisible(false);
	hostBg->setIsVisible(true);
	hostMenu->setIsVisible(true);
}

void StartScene::hostBackCallBack(cocos2d::CCObject *pSender)
{
	hostBg->setIsVisible(false);
	hostMenu->setIsVisible(false);
	selectBg->setIsVisible(true);
	selectMenu->setIsVisible(true);
}


void StartScene::modeFreeforallCallBack(cocos2d::CCObject *pSender)
{

}

void StartScene::modeBackCallBack(cocos2d::CCObject *pSender)
{
	menu->setIsVisible(true);
	selectBg->runAction( 
		CCEaseElasticOut::actionWithAction(
		CCMoveTo::actionWithDuration(2, ccp(selectBg->getPosition().x,selectBg->getPosition().y+winSize.height)), 0.35f
		) 
		);
	selectMenu->runAction( 
		CCEaseElasticOut::actionWithAction(
		CCMoveTo::actionWithDuration(2, ccp(selectMenu->getPosition().x,selectMenu->getPosition().y+winSize.height)), 0.35f
		) 
		);
}

void StartScene::optionsBackCallBack(cocos2d::CCObject *pSender)
{
	menu->setIsVisible(true);
	optionsBg->runAction( 
		CCEaseElasticOut::actionWithAction(
		CCMoveTo::actionWithDuration(2, ccp(optionsBg->getPosition().x-winSize.width,optionsBg->getPosition().y)), 0.35f
		) 
		);
	optionMenu->runAction( 
		CCEaseElasticOut::actionWithAction(
		CCMoveTo::actionWithDuration(2, ccp(optionMenu->getPosition().x-winSize.width,0)), 0.35f
		) 
		);
}

void StartScene::optionsMusicCallBack(cocos2d::CCObject *pSender)
{
	if(isMusicOn)
	{
		isMusicOn = false;
	}
	else
	{
		isMusicOn = true;
	}
}

void StartScene::optionsSoundCallBack(cocos2d::CCObject *pSender)
{
	if(isEffectOn)
	{
		isEffectOn = false;
	}
	else
	{
		isEffectOn = true;
	}
}

void StartScene::exitYesCallBack(cocos2d::CCObject *pSender)
{
	CCDirector::sharedDirector()->end();
}

void StartScene::exitNoCallBack(cocos2d::CCObject *pSender)
{
	menu->setIsVisible(true);
	exitBg->runAction( 
		CCEaseElasticOut::actionWithAction(
		CCMoveTo::actionWithDuration(2, ccp(exitBg->getPosition().x-winSize.width,exitBg->getPosition().y)), 0.35f
		) 
		);
	exitMenu->runAction( 
		CCEaseElasticOut::actionWithAction(
		CCMoveTo::actionWithDuration(2, ccp(exitMenu->getPosition().x-winSize.width,0)), 0.35f
		) 
		);
}

void StartScene::menuExitCallBack(cocos2d::CCObject *pSender)
{
	winSize = CCDirector::sharedDirector()->getWinSize();
	menu->setIsVisible(false);
	exitBg = CCSprite::spriteWithFile(exit_bg);
	exitBg->setPosition(ccp(400,240));
	this->addChild(exitBg);

	CCMenuItemImage *yes = CCMenuItemImage::itemFromNormalImage(
		button_yes,
		button_yes,
		this,
		menu_selector(StartScene::exitYesCallBack)
		);
	yes->setPosition(ccp(340,200));

	CCMenuItemImage *no = CCMenuItemImage::itemFromNormalImage(
		button_no,
		button_no,
		this,
		menu_selector(StartScene::exitNoCallBack)
		);
	no->setPosition(ccp(470,200));

	exitMenu  = CCMenu::menuWithItems(yes,no,NULL);
	exitMenu->setPosition(CCPointZero);
	this->addChild(exitMenu);

	exitBg->setPosition(ccp(exitBg->getPosition().x-winSize.width/2,exitBg->getPosition().y));
	exitBg->runAction( 
		CCEaseElasticOut::actionWithAction(
		CCMoveTo::actionWithDuration(2, ccp(400,240)), 0.35f
		) 
		);
	exitMenu->setPosition(ccp(exitMenu->getPosition().x-winSize.width/2,0));
	exitMenu->runAction( 
		CCEaseElasticOut::actionWithAction(
		CCMoveTo::actionWithDuration(2, CCPointZero), 0.35f
		) 
		);
}

void StartScene::keyBackClicked()
{
	//CCDirector::sharedDirector()->end();
}


bool isMusicOn = true;
bool isEffectOn = true;