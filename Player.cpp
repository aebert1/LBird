
#include "Player.h"

using namespace cocos2d;


Player::Player()
{

}

void Player::initPlayer()
{
	CCSpriteFrameCache* frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
		frameCache->addSpriteFramesWithFile("pigeonFlight.plist");

		pigeonFlightSheet = CCSpriteBatchNode::create("pigeonFlight.png");
		//addChild(pigeonFlightSheet, 3);

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
		pigeonSprite->setPosition(ccp(SCREEN_WIDTH/2, SCREEN_HEIGHT/2));

		CCAction* flightAction = CCRepeatForever::create(CCAnimate::create(flightAnim));
		pigeonSprite->runAction(flightAction);
		pigeonFlightSheet->addChild(pigeonSprite, 3);

}

void Player::updatePlayer()
{

	pigeonSprite->runAction(CCMoveTo::create(0.001f, pigeonPos));

}