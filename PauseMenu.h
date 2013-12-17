
#ifndef _PAUSEMENU_H_
#define _PAUSEMENU_H_

#include "cocos2d.h"
#include "MainMenuScene.h"


class PauseMenu:public cocos2d::CCLayer
{
public:

	virtual bool init();
	static cocos2d::CCScene* scene();
	
	// menu operation declarations
	void onPause(CCObject* pSender);
	void onResume(CCObject* pSender);
	void onQuit(CCObject* pSender);

	CREATE_FUNC(PauseMenu);

};



#endif