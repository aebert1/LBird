
#ifndef _MAINMENUSCENE_H_
#define _MAINMENUSCENE_H_

#include "cocos2d.h"
#include "Level0.h"

class MainMenu:public cocos2d::CCLayer
{
public:
	
	virtual bool init();
	static cocos2d::CCScene* scene();

	//functions for click even handling
	void onStartGame(CCObject* pSender);
	void changeScene();
	void onOptions(CCObject* pSender);
	void onQuit(CCObject* pSender);


	// implement the "static node()* method manually
	CREATE_FUNC(MainMenu);
};

#endif