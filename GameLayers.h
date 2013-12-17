#pragma once

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "AppDelegate.h"


USING_NS_CC;




class BackgroundLayer : public cocos2d::CCLayer
{
public:

	BackgroundLayer();
	//virtual bool init();

	void initSky();
	void initGround();
	CREATE_FUNC(BackgroundLayer);
};

class GameLayer : public cocos2d::CCLayer
{
public:

	GameLayer();
	//virtual bool init();

	bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	void ccTouchEnded(CCTouch* touch, CCEvent* event);
	void ccTouchMoved(CCTouch* touch, CCEvent* event);

	void onEnter();
	void onExit();

	void initPlayer();
	void updatePlayer();

	void initForeground();
	void rotateForeground(float);

	void poopMech();

	virtual void update(float);

	bool poop;

	float angle;

	CCPoint startPos, endPos, tempPos;
	CCPoint pigeonPos;
	CCSprite* pigeonSprite;
	CCSprite* ground;
	CCSprite* target;
	CCSprite* bomb;

	b2World* world;

	
	CREATE_FUNC(GameLayer);

	
};

class HUDLayer : public cocos2d::CCLayer
{
public:
	
	HUDLayer();
	//virtual bool init();
	void initHUD();
	CREATE_FUNC(HUDLayer);
};