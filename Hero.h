#pragma once
#include "Character.h"

//����ɫ��ָ��ö��
enum class COMMAND
{
	NONE,
	LeftMove,//�����ƶ�
	LeftStop,//�����ƶ�ֹͣ
	RightMove,//�����ƶ�
	RightStop,//����ֹͣ
	Jump//��Ծ
};

//Ӣ�۵��࣬�̳��Խ�ɫ��character
//���˽��ܿ���ָ��ĺ�������ʱ
class Hero :public character
{
public:
	static Hero* create();
	virtual bool init();

	void getCommand(COMMAND cmd);
private:


};