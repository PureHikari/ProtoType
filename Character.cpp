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
			this->runAction(MoveBy::create(time, Vec2(-GRID_SIZE, 0)));
			schedule([=](float) {
				this->runAction(MoveBy::create(time,Vec2(-GRID_SIZE,0)));
			}, time, "moveLeft");
		}
			break;
		case DIRECTION::RIGHT:
		{
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
	this->runAction(MoveBy::create(HERO_FALL_TIME, Vec2(0, -GRID_SIZE)));
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