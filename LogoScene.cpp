
#include "LogoScene.h"

using namespace cocos2d;

CCScene* LogoScene::scene()
{
	CCScene* scene = NULL;
	do
	{
		//layer and scene are autorelease objects
		scene = CCScene::create();
		CC_BREAK_IF(! scene);
		LogoScene* layer = LogoScene::create();
		CC_BREAK_IF(! layer);

		//add layer as a child to scene
		scene->addChild(layer);

	} while (0);


	// return the Logo scene
	return scene;

}

bool LogoScene::init()
{
	bool bRet = false;
	int counter = 0;
	do
	{
		CCLayer::init();
		CC_BREAK_IF(!CCLayer::init());

		//Enable touch/click actions
		this->setTouchEnabled(false);

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCSprite* background = CCSprite::create("logo_ugofar.png",
			CCRectMake(0,0,SCREEN_WIDTH, SCREEN_HEIGHT));

		//set logo background
		background->setPosition(ccp(background->getContentSize().width/2,
												winSize.height/2));

		this->addChild(background);

		bRet = true;
		
		//set delay for logoscene and sequence before loading next scene
		CCDelayTime* startDelay = CCDelayTime::create(1.0f);
		CCCallFunc* changeScene = CCCallFunc::create(this, callfunc_selector(LogoScene::onChange));
		CCSequence* newSeq = CCSequence::create(startDelay, changeScene, NULL);
		runAction(newSeq);
		
		} while (0);
	
		
	return bRet;
}

void LogoScene::onChange()
{
	//initialize pscene and change scenes with transition
	CCScene* pScene = MainMenu::scene();			
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0f, pScene));
}