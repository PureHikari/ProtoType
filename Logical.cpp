#include "Logical.h"
#include "commonData.h"

USING_NS_CC;

Logical* Logical::m_self = nullptr;

Logical* Logical::getInstance()
{
	if (!m_self)
	{
		m_self = new Logical();
	}

	return m_self;
}

void Logical::init(Node* node)
{
	m_layer = node;
}

void Logical::checkSkill(character* ch)
{
	if (ch->isAttack())
	{
		int skillNum = ch->attack();

		auto skill = Skill::create(skillNum);
		auto dr = ch->getDirection();

		Vec2 pos = Vec2::ZERO;
		if (dr == DIRECTION::LEFT)
		{
			pos = ch->getPosition() + Vec2(-GRID_SIZE,0);
		}
		else
		{
			pos = ch->getPosition() + Vec2(GRID_SIZE, 0);
		}

		skill->setPosition(pos);
		m_layer->addChild(skill);
	}
}