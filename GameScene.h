#pragma once
 
#include "cocos2d.h"

class GameScene :public cocos2d::Layer
{
public:
	static cocos2d::Scene*  createScene();
	bool virtual init();

	CREATE_FUNC(GameScene);
private:
};