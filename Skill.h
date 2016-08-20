#pragma once
#include "cocos2d.h"

class Skill :public cocos2d::Sprite
{
public:
	static Skill* create(int id);
	bool virtual init(int id);

	bool getIsAvaliable() { return m_isAvaliable; }

	bool checkCollision(cocos2d::Sprite*);
private:

	bool m_isAvaliable = true;

	//�����洢�Ѿ����й���Ŀ�꣬��ֹ����ظ�����
	cocos2d::Vector<cocos2d::Sprite*> m_hitted;
};