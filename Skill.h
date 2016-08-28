#pragma once
#include "cocos2d.h"

/*
技能类继承自Sprite类，本身加载的图片代表技能命中判断的范围，之后会有专门的Sprite成员变量用于展示技能效果
*/

class Skill :public cocos2d::Sprite
{
public:
	static Skill* create(int id,bool isMsRelease,bool isLeft);
	bool virtual init(int id, bool isMsRelease, bool isLeft);

	bool getIsAvaliable() { return m_isAvaliable; }

	//检查传入的角色是否被该技能命中
	bool checkCollision(cocos2d::Sprite*);

	//按照具体的类型来执行相应的操作
	void action();

	//处理后事
	void doBeforeDie();

	int getDmg() { return m_dmg; }
	bool isMsReleased() { return m_isMsRelease; }
private:
	//编号
	int m_id = -1;

	bool m_isLeft = false;

	//是否有效
	bool m_isAvaliable = true;

	//用来存储已经命中过的目标，防止多次重复攻击
	cocos2d::Vector<cocos2d::Sprite*> m_hitted;

	//技能命中判断的间隔时间
	float m_interval = 1.0f;

	//技能应该造成的伤害
	//临时
	int m_dmg = 10;

	//技能持续的时间
	float m_existTime = 1.0f;

	//是否由怪物释放
	bool m_isMsRelease = false;
};