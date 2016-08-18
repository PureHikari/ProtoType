#pragma once
#include "character.h"
#include "Skill.h"

//逻辑类，负责逻辑处理，包含
//英雄和怪物释放技能判断和实现
//英雄和怪物收到技能攻击判断
//技能命中后的奖励判断和实现
class Logical
{
public:
	static Logical* getInstance();

	void init(cocos2d::Node*);

	void checkSkill(character* ch);
private:
	static Logical* m_self;

	cocos2d::Node* m_layer = nullptr;
};