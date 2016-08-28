#pragma once
#include "Character.h"

//给角色的指令枚举
enum class COMMAND
{
	NONE,
	LeftMove,//向左移动
	LeftStop,//向左移动停止
	RightMove,//向右移动
	RightStop,//向右停止
	Jump,//跳跃
	Attack,//攻击
	Skill1,//技能1
	Skill2//技能2
};

//英雄的类，继承自角色类character
//多了接受控制指令的函数，暂时
class Hero :public character
{
public:
	static Hero* create();
	virtual bool init();

	void getCommand(COMMAND cmd);
private:


};