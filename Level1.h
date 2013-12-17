#pragma once

#include "cocos2d.h"
#include "PauseMenu.h"
#include "GameLoop.h"
#include "AppDelegate.h"

USING_NS_CC;

class Level1: public cocos2d::CCLayer
{
public:
	virtual bool init();
	static cocos2d::CCScene* scene();

	// implement the "static node()" method manually
	CREATE_FUNC(Level1);

	GameLoop gameLoop;
};