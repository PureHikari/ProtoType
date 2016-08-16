#pragma once
#include "cocos2d.h"

class TitleScene :public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	bool virtual init();
	CREATE_FUNC(TitleScene);

	//进入新游戏
	void newGame();

	//进入编辑模式
	void editMode();
private:
};