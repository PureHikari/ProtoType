#pragma once
#include "cocos2d.h"

class TitleScene :public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	bool virtual init();
	CREATE_FUNC(TitleScene);

	//��������Ϸ
	void newGame();

	//����༭ģʽ
	void editMode();
private:
};