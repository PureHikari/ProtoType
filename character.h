#pragma once
#include "cocos2d.h"

//枚举角色的方向
enum class DIRECTION
{
	//NONE,
	LEFT,
	RIGHT
};

//角色的基类，包含角色的移动和基本的属性，主角将继承此类
class character :public cocos2d::Sprite
{
public:
	static character* create();
	bool virtual init();

	void turnOff();//转身的函数

	void move(DIRECTION dr);//实现移动的函数,参数为移动的方向
	void stop(DIRECTION dr);//停止移动的函数，参数为停止的方向

	void jump();//跳跃的函数
	void jumpToHead();//停止跳跃的函数，当撞到墙的时候调用

	bool getIsJumping() { return m_isJumping; }
	bool getIsFalling() { return m_isFalling; }

	void fallDown();//开始下落
	void land();//落到地面，停止下落
protected:
	//角色的朝向，默认为朝右
	DIRECTION m_direction = DIRECTION::RIGHT;

	//是否处于跳跃的状态
	bool m_isJumping = false;
	//是否处于下落的状态
	bool m_isFalling = false;

	//角色的速度，代表每走一格所需要的时间
	float m_speed = 1.0f;
};