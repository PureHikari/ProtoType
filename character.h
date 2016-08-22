#pragma once
#include "cocos2d.h"

//ö�ٽ�ɫ�ķ���
enum class DIRECTION
{
	//NONE,
	LEFT,
	RIGHT
};

//��ɫ����ļ�������
struct skillData
{
	int id;//���ܵ�id
	int CoolDown;//���ܵ���ȴʱ��
	int cdRealTime;//���ܵ���ȴ��ʱ
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

	//����
	void hit(int dmg);
	//������ƣ���֤����ֵ�������������ֵ
	void heal(int heal);

	int getHp() { return m_hp; }
	bool getIsAlive() { return m_isAlive; }

	//����˳���ȡ���ܵ���ȴ��ʱ������-1��ʾû�иü���
	int getSkillCD(int id);

	void coolDown();
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

	//��ɫ������ֵ���������ֵ
	int m_hp = 100;
	int m_maxHp = 100;

	bool m_isAlive = true;

	std::vector<skillData>m_skills;
};