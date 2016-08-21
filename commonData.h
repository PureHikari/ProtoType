#pragma once
//定义各种需要的参数，保证只有cpp文件调用该头文件

//每一格的大小
const int GRID_SIZE = 32;
//15 10

//横向和竖向的格子数目
const int GRID_X = 30;
const int GRID_Y = 20;

//跳跃时移动的速度减少量
const float SLOW = 1.2f;

//下落每一格所需要的时间
const float HERO_FALL_TIME = 0.10f;

//英雄移动一格所需要的时间
const float HERO_MOVE_TIME = 0.25f;

//获取屏幕大小
#define VISIBLE_SIZE Director::getInstance()->getVisibleSize()

//技能类中将角色从命中列表中删除的动作的tag
const int DEL_TAG = 777;

//定义各种zorder
#define BG_ZORDER -1
#define BR_ZORDER 1
#define HERO_ZOREDER 4