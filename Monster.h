#pragma once
#include "character.h"

//������࣬�̳��Խ�ɫ��character
//��ʱû�ж�Ķ���
class Monster :public character
{
public:
	static Monster* create();
	virtual bool init();

	void autoAttack();
private:

};