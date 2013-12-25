
#include "GameLayers.h"



SkyLayer::SkyLayer()
{
	bool bRet = false;

	do
	{
		CC_BREAK_IF(! SkyLayer::init());

		initSky();

		bRet = true;
	} while(0);

	//return bRet;
}

void SkyLayer::initSky()
{
	CCSprite* sky = CCSprite::create("sky.png");

	//sky->setScale(3.0f);
	sky->setPosition(ccp(SCREEN_WIDTH/2, SCREEN_HEIGHT/2));

	this->addChild(sky);
}














GameLayer::GameLayer():nIndexTic(0)
{
	bool bRet = false;

	do
	{
		CC_BREAK_IF(! GameLayer::init());

		angle = -1;

		initPlayer();

		initForeground();

		scheduleUpdate();


	} while(0);

	//return bRet;
}

bool GameLayer::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	CCLog("Touch Began");
	startPos = CCDirector::sharedDirector()->convertToGL(touch->getLocation());	
	
	return true;
}

void GameLayer::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	CCLOG("Touch Ended");
	
}

void GameLayer::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	CCLOG("Touch Moved");

		endPos = CCDirector::sharedDirector()->convertToGL(touch->getLocation());
		tempPos = endPos - startPos;
		startPos = endPos;


	pigeonPos = pigeonSprite->getPosition();

	if (tempPos.y < 0 && pigeonPos.y < SCREEN_WIDTH*2+100)
	{
		pigeonPos.y += 5.0f;
	}
	else if (tempPos.y > 0 && pigeonPos.y > SCREEN_WIDTH*2-320)
	{
		pigeonPos.y -= 5.0f;
	}

	if (tempPos.x > 10 )
	{
			//pigeonPos.x += 4.0f;
			angle = -1.0f;
			
	}

	else if (tempPos.x < -10 )
	{
			//pigeonPos.x -= 4.0f;
			angle = 1.0f;
	}

	updatePlayer();
}

void GameLayer::onEnter()
{
	//Enable touch
	this->setTouchEnabled(true);
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
	
	CCNode::onEnter();
}

void GameLayer::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCNode::onExit();
}

void GameLayer::initPlayer()
{

	CCSpriteFrameCache* frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
		frameCache->addSpriteFramesWithFile("pigeonFlight.plist");

		CCSpriteBatchNode* pigeonFlightSheet = CCSpriteBatchNode::create("pigeonFlight.png");
		addChild(pigeonFlightSheet, 3);

		CCArray* pigeonFrames = new CCArray;
		for ( int i = 1; i <= 18; i++)
		{
			CCString* filename = CCString::createWithFormat("pigeonFlight%d.png", i);
			CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(filename->getCString());
			pigeonFrames->addObject(frame);
		}

		CCAnimation* flightAnim = CCAnimation::createWithSpriteFrames(pigeonFrames, 0.05);
		pigeonSprite = CCSprite::createWithSpriteFrameName("pigeonFlight1.png");

		pigeonSprite->setScale(0.5f);
		pigeonSprite->setPosition(ccp(SCREEN_WIDTH/2 - 500, SCREEN_WIDTH*3 + 250));

		CCAction* flightAction = CCRepeatForever::create(CCAnimate::create(flightAnim));
		pigeonSprite->runAction(flightAction);
		pigeonFlightSheet->addChild(pigeonSprite, 3);

		schedule(schedule_selector(GameLayer::tick1), 0.10f);
		schedule(schedule_selector(GameLayer::tick2), 0.03f);

}

void GameLayer::tick1(float dt)
{
	//CCPoint pige = pigeonSprite->getPosition();
	pigeonPos = pigeonSprite->getPosition();
	switch (nIndexTic)
	{
	case 0:
		pigeonPos.x = pigeonPos.x - 30;
		break;
	case 1:
		pigeonPos.x = pigeonPos.x + 30;
		break;
	case 2:
		break;
	}
	updateElastic();
	nIndexTic++;
	if (nIndexTic==3)
		nIndexTic=0;
	CCLog("tick1");
}

void GameLayer::tick2(float dt)
{
	if (angle == -1.0f)
	{
		CCLog("update -1.0");
		rotateForeground(-1.0f);
	}
	else if (angle == 1.0f)
	{
		CCLog("update 1.0");
		rotateForeground(1.0f);
	}
	CCLog("tick2");
}


void GameLayer::updatePlayer()
{

	pigeonSprite->runAction(CCMoveTo::create(0.001f, pigeonPos));

}

void GameLayer::updateElastic()
{
	pigeonSprite->runAction(CCSpeed::create(CCMoveTo::create(0.001f, pigeonPos),0.008f));
}

void GameLayer::initForeground()
{
		//Add background
		
		
		ground = CCSprite::create("WorldForeground.png");
		
		ground->setPosition(ccp(0, 120));

		this->addChild(ground);
		//ground->addChild(trees1);


}

void GameLayer::rotateForeground(float dir)
{
	
	int d = 5;
	
	CCAction* action1 = runAction(CCRotateBy::create(0.05f, dir));
	CCArray* actArray = CCArray::createWithCapacity(1);

	actArray->addObject(action1);

	CCSequence* seq = CCSequence::create(actArray);

	ground->runAction(seq);

}

void GameLayer::update(float dt)
{
	CCLog("PigeonPos x=%f,y=%f",pigeonSprite->getPositionX(),pigeonSprite->getPositionY());
	/*if (angle == -1.0f)
	{
		CCLog("update -1.0");
		rotateForeground(-1.0f);
	}
	else if (angle == 1.0f)
	{
		CCLog("update 1.0");
		rotateForeground(1.0f);
	}*/
}




HUDLayer::HUDLayer()
{
	bool bRet = false;

	do
	{
		CC_BREAK_IF(! HUDLayer::init());

		initHUD();

	} while(0);

	//return bRet;
}

void HUDLayer::initHUD()
{
		//Create pause menu sprite
		CCMenuItemFont* pauseItem = CCMenuItemFont::create("Pause", this, 
			menu_selector(PauseMenu::onPause));

		// combine to form a menu and allign Vertically
		CCMenu* menu = CCMenu::create(pauseItem, NULL);
		menu->alignItemsHorizontally();

		// set menu position
		menu->setPosition(SCREEN_WIDTH - 55, 20);

		this->addChild(menu, 3);
}
