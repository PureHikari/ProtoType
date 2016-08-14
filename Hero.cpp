#include "Hero.h"
#include "commonData.h"

USING_NS_CC;

Hero* Hero::create()
{
	auto hero = new Hero();
	if (hero && hero->init())
	{
		hero->autorelease();
		return hero;
	}
	CC_SAFE_DELETE(hero);
	return nullptr;
}

bool Hero::init()
{
	if (!character::init())
	{
		return false;
	}

	m_speed = HERO_MOVE_TIME;

	return true;
}

void Hero::getCommand(COMMAND cmd)
{
	switch (cmd)
	{
		case COMMAND::LeftMove:
		{
			move(DIRECTION::LEFT);
		}
			break;
		case COMMAND::LeftStop:
		{
			stop(DIRECTION::LEFT);
		}
			break;
		case COMMAND::RightMove:
		{
			move(DIRECTION::RIGHT);
		}
			break;
		case COMMAND::RightStop:
		{
			stop(DIRECTION::RIGHT);
		}
			break;
		case COMMAND::Jump:
		{
			jump();
		}
			break;
		default:
			break;
	}
}