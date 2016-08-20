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

	this->runAction(Sequence::create(DelayTime::create(2.0f), CallFuncN::create([=](Ref*) {
		this->m_isAvaliable = false;
	}), nullptr));

	return true;
}

bool Skill::checkCollision(Sprite* ch)
{
	for (auto ht : m_hitted)
	{
		if (ht == ch)
		{
			return false;
		}
	}

	if (ch->getBoundingBox().intersectsRect(this->getBoundingBox()))
	{
		m_hitted.pushBack(ch);
		return true;
	}

	return false;
}