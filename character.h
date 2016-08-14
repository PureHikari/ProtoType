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
protected:
	//��ɫ�ĳ���Ĭ��Ϊ����
	DIRECTION m_direction = DIRECTION::RIGHT;

	//�Ƿ�����Ծ��״̬
	bool m_isJumping = false;

	//��ɫ���ٶȣ�����ÿ��һ������Ҫ��ʱ��
	float m_speed = 1.0f;
};