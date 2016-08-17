#pragma once
#include "cocos2d.h"
#include "commonData.h"

class MapGrid :public cocos2d::Sprite
{
public:
	static MapGrid* create();
	bool virtual init();

	void change();

	bool getIsBreal() { return m_isBreal; }
private:
	bool m_isBreal = false;
};

class EditScene :public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene(int id, bool isNew);
	bool virtual init(int id, bool isNew);

	static EditScene* create(int id, bool isNew);

	//划出格子之间的线
	void drawGridLine();

	//触摸函数
	bool onBegin(cocos2d::Touch* touch,cocos2d::Event* event);
	void onPress(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	void saveMap();
private:
	MapGrid* m_map[GRID_X][GRID_Y];

	//地图元素
	int m_mapId = 0;
	bool m_isNew = false;
};