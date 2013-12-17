
#include "Level1.h"

using namespace cocos2d;

CCScene* Level1::scene()
{
	CCScene* scene = NULL;
	do
	{
		CCLayer* layer = CCLayer::create();
		layer->setContentSize(CCSizeMake(SCREEN_WIDTH, SCREEN_HEIGHT));

		CC_BREAK_IF(! layer);

		scene->addChild(layer, 1);

		

	} while (0);

	return scene;
}

bool Level1::init()
{
	bool bRet = false;

	do
	{
		CC_BREAK_IF(!CCLayer::init());


		bRet = true;
	} while (0);

	return bRet;
}