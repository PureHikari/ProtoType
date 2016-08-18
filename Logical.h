#pragma once
#include "character.h"
#include "Skill.h"

//�߼��࣬�����߼���������
//Ӣ�ۺ͹����ͷż����жϺ�ʵ��
//Ӣ�ۺ͹����յ����ܹ����ж�
//�������к�Ľ����жϺ�ʵ��
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