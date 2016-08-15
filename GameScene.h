#pragma once
 
#include "Hero.h"
#include "commonData.h"

//��ͼԪ�ص�ö�٣���ʱֻ�пպ��ϰ�
enum class MapElement
{
	NONE,
	BAREAL,
	HEROPOS//Ӣ�۵ĳ�ʼλ��
};

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

	//���ص�ͼ�Ľű�����ʱд���ں�����
	void initMap();
	//���յ�ͼ�ű����Ƶ�ͼ
	void paintMap();

	//����Ӣ��
	void initHero();

	//ʵ��Ӣ�۵����䣬����Ҳ��ʵ�ֹ��������Ч��
	void fallDown();
	//�����Ƿ���һ���Ƿ������½
	bool isNextLand(cocos2d::Vec2,bool);

	void update(float);
private:
	
	//Ӣ��
	Hero* m_hero=nullptr;
	//Ӣ�۵ĳ�ʼλ��
	cocos2d::Vec2 m_heroPos = cocos2d::Vec2::ZERO;

	//��ͼ,�ö�ά�����ʾ����ʱ���ȹ涨��С
	//i��ʾ��������ݣ�j��ʾ��������ݣ�����ʱ�������ϻ���
	MapElement m_map[GRID_X][GRID_Y] = { MapElement::NONE };
};