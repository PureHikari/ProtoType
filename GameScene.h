#pragma once
 
#include "Hero.h"
#include "commonData.h"

//地图元素的枚举，暂时只有空和障碍
enum class MapElement
{
	NONE,
	BAREAL,
	HEROPOS//英雄的初始位置
};

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

	//加载地图的脚本，暂时写死在函数内
	void initMap();
	//按照地图脚本绘制地图
	void paintMap();

	//加载英雄
	void initHero();

	//实现英雄的下落，后期也会实现怪物的下落效果
	void fallDown();
	//返回是否下一格是否可以着陆
	bool isNextLand(cocos2d::Vec2,bool);

	void update(float);
private:
	
	//英雄
	Hero* m_hero=nullptr;
	//英雄的初始位置
	cocos2d::Vec2 m_heroPos = cocos2d::Vec2::ZERO;

	//地图,用二维数组表示，暂时事先规定大小
	//i表示横向的数据，j表示竖向的数据，绘制时，从左上绘制
	MapElement m_map[GRID_X][GRID_Y] = { MapElement::NONE };
};