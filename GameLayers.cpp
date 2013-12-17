
#include "GameLayers.h"



BackgroundLayer::BackgroundLayer()
{
	bool bRet = false;

	do
	{
		CC_BREAK_IF(! BackgroundLayer::init());

		initSky();
		initGround();

		bRet = true;
	} while(0);

	//return bRet;
}

void BackgroundLayer::initSky()
{
	//Create and add sky to scene
	CCSprite* sky = CCSprite::create("sky.png");
	//sky->setScale(3.0f);
	sky->setPosition(ccp(SCREEN_WIDTH/2, SCREEN_HEIGHT/2));
	this->addChild(sky);

	//Create and add background buildings to scene
	CCSprite* building1 = CCSprite::create("buildings_BG.png");
	building1->setPosition(ccp(SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 - 135));
	this->addChild(building1);
	
	CCSprite* building2 = CCSprite::create("buildings_BG.png");
	building2->setPosition(ccp(SCREEN_WIDTH/2 + 350, SCREEN_HEIGHT/2 - 170));
	building2->setRotationY(10.0f);
	this->addChild(building2);
	
	CCSprite* cloud1 = CCSprite::create("cloud01.png");
	cloud1->setPosition(ccp(SCREEN_WIDTH/2 + 300, SCREEN_HEIGHT/2 + 250));
	this->addChild(cloud1);

	CCSprite* cloud2 = CCSprite::create("cloud02.png");
	cloud2->setPosition(ccp(SCREEN_WIDTH/2 - 250, SCREEN_HEIGHT/2 + 245));
	this->addChild(cloud2);

	CCSprite* cloud3 = CCSprite::create("cloud03.png");
	cloud3->setPosition(ccp(SCREEN_WIDTH/2 - 250, SCREEN_HEIGHT/2 + 100));
	this->addChild(cloud3);

}

void BackgroundLayer::initGround()
{
	CCSprite* bush1 = CCSprite::create("bush02.png");
	bush1->setPosition(ccp(SCREEN_WIDTH/2 + 300, SCREEN_HEIGHT/2 -205));
	this->addChild(bush1);

	CCSprite* bush2 = CCSprite::create("bush03.png");


	CCSprite* ground = CCSprite::create("grounds.png");
	ground->setPosition(ccp(SCREEN_WIDTH/2, SCREEN_HEIGHT/2 - 250));
	this->addChild(ground);
}





GameLayer::GameLayer()
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
		pigeonPos.y += 6.5f;
	}
	else if (tempPos.y > 0 && pigeonPos.y > SCREEN_WIDTH*2-320)
	{
		pigeonPos.y -= 6.5f;
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
	
	b2Vec2 gravity;
	gravity.Set(0.0f, -10.0f);

	world = new b2World(gravity);

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
		pigeonSprite->setPosition(ccp(SCREEN_WIDTH/2, (SCREEN_WIDTH/2)+(SCREEN_WIDTH*1.5)));

		CCAction* flightAction = CCRepeatForever::create(CCAnimate::create(flightAnim));
		pigeonSprite->runAction(flightAction);
		pigeonFlightSheet->addChild(pigeonSprite, 3);

}

void GameLayer::updatePlayer()
{

	pigeonSprite->runAction(CCMoveTo::create(0.001f, pigeonPos));

}

void GameLayer::initForeground()
{
		//Add background
		
		
		
		ground = CCSprite::create("GROUND.png");
		CCSprite* trees1 = CCSprite::create("TREE01.png");

		// Scale background to proper size
		ground->setScale(3.0);
		//trees1->setScale(0.5f);

		ground->setPosition(ccp((SCREEN_WIDTH/2), (SCREEN_HEIGHT/2)));
		trees1->setPosition(ccp((SCREEN_WIDTH/2)-220, (SCREEN_HEIGHT/2)+48));

		//sky->setAnchorPoint(ccp(SCREEN_WIDTH/2, (SCREEN_HEIGHT/2)-1300));
		//ground->setAnchorPoint(ccp(SCREEN_WIDTH/2, (SCREEN_HEIGHT/2)-1000));
		//trees1->setAnchorPoint(ccp((SCREEN_WIDTH/2), (SCREEN_HEIGHT/2)-1300));

		this->addChild(ground);
		ground->addChild(trees1);


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

void GameLayer::poopMech()
{
	CCLog("Enable Poop Launcher");
	target = CCSprite::create();
	target->setPosition(ccp(SCREEN_WIDTH/2, SCREEN_WIDTH*2-375));
	target->setAnchorPoint(ccp(SCREEN_WIDTH*1.5, SCREEN_WIDTH*1.5));

	ground->addChild(target, 1);

	target->runAction(CCRotateBy::create(0.5f, angle));

	bomb = CCSprite::create("poop.png");
	bomb->setPosition(ccp(pigeonSprite->getPositionX(), pigeonSprite->getPositionY()-50));

	this->addChild(bomb, 1);

	bomb->runAction(CCMoveTo::create(0.5f, target->getPosition()));
	
	if ( bomb->getPositionY() == target->getPositionY())
	{
		bomb->removeFromParentAndCleanup(true);
	}
	
}

void GameLayer::update(float dt)
{
	if (angle == -1.0f)
	{
		rotateForeground(-1.0f);
	}
	else if (angle == 1.0f)
	{
		rotateForeground(1.0f);
	}


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
	char str;
	int sc2 = -200;
	CCString* sc = CCString::create("Score: ");
	


		//Create pause menu sprite
		CCMenuItemFont* pauseItem = CCMenuItemFont::create("Pause", this, 
			menu_selector(PauseMenu::onPause));

		// combine to form a menu and allign Vertically
		CCMenu* menu = CCMenu::create(pauseItem, NULL);
		menu->alignItemsHorizontally();

		// set menu position
		menu->setPosition(SCREEN_WIDTH - 55, 20);

		this->addChild(menu, 1);

		
		CCLabelTTF* score = CCLabelTTF::create(sc->getCString(), "Comic Sans", 25);
		score->setPosition(ccp(SCREEN_WIDTH-200, SCREEN_HEIGHT-20));

		this->addChild(score, 3);
		

}
