#include "character.h"
#include "commonData.h"

USING_NS_CC;

character* character::create()
{
	auto chara =new character();
	if (chara && chara->init())
	{
		chara->autorelease();
		return chara;
	}
	CC_SAFE_DELETE(chara);
	return nullptr;
}

bool character::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	this->initWithFile("hero.png");
	//this->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);

	///*
	//�����ô��룬��Ѫ����ʾ��ÿ����ɫ��ͷ�ϲ�����ˢ��
	schedule([=](float) {
		auto lab = static_cast<Label*>(this->getChildByTag(100));
		if (lab)
		{
			lab->setString(StringUtils::format("%d/%d", m_hp, m_maxHp));
		}
		else
		{
			lab = Label::createWithSystemFont(StringUtils::format("%d/%d", m_hp, m_maxHp), "", 24);
			lab->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height + lab->getContentSize().height));
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

	///*
	//�����ô��룬���ڼ���һ��ָ���ļ���
	skillData tempS;
	tempS.cdRealTime = 0;
	tempS.CoolDown = 120;
	tempS.id = 1;

	m_skills.push_back(tempS);
	//*/

	///*
	//�����ô��룬����չʾ��ɫ�ļ�����ȴ
	schedule([=](float) {
		auto cd = (Label*)getChildByTag(778);
		if (cd)
		{
			cd->setString(StringUtils::format("%d", m_skills.at(0).cdRealTime));
		}
		else
		{
			cd = Label::createWithSystemFont(StringUtils::format("%d", m_skills.at(0).cdRealTime), "", 24);
			cd->setPosition(Vec2(this->getContentSize().width / 2, -cd->getContentSize().height));
			this->addChild(cd, 10, 778);
		}
	},0.1f,"cd");
	//*/

	return true;
}

void character::turnOff()
{
	if (m_direction==DIRECTION::RIGHT)
	{
		m_direction = DIRECTION::LEFT;
		this->setSkewX(180);
	}
	else
	{
		m_direction = DIRECTION::RIGHT;
		this->setSkewX(0);
	}
}

//���ü�ʱ�����ƶ���ʽ��֤ÿ���ƶ����ܶ�Ӧ������
void character::move(DIRECTION dr)
{
	turnOff();

	auto time = m_speed;
	if (m_isJumping)
	{
		//��Ծʱ�ƶ�����Ҫ��ʱ������
		time *= SLOW;
	}

	switch (dr)
	{
		case DIRECTION::LEFT:
		{
			if(!m_isLeftStop)
				this->runAction(MoveBy::create(time, Vec2(-GRID_SIZE, 0)));
			schedule([=](float) {
				this->runAction(MoveBy::create(time,Vec2(-GRID_SIZE,0)));
			}, time, "moveLeft");
		}
			break;
		case DIRECTION::RIGHT:
		{
			if (!m_isRightStop)
				this->runAction(MoveBy::create(time, Vec2(GRID_SIZE, 0)));
			schedule([=](float) {
				this->runAction(MoveBy::create(time, Vec2(GRID_SIZE, 0)));
			}, time, "moveRight");
		}
			break;
		default:
			break;
	}
}

void character::stop(DIRECTION dr)
{
	switch (dr)
	{
		case DIRECTION::LEFT:
		{
			unschedule("moveLeft");
		}
			break;
		case DIRECTION::RIGHT:
		{
			unschedule("moveRight");
		}
			break;
		default:
			break;
	}
}

void character::stopped(bool left, bool right)
{
	m_isLeftStop = left;
	m_isRightStop = right;
}

void character::jump()
{
	if (m_isJumping || m_isFalling)
	{
		//���������Ծ״̬����ֱ�ӷ��ز�ִ����Ծ����
		return;
	}
	else
	{
		m_isJumping = true;
		//comming soon
		this->runAction(Sequence::create(MoveBy::create(HERO_MOVE_TIME, Vec2(0, GRID_SIZE * 4)), CallFuncN::create([=](Ref*) {
			m_isJumping = false;
		}), nullptr));
	}
}

void character::jumpToHead()
{
	m_isJumping = false;
	//unschedule("jumping");
	log("comming soonish");
}

void character::fallDown()
{
	m_isFalling = true;
	//this->runAction(MoveBy::create(HERO_FALL_TIME, Vec2(0, -GRID_SIZE)));
	schedule([=](float) {
		this->runAction(MoveBy::create(HERO_FALL_TIME,Vec2(0,-GRID_SIZE)));
	}, HERO_FALL_TIME, "fallDown");
}

void character::land()
{
	scheduleOnce([=](float) {
		m_isFalling = false;
	}, 0.1f, "forSafe");
	unschedule("fallDown");
}

void character::startAttack()
{
	if (m_skills.at(0).cdRealTime > 0)
		return;
	m_isAttacking = true;
}

int character::attack()
{
	m_isAttacking = false;

	m_skills.at(0).cdRealTime = m_skills.at(0).CoolDown;

	return 1;
}

void character::hit(int dmg)
{
	auto lab = Label::createWithSystemFont(StringUtils::format("%d", dmg), "", 24);
	lab->setPosition(this->getContentSize() / 2);
	this->addChild(lab);

	lab->setColor(Color3B::RED);

	lab->runAction(Sequence::create(MoveBy::create(1, Vec2(0, GRID_SIZE * 2)), RemoveSelf::create(), nullptr));

	m_hp -= dmg;
	if (m_hp <= 0)
	{
		m_hp = 0;

		m_isAlive = false;
	}
}

void character::heal(int heal)
{
	auto lab = Label::createWithSystemFont(StringUtils::format("%d", heal), "", 24);
	lab->setPosition(this->getContentSize() / 2);
	this->addChild(lab);

	lab->setColor(Color3B::GREEN);

	lab->runAction(Sequence::create(MoveBy::create(1, Vec2(0, GRID_SIZE * 2)), RemoveSelf::create(), nullptr));

	m_hp += heal;

	if (m_hp > m_maxHp)
	{
		m_hp = m_maxHp;
	}
}

int character::getSkillCD(int id)
{
	if (id > m_skills.size())
	{
		return -1;
	}

	return m_skills.at(id).cdRealTime;
}

void character::coolDown()
{
	for (int i = 0; i < m_skills.size(); i++)
	{
		m_skills.at(i).cdRealTime--;
		if (m_skills.at(i).cdRealTime < 0)
		{
			m_skills.at(i).cdRealTime = 0;
		}
	}
}