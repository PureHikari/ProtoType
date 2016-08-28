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
		//����ɫ���������з�ֹ����ж�
		m_hitted.pushBack(ch);

		auto action= Sequence::create(DelayTime::create(m_interval), CallFuncN::create([=](Ref*) {
			if (this && this->getIsAvaliable() && ch)
			{
				//�����ʱ����󽫽�ɫ��������ɾ��
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
		case 0://���Ϊ0���������������Ȼ��ԭ�ش���һ��ʱ��
		{
			this->runAction(Sequence::create(DelayTime::create(m_existTime), CallFuncN::create([=](Ref*) {
				this->doBeforeDie();
			}), nullptr));
		}
			break;
		case 1://���Ϊ1����������ɺ���ָ��������
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
		case 2://���Ϊ2����������ܴӽ�ɫλ�ÿ�ʼ��ɢ
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