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

	this->initSkill();

	///*
	//测试用代码，用于展示角色的技能冷却
	schedule([=](float) {
		auto cd = (Label*)getChildByTag(778);

		std::string str="";
		int i = 0;
		while (true)
		{
			int cd = this->getSkillCD(i);
			if (cd != -1)
			{
				str += StringUtils::format("|%d", cd);
			}
			else
			{
				break;
			}

			i++;
		}

		if (cd)
		{
			cd->setString(str);
		}
		else
		{
			cd = Label::createWithSystemFont(str, "", 24);
			cd->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height + cd->getContentSize().height));
			this->addChild(cd, 10, 778);
		}
	},0.1f,"cd");
	//*/

	return true;
}

void character::turnOff(DIRECTION dr)
{
	if (dr == m_direction)
		return;

	if (dr ==DIRECTION::LEFT)
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

//采用计时器的移动方式保证每次移动都能对应格子线
void character::move(DIRECTION dr)
{
	turnOff(dr);

	auto time = m_speed;
	if (m_isJumping)
	{
		//跳跃时移动所需要的时间增加
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
		//如果处于跳跃状态，则直接返回不执行跳跃操作
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

void character::startAttack(int num)
{
	if (num >= m_skills.size())
		return;

	if (m_isFalling || m_isJumping || m_skills.at(num).cdRealTime > 0)
		return;

	m_skillNum = num;
	m_isAttacking = true;
}

int character::attack()
{
	m_isAttacking = false;

	m_skills.at(m_skillNum).cdRealTime = m_skills.at(m_skillNum).CoolDown;

	return m_skills.at(m_skillNum).id;
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
	if (id >= m_skills.size())
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

bool character::isMonster()
{
	if (m_standPoint == Character_type::Monster)
		return true;
	else
		return false;
}

void character::initSkill()
{
	//加载第一个技能，正面近身攻击一次
	skillData temp0;
	temp0.cdRealTime = 0;
	temp0.CoolDown = 120;
	temp0.id = 0;
	m_skills.push_back(temp0);

	//加载第二个技能，向正面发射
	skillData temp1;
	temp1.cdRealTime = 0;
	temp1.CoolDown = 120;
	temp1.id = 1;
	m_skills.push_back(temp1);

	//加载第三个技能，从中心向两方扩散
	skillData temp2;
	temp2.cdRealTime = 0;
	temp2.CoolDown = 120;
	temp2.id = 2;
	m_skills.push_back(temp2);
}