#pragma once
 
#include "cocos2d.h"
#include "Hero.h"

class GameScene :public cocos2d::Layer
{
public:
	static cocos2d::Scene*  createScene();
	bool virtual init();

	CREATE_FUNC(GameScene);

	//添加各种监视器
	void initListener();

	/*
	//触摸开始的函数
	bool onBegan(cocos2d::Touch *touch, cocos2d::Event* event);
	//触摸结束的函数
	void onEnd(cocos2d::Touch *touch, cocos2d::Event* event);
	//*/

	//键盘按下的函数
	void onKeyPress(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	//键盘松开的函数
	void onKeyRelease(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
private:
	
	//英雄
	Hero* m_hero=nullptr;
};