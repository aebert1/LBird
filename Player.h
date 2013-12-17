#pragma once

#include "cocos2d.h"
#include "Level0.h"

USING_NS_CC;

class Player
{
public:

	Player();

	void initPlayer();
	void updatePlayer();
	

	CCSpriteBatchNode* pigeonFlightSheet;
	CCPoint startPos, endPos, tempPos;
	CCPoint pigeonPos;
	CCSprite* pigeonSprite;

	
};