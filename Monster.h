#pragma once
#include "character.h"

//怪物的类，继承自角色类character
//暂时没有多的东西
class Monster :public character
{
public:
	static Monster* create();
	virtual bool init();

	void autoAttack();
private:

};