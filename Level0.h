
#ifndef _LEVEL0_H_
#define _LEVEL0_H_

#include "cocos2d.h"
#include "PauseMenu.h"
#include "GameLayers.h"
#include "AppDelegate.h"

USING_NS_CC;

class Level0: public cocos2d::CCLayer
{
public:
	virtual bool init();
	static cocos2d::CCScene* scene();

	// implement the "static node()* method manually
	CREATE_FUNC(Level0);

private:

};

#endif