#ifndef _LOGOSCENE_H_
#define _LOGOSCENE_H_

#include "cocos2d.h"
#include "MainMenuScene.h"

class LogoScene:public cocos2d::CCLayer
{
public:

	virtual bool init();
	static cocos2d::CCScene* scene();

	void onChange();

	CREATE_FUNC(LogoScene);
};

#endif
