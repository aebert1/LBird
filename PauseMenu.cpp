
#include "PauseMenu.h"

using namespace cocos2d;

CCScene* PauseMenu::scene()
{
	CCScene* scene = NULL;
	do
	{
		// scene is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// layer  is an autorelease object
		PauseMenu* layer = PauseMenu::create();
		CC_BREAK_IF(! layer);

		//add layer as a child to scene
		scene->addChild(layer);

	} while(0);

	// return the scene
	return scene;
}

bool PauseMenu::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCLayer::init());

		//Enable touch
		this->setTouchEnabled(true);


		//Add Background to scene
		CCSprite* background = CCSprite::create("bg_pausescreen.png",
			CCRectMake(0,0,SCREEN_WIDTH, SCREEN_HEIGHT));
		background->setPosition(ccp(SCREEN_WIDTH/2, SCREEN_HEIGHT/2));

		this->addChild(background);

		//Add blackboard sprite to scene
		CCSprite* blackboard = CCSprite::create("blackboard.png",
			CCRectMake(0,0, getContentSize().width, getContentSize().height));
		blackboard->setPosition(ccp((SCREEN_WIDTH/2)+510, (SCREEN_HEIGHT/2)-10));

		this->addChild(blackboard);

		//Add score sprite to scene
		CCSprite* score = CCSprite::create("score.png");
		score->setPosition(ccp((SCREEN_WIDTH/2)+250, (SCREEN_HEIGHT/2)));

		this->addChild(score);

		//Add pigeon to scene
		CCSprite* pigeon = CCSprite::create("pigeon_pause.png",
			CCRectMake(0,0, getContentSize().width, getContentSize().height));
		pigeon->setPosition(ccp((SCREEN_WIDTH/2)+50, (SCREEN_HEIGHT/2)-113));

		this->addChild(pigeon);

		//Create pause menu buttons
		CCMenuItemImage* resumeItem = CCMenuItemImage::create("button_tap.png", "button_tap.png", 
			this, menu_selector(PauseMenu::onResume));
		CCMenuItemImage* exitItem = CCMenuItemImage::create("b_exit.png", "b_exit.png",
			this, menu_selector(PauseMenu::onQuit));
		// initialize menu and set position
		CCMenu* menu = CCMenu::create(resumeItem, NULL);
		CCMenu* menu1 = CCMenu::create(exitItem, NULL);
		menu->setPosition((SCREEN_WIDTH/2)+250, (SCREEN_HEIGHT/2)+230);
		menu1->setPosition((SCREEN_WIDTH/2)-100, (SCREEN_HEIGHT/2)-250);
		//add menu as child to scene
		this->addChild(menu, 1);
		this->addChild(menu1, 1);

		bRet = true;
	} while (0);

	return bRet;
}

// move to pause menu
void PauseMenu::onPause(CCObject* pSender)
{
	CCScene* pScene = PauseMenu::scene();
	CCDirector::sharedDirector()->pushScene(PauseMenu::scene());
}

//return to game level
void PauseMenu::onResume(CCObject* pSender)
{
	CCScene* pScene = PauseMenu::scene();
	CCDirector::sharedDirector()->popScene();
}

//return to the main menu
void PauseMenu::onQuit(CCObject* pSender)
{
	CCScene* pScene = PauseMenu::scene();
	CCDirector::sharedDirector()->replaceScene(MainMenu::scene());
}