
#include "Level0.h"


using namespace cocos2d;

CCScene* Level0::scene()
{
	CCScene* scene = NULL;
	do
	{
		//scene is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		//layer is an autorelease object
		BackgroundLayer* backgroundLayer = BackgroundLayer::create();
		backgroundLayer->setContentSize(CCSizeMake(SCREEN_WIDTH, SCREEN_HEIGHT));
		CC_BREAK_IF(! backgroundLayer);

		//add layer as a child to scene
		scene->addChild(backgroundLayer, 1);
		/*
		GameLayer* gameLayer = GameLayer::create();
		gameLayer->setContentSize(CCSizeMake(SCREEN_WIDTH*3, SCREEN_WIDTH*3));
		gameLayer->setPosition(ccp(0, SCREEN_HEIGHT*-2.25));
		CC_BREAK_IF(! gameLayer);
		scene->addChild(gameLayer, 2);
		*/
		HUDLayer* hudLayer = HUDLayer::create();
		hudLayer->setContentSize(CCSizeMake(SCREEN_WIDTH, SCREEN_HEIGHT));
		CC_BREAK_IF(! hudLayer);

		scene->addChild(hudLayer, 4);

	} while (0);

	

	// return the scene
	return scene;
}

bool Level0::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCLayer::init());

		bRet = true;
	} while (0);

	return bRet;
}

