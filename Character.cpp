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

	this->initWithFile("closeNormal.png");

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
	if (m_isJumping)
	{
		//���������Ծ״̬����ֱ�ӷ��ز�ִ����Ծ����
		return;
	}
	else
	{
		m_isJumping = true;
		//comming soon
	}
}