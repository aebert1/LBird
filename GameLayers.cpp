
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



/********************************************************************
					        Game Layer

********************************************************************/

GameLayer::GameLayer():nIndexTic(0)
{
	bool bRet = false;

	do
	{
		CC_BREAK_IF(! GameLayer::init());

		angle = 0;

		poopSprite = NULL;
		

		initPlayer();

		initForeground();

		placeFireButton();

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
	angle = 0;
}

void GameLayer::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	CCLOG("Touch Moved");

		endPos = CCDirector::sharedDirector()->convertToGL(touch->getLocation());
		tempPos = endPos - startPos;
		startPos = endPos;


	pigeonPos = pigeonSprite->getPosition();

	if (tempPos.y < 0 && pigeonPos.y < 3200)
	{
		pigeonPos.y += 5.0f;
	}
	else if (tempPos.y > 0 && pigeonPos.y > 2735)
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
		frameCache->addSpriteFramesWithFile("LuckyFlying.plist");

		CCSpriteBatchNode* pigeonFlightSheet = CCSpriteBatchNode::create("LuckyFlying.png");
		addChild(pigeonFlightSheet, 3);

		CCArray* pigeonFrames = new CCArray;
		for ( int i = 2; i <= 4; i++)
		{
			CCString* filename = CCString::createWithFormat("lucky_flying_0000%d.png", i);
			CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(filename->getCString());
			pigeonFrames->addObject(frame);
		}

		CCAnimation* flightAnim = CCAnimation::createWithSpriteFrames(pigeonFrames, 0.1);
		pigeonSprite = CCSprite::createWithSpriteFrameName("lucky_flying_00002.png");

		//pigeonSprite->setScale(0.5f);
		pigeonSprite->setPosition(ccp(SCREEN_WIDTH/2 - 500, SCREEN_WIDTH*3 + 250));

		CCAction* flightAction = CCRepeatForever::create(CCAnimate::create(flightAnim));
		pigeonSprite->runAction(flightAction);
		pigeonFlightSheet->addChild(pigeonSprite, 3);

		schedule(schedule_selector(GameLayer::tick1), 0.10f);
		schedule(schedule_selector(GameLayer::tick2), 0.03f);

}

void GameLayer::placeFireButton()
{
	CCMenuItemImage* fireButton = CCMenuItemImage::create("fire_button.png", "fire_button_hit.png",
		this, menu_selector(GameLayer::onPoopMech));
	CCMenu* menu = CCMenu::create(fireButton, NULL);
	menu->setPosition(ccp(SCREEN_WIDTH/2 - 75, SCREEN_WIDTH*3 - 175));

	this->addChild(menu, 1);
}

void GameLayer::tick1(float dt)
{
	//CCPoint pige = pigeonSprite->getPosition();
	pigeonPos = pigeonSprite->getPosition();
	switch (nIndexTic)
	{
	case 0:
		pigeonPos.x = pigeonPos.x - 10;
		break;
	case 1:
		pigeonPos.x = pigeonPos.x + 10;
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
		pigeonSprite->setScaleX(1.0f);
	}
	else if (angle == 1.0f)
	{
		CCLog("update 1.0");
		rotateForeground(1.0f);
		pigeonSprite->setScaleX(-1.0f);
	}
	else
	{
		rotateForeground(0.0f);
	}

	CCLog("tick2");
}

void GameLayer::updatePlayer()
{

	pigeonSprite->runAction(CCMoveTo::create(0.0001f, pigeonPos));

}

void GameLayer::onPoopMech(CCObject* pSender)
{
	/*
	CCString* filename = new CCString;
	CCSpriteFrameCache* frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	frameCache->addSpriteFramesWithFile("poop1.plist");

	CCSpriteBatchNode* poopSheet = CCSpriteBatchNode::create("poop1.png");
	ground->addChild(poopSheet, 3);

	CCArray* poopFrames = new CCArray;
	//CCArray* poopFrames1 = new CCArray;
	for ( int i = 1; i <= 11; i++)
	{
		if (i < 10)
			filename = CCString::createWithFormat("poo_sprite%i.png", i);
		else
			filename = CCString::createWithFormat("poo_sprite%i.png", i);
		CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(filename->getCString());
		poopFrames->addObject(frame);
	}
	
	CCAnimation* poopAnim = CCAnimation::createWithSpriteFrames(poopFrames, 0.05f);
	//CCAnimation* poopAnim1 = CCAnimation::createWithSpriteFrames(poopFrames1, 0.05f);
	poopSprite = CCSprite::createWithSpriteFrameName("poo_sprite1.png");

	poopSprite->setPosition(ccp(pigeonSprite->getPositionX(), pigeonSprite->getPositionY()-50));

	CCAction* poopActBegin = CCAnimate::create(poopAnim);
	//CCAction* poopActEnd = CCAnimate::create(poopAnim1);
	CCAction* poopFall = CCMoveBy::create(1.0f, ccp(10*angle, pigeonSprite->getPositionY()-2735));

	poopSprite->runAction(poopActBegin);
	poopSprite->runAction(poopFall);
	//poopSprite = CCSprite::createWithSpriteFrameName("poo_sprite5.png");
	//poopSprite->runAction(poopActEnd);

	poopSheet->addChild(poopSprite, 3);

	/*
	float animDuration = 0.05;

	CCAnimation* poopAnim = CCAnimation::createWithSpriteFrames(poopFrames, animDuration);
	poopSprite = CCSprite::createWithSpriteFrameName("poo_sprite01.png");
	
	poopSprite->setPositionY(pigeonPos.y - 20);
	poopSprite->setPositionX(pigeonPos.x + 10 * angle);

	CCAction* poopAction = CCAnimate::create(poopAnim);
	CCAction* poopFall = CCMoveBy::create(animDuration, ccp(30*angle, -2));
	
	poopSprite->runAction(poopAction);
	
	poopSprite->runAction(poopFall);
	*/
	poopSprite = CCSprite::create("poo_sprite01.png");
	poopSprite->setPosition(ccp(pigeonSprite->getPositionX()-10, pigeonSprite->getPositionY()-48));

	this->addChild(poopSprite, 3);

	float fallDist = 2700-pigeonSprite->getPositionY();
	float fallDur = 0.0f;
	fallDur = 1.0f;


	CCAction* drop = CCMoveBy::create(fallDur, ccp(100*angle, fallDist));
	CCArray* actArray = CCArray::createWithCapacity(2);

	actArray->addObject(drop);
	actArray->addObject(CCCallFunc::create(poopSprite, callfunc_selector(CCSprite::removeFromParent)));
	
	CCSequence* seq = CCSequence::create(actArray);

	poopSprite->runAction(seq);
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
	CCArray* actArray = CCArray::createWithCapacity(2);

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
		menu->setPosition(SCREEN_WIDTH - 50, SCREEN_HEIGHT - 20);

		this->addChild(menu, 3);

		
}
