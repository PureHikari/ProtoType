#include "Skill.h"
#include "commonData.h"

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

		for (auto ch : this->m_hitted)
		{
			ch->stopActionByTag(DEL_TAG);
		}
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
		//将角色放入向量中防止多次判断
		m_hitted.pushBack(ch);

		auto action= Sequence::create(DelayTime::create(m_interval), CallFuncN::create([=](Ref*) {
			if (this && this->getIsAvaliable() && ch)
			{
				//当间隔时间过后将角色从向量中删除
				m_hitted.eraseObject(ch);
			}
		}), nullptr);
		action->setTag(DEL_TAG);

		ch->runAction(action);

		return true;
	}

	return false;
}