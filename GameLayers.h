#pragma once

#include "cocos2d.h"
#include "AppDelegate.h"

USING_NS_CC;




class SkyLayer : public cocos2d::CCLayer
{
public:

	SkyLayer();
	//virtual bool init();

	void initSky();
	CREATE_FUNC(SkyLayer);
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
	void placeFireButton();
	void updatePlayer();
	void updateElastic();
	void onPoopMech(CCObject* pSender);

	void initForeground();
	void rotateForeground(float);

	virtual void update(float);

	float angle;

	CCPoint startPos, endPos, tempPos;
	CCPoint pigeonPos;
	CCSprite* pigeonSprite;
	CCSprite* poopSprite;
	CCSprite* ground;
	void tick1(float dt);
	void tick2(float dt);
	CREATE_FUNC(GameLayer);
	int nIndexTic;
	
};

class HUDLayer : public cocos2d::CCLayer
{
public:
	
	HUDLayer();
	//virtual bool init();
	void initHUD();
	CREATE_FUNC(HUDLayer);
};