#pragma once
#include "cocos2d.h"

class TitleScene :public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	bool virtual init();
	CREATE_FUNC(TitleScene);

	//ѡ��ؿ�����,����Ϊ�Ƿ��Ǳ༭ģʽ���༭ģʽ�����½���ť
	void showMapSelect(bool isEdit);
private:
};