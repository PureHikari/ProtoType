#pragma once
//定义各种需要的参数，保证只有cpp文件调用该头文件

//每一格的大小
const int GRID_SIZE = 36;

//跳跃时移动的速度减少量
const float SLOW = 1.2f;

//英雄移动一格所需要的时间
const float HERO_MOVE_TIME = 0.5f;

//获取屏幕大小
#define VISIBLE_SIZE Director::getInstance()->getVisibleSize()