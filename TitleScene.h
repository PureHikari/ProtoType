#pragma once
#include "cocos2d.h"

class TitleScene :public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	bool virtual init();
	CREATE_FUNC(TitleScene);

	//选择关卡界面,参数为是否是编辑模式，编辑模式下有新建按钮
	void showMapSelect(bool isEdit);
private:
};