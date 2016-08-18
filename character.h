#pragma once
#include "cocos2d.h"

//ö�ٽ�ɫ�ķ���
enum class DIRECTION
{
	//NONE,
	LEFT,
	RIGHT
};

//��ɫ�Ļ��࣬������ɫ���ƶ��ͻ��������ԣ����ǽ��̳д���
class character :public cocos2d::Sprite
{
public:
	static character* create();
	bool virtual init();

	void turnOff();//ת��ĺ���

	void move(DIRECTION dr);//ʵ���ƶ��ĺ���,����Ϊ�ƶ��ķ���
	void stop(DIRECTION dr);//ֹͣ�ƶ��ĺ���������Ϊֹͣ�ķ���

	void jump();//��Ծ�ĺ���
	void jumpToHead();//ֹͣ��Ծ�ĺ�������ײ��ǽ��ʱ�����

	bool getIsJumping() { return m_isJumping; }
	bool getIsFalling() { return m_isFalling; }

	void fallDown();//��ʼ����
	void land();//�䵽���棬ֹͣ����

	//void attack();//����
	void startAttack();//��ʼ����
	int attack();//�����ĺ���������Ҫ�ͷż��ܵı�ţ��˴���ʱ�̶�Ϊ1
	bool isAttack() { return m_isAttacking; }//�����Ƿ��ڹ���״̬

	DIRECTION getDirection() { return m_direction; }//��ý�ɫ�ķ���

	void stopped(bool left, bool right);
protected:
	//��ɫ�ĳ���Ĭ��Ϊ����
	DIRECTION m_direction = DIRECTION::RIGHT;

	//�Ƿ�����Ծ��״̬
	bool m_isJumping = false;
	//�Ƿ��������״̬
	bool m_isFalling = false;

	//��ɫ���ٶȣ�����ÿ��һ������Ҫ��ʱ��
	float m_speed = 1.0f;

	bool m_isLeftStop = false;
	bool m_isRightStop = false;

	//�Ƿ��ڹ�����״̬
	bool m_isAttacking = false;
};