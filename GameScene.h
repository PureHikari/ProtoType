#pragma once
 
#include "cocos2d.h"
#include "Hero.h"

class GameScene :public cocos2d::Layer
{
public:
	static cocos2d::Scene*  createScene();
	bool virtual init();

	CREATE_FUNC(GameScene);

	//��Ӹ��ּ�����
	void initListener();

	/*
	//������ʼ�ĺ���
	bool onBegan(cocos2d::Touch *touch, cocos2d::Event* event);
	//���������ĺ���
	void onEnd(cocos2d::Touch *touch, cocos2d::Event* event);
	//*/

	//���̰��µĺ���
	void onKeyPress(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	//�����ɿ��ĺ���
	void onKeyRelease(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
private:
	
	//Ӣ��
	Hero* m_hero=nullptr;
};