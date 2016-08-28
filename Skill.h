#pragma once
#include "cocos2d.h"

/*
������̳���Sprite�࣬������ص�ͼƬ�����������жϵķ�Χ��֮�����ר�ŵ�Sprite��Ա��������չʾ����Ч��
*/

class Skill :public cocos2d::Sprite
{
public:
	static Skill* create(int id,bool isMsRelease,bool isLeft);
	bool virtual init(int id, bool isMsRelease, bool isLeft);

	bool getIsAvaliable() { return m_isAvaliable; }

	//��鴫��Ľ�ɫ�Ƿ񱻸ü�������
	bool checkCollision(cocos2d::Sprite*);

	//���վ����������ִ����Ӧ�Ĳ���
	void action();

	//�������
	void doBeforeDie();

	int getDmg() { return m_dmg; }
	bool isMsReleased() { return m_isMsRelease; }
private:
	//���
	int m_id = -1;

	bool m_isLeft = false;

	//�Ƿ���Ч
	bool m_isAvaliable = true;

	//�����洢�Ѿ����й���Ŀ�꣬��ֹ����ظ�����
	cocos2d::Vector<cocos2d::Sprite*> m_hitted;

	//���������жϵļ��ʱ��
	float m_interval = 1.0f;

	//����Ӧ����ɵ��˺�
	//��ʱ
	int m_dmg = 10;

	//���ܳ�����ʱ��
	float m_existTime = 1.0f;

	//�Ƿ��ɹ����ͷ�
	bool m_isMsRelease = false;
};