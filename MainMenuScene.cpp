
#include "MainMenuScene.h"

using namespace cocos2d;

CCScene* MainMenu::scene()
{
	CCScene* scene = NULL;
	do
	{
		CCLOG("[MainMenu::scene]");

		// scene is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		//layer is an autorelease object
		MainMenu *layer = MainMenu::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the Main menu scene
	return scene;
}






// on "init" you need to initialze your instance
bool MainMenu::init()
{
	bool bRet = false;
	do
	{
		CCLayer::init();
		CC_BREAK_IF(!CCLayer::init());

		//Enable touch/click actions
		this->setTouchEnabled(true);


		///////////////////////////////////////////////////////////////////
		// initialize and set background 
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		CCSprite *background = CCSprite::create("screen_BG.png",
			CCRectMake(0,0,SCREEN_WIDTH, SCREEN_HEIGHT));
		
		background->setPosition(ccp(background->getContentSize().width/2,
								winSize.height/2));

		this->addChild(background);
		//////////////////////////////////////////////////////////////////




		//////////////////////////////////////////////////////////////////
		// Initialize and set playe button and menu 
		CCMenuItemToggle* pPlayItem = CCMenuItemToggle::createWithTarget(this,
			menu_selector(MainMenu::onStartGame),
			CCMenuItemImage::create("b_play.png", "b_play.png"),
			CCMenuItemImage::create("b_playHIT.png", "b_playHIT.png"),
			NULL);
		
		//CCMenuItemImage *pPlayItem = CCMenuItemImage::create("b_play.png", "b_playHIT.png", "b_playHIT.png",
		//	this, menu_selector(MainMenu::onStartGame));
		CC_BREAK_IF( !pPlayItem);

		CCMenuItemImage *pExitItem = CCMenuItemImage::create("b_exit.png", "b_exitHIT.png",
			this, menu_selector(MainMenu::onQuit));
		CC_BREAK_IF( !pExitItem);

		pPlayItem->setPosition(SCREEN_WIDTH/2 + 290, SCREEN_HEIGHT/2 + 100);
		pExitItem->setPosition(SCREEN_WIDTH/2 + 290, SCREEN_HEIGHT/2 - 100);

		CCMenu* pMenuSt = CCMenu::createWithItem(pPlayItem);
		CCMenu* pMenuEx = CCMenu::createWithItem(pExitItem);

		pMenuSt->setPosition(CCPointZero);
		pMenuEx->setPosition(CCPointZero);
		CC_BREAK_IF(! pMenuSt);
		CC_BREAK_IF(! pMenuEx);

		// add this to the layer
		this->addChild(pMenuSt, 1);
		this->addChild(pMenuEx, 1);
		/////////////////////////////////////////////////////////////////////


		bRet = true;
	} while (0);

	return bRet;
}

void MainMenu::onStartGame(CCObject* pSender)
{

	CCDelayTime* startDelay = CCDelayTime::create(0.2f);
	CCCallFunc* changeScene = CCCallFunc::create(this, callfunc_selector(MainMenu::changeScene));
	CCSequence* newSeq = CCSequence::create(startDelay, changeScene, NULL);
	runAction(newSeq);

}
void MainMenu::changeScene()
{
	//Load Level with transition
	CCScene* pScene = Level0::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0f, pScene));
}

void MainMenu::onOptions(CCObject* pSender)
{

}

void MainMenu::onQuit(CCObject* pSender)
{
	//Exit Game
	CCDirector::sharedDirector()->end();
}