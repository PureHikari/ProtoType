#pragma once
#include "cocos2d.h"

class Skill :public cocos2d::Sprite
{
public:
	static Skill* create(int id);
	bool virtual init(int id);
private:
};