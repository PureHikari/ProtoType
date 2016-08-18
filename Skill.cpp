#include "Skill.h"

USING_NS_CC;

Skill* Skill::create(int id)
{
	auto skill = new Skill();
	if (skill && skill->init(id))
	{
		skill->autorelease();
		return skill;
	}
	CC_SAFE_DELETE(skill);
	return nullptr;
}

bool Skill::init(int id)
{
	if (!Sprite::init())
	{
		return false;
	}

	this->initWithFile("skill.png");

	this->runAction(Sequence::create(DelayTime::create(2.0f), RemoveSelf::create(),nullptr));

	return true;
}