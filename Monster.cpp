#include "Monster.h"

USING_NS_CC;

Monster* Monster::create()
{
	auto hero = new Monster();
	if (hero && hero->init())
	{
		hero->autorelease();
		return hero;
	}
	CC_SAFE_DELETE(hero);
	return nullptr;
}

bool Monster::init()
{
	if (!character::init())
	{
		return false;
	}

	m_standPoint = Character_type::Monster;

	///*
	//测试用代码，将血量显示在每个角色的头上并不断刷新
	schedule([=](float) {
		auto lab = static_cast<Label*>(this->getChildByTag(100));
		if (lab)
		{
			lab->setString(StringUtils::format("%d/%d", m_hp, m_maxHp));
		}
		else
		{
			lab = Label::createWithSystemFont(StringUtils::format("%d/%d", m_hp, m_maxHp), "", 24);
			lab->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height + lab->getContentSize().height * 2));
			this->addChild(lab, 10, 100);
		}

		if (m_hp > m_maxHp * 0.2f)
		{
			lab->setColor(Color3B::GREEN);
		}
		else
		{
			lab->setColor(Color3B::RED);
		}
	}, 0.1f, "fresh");
	//*/

	this->autoAttack();

	return true;
}

void Monster::autoAttack()
{
	schedule([=](float) {
		this->startAttack(random(0,1)?0:1);
	}, 1, "autoAttack");
}