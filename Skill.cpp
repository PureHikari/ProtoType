#include "Skill.h"
#include "commonData.h"

USING_NS_CC;

Skill* Skill::create(int id, bool isMsRelease, bool isLeft)
{
	auto skill = new Skill();
	if (skill && skill->init(id,isMsRelease,isLeft))
	{
		skill->autorelease();
		return skill;
	}
	CC_SAFE_DELETE(skill);
	return nullptr;
}

bool Skill::init(int id, bool isMsRelease, bool isLeft)
{
	if (!Sprite::init())
	{
		return false;
	}

	this->initWithFile("skill.png");

	m_isMsRelease = isMsRelease;
	m_id = id;
	m_isLeft = isLeft;

	this->action();

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

void Skill::action()
{
	switch (m_id)
	{
		case 0://编号为0的情况，正面生成然后原地存在一段时间
		{
			this->runAction(Sequence::create(DelayTime::create(m_existTime), CallFuncN::create([=](Ref*) {
				this->doBeforeDie();
			}), nullptr));
		}
			break;
		case 1://编号为1的情况，生成后像指定方向发射
		{
			Vec2 pos;
			if (m_isLeft)
			{
				pos = Vec2(-GRID_SIZE * 20, 0);
			}
			else
			{
				pos = Vec2(GRID_SIZE * 20, 0);
			}

			this->runAction(Sequence::create(MoveBy::create(m_existTime, pos), CallFuncN::create([=](Ref*) {
				this->doBeforeDie();
			}), nullptr));
		}
			break;
		case 2://编号为2的情况，技能从角色位置开始扩散
		{
			this->runAction(Sequence::create(ScaleBy::create(m_existTime,5,1), CallFuncN::create([=](Ref*) {
				this->doBeforeDie();
			}), nullptr));
		}
			break;
	}
}

void Skill::doBeforeDie()
{
	this->m_isAvaliable = false;

	for (auto ch : this->m_hitted)
	{
		ch->stopActionByTag(DEL_TAG);
	}
}