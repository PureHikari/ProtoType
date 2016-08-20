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

//采用计时器的移动方式保证每次移动都能对应格子线
void character::move(DIRECTION dr)
{
	turnOff();

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

void character::startAttack()
{
	m_isAttacking = true;
}

int character::attack()
{
	m_isAttacking = false;
	return 1;
}

void character::hit(int dmg)
{
	auto lab = Label::createWithSystemFont(StringUtils::format("%d", dmg), "", 24);
	lab->setPosition(this->getContentSize() / 2);
	this->addChild(lab);

	lab->setColor(Color3B::RED);

	lab->runAction(Sequence::create(MoveBy::create(1, Vec2(0, GRID_SIZE * 2)), RemoveSelf::create(), nullptr));
}